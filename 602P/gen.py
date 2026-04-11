import random
import sys

MAX_N = int(sys.argv[1]) if len(sys.argv) > 1 else 10

N = random.randint(1, MAX_N)
max_edges = N * (N - 1) // 2
M = random.randint(0, max_edges)
edges = random.sample([(u, v) for u in range(N) for v in range(u + 1, N)], M)
print(N, M)
for u, v in edges:
    print(u, v)
