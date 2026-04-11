#!/usr/bin/env bash
# stress.sh — stress tester for W2P4 (Maximum Independent Set)
#
# Usage:  bash 602P/stress.sh [num_tests] [max_N]
# Defaults: 500 tests, N up to 10
#
# Compiles W2P4.cpp and brute.cpp, then runs random small cases
# and compares the MIS *size* (first line of output).
# Stops and prints the failing test on the first mismatch.

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
    # Generate a random test case with python
    TEST=$(python3 -c "
import random
N = random.randint(1, $MAX_N)
max_edges = N * (N - 1) // 2
M = random.randint(0, max_edges)
edges = random.sample([(u, v) for u in range(N) for v in range(u+1, N)], M)
print(N, M)
for u, v in edges:
    print(u, v)
")

    OUT_W2P4=$(echo "$TEST"  | /tmp/w2p4  2>/dev/null | head -1)
    OUT_BRUTE=$(echo "$TEST" | /tmp/brute 2>/dev/null | head -1)

    if [ "$OUT_W2P4" != "$OUT_BRUTE" ]; then
        FAILS=$((FAILS + 1))
        echo ""
        echo "=== WRONG on test $i ==="
        echo "--- Input ---"
        echo "$TEST"
        echo "--- W2P4  says: $OUT_W2P4"
        echo "--- Brute says: $OUT_BRUTE"
    fi

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
