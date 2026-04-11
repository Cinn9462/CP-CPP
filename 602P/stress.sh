#!/usr/bin/env bash
# stress.sh — stress tester for W2P4 (Maximum Independent Set)
#
# Usage:  bash 602P/stress.sh [num_tests] [max_N]
# Defaults: 500 tests, N up to 10
#
# Compiles W2P4.cpp and brute.cpp, then runs random small cases.
# Checks that:
#   1. W2P4's MIS size matches the brute-force size.
#   2. The vertices W2P4 outputs actually form a valid independent set.

set -euo pipefail

NUM_TESTS=${1:-500}
MAX_N=${2:-10}
DIR="$(cd "$(dirname "$0")" && pwd)"

echo "Compiling..."
g++ -O2 -o /tmp/w2p4   "$DIR/W2P4.cpp"
g++ -O2 -o /tmp/brute  "$DIR/brute.cpp"
echo "Done. Running $NUM_TESTS tests with N <= $MAX_N ..."

FAILS=0
for i in $(seq 1 "$NUM_TESTS"); do
    # Generate a random test case via a separate Python script (avoids CRLF/inline issues)
    TEST=$(python3 "$DIR/gen.py" "$MAX_N")

    FULL_W2P4=$(echo "$TEST" | /tmp/w2p4  2>/dev/null || true)
    OUT_BRUTE=$(echo "$TEST" | /tmp/brute 2>/dev/null | head -1 || true)

    OUT_W2P4=$(echo "$FULL_W2P4" | head -1 || true)
    VERTS_W2P4=$(echo "$FULL_W2P4" | tail -n +2 || true)

    FAIL=0

    # Check 1: size matches brute force
    if [ "$OUT_W2P4" != "$OUT_BRUTE" ]; then
        FAIL=1
        echo ""
        echo "=== WRONG SIZE on test $i ==="
        echo "--- Input ---"
        echo "$TEST"
        echo "--- W2P4  says: $OUT_W2P4"
        echo "--- Brute says: $OUT_BRUTE"
    fi

    # Check 2: the vertices W2P4 listed actually form an independent set
    if ! python3 - "$TEST" "$VERTS_W2P4" <<'PYEOF'
import sys

raw_input = sys.argv[1]
raw_verts = sys.argv[2]

lines = raw_input.strip().split('\n')
N, M = map(int, lines[0].split())

adj = [set() for _ in range(N)]
for line in lines[1:]:
    parts = line.split()
    if len(parts) == 2:
        u, v = int(parts[0]), int(parts[1])
        adj[u].add(v)
        adj[v].add(u)

verts = list(map(int, raw_verts.split())) if raw_verts.strip() else []

ok = True
for idx, u in enumerate(verts):
    for v in verts[idx + 1:]:
        if v in adj[u]:
            ok = False
            break
    if not ok:
        break

sys.exit(0 if ok else 1)
PYEOF
    then
        FAIL=1
        echo ""
        echo "=== NOT AN INDEPENDENT SET on test $i ==="
        echo "--- Input ---"
        echo "$TEST"
        echo "--- W2P4 vertices: $VERTS_W2P4"
    fi

    FAILS=$((FAILS + FAIL))

    # Progress indicator every 50 tests
    if (( i % 50 == 0 )); then
        echo "  $i / $NUM_TESTS done  ($FAILS wrong so far)"
    fi
done

echo ""
if (( FAILS == 0 )); then
    echo "All $NUM_TESTS tests passed!"
else
    echo "$FAILS / $NUM_TESTS tests WRONG."
fi
