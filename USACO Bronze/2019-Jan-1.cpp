#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ifstream fin ("shell.in");
    ofstream fout ("shell.out");
    
    array<int, 3> stones = {0, 1, 2};
    array<int, 3> count = {0, 0, 0};

    int swaps; fin >> swaps;
    int swap1, swap2, guess, temp;

    for (int i = 0; i < swaps; i++) {
        fin >> swap1 >> swap2 >> guess;
        temp = stones[swap1 - 1];
        stones[swap1 - 1] = stones[swap2 - 1];
        stones[swap2 - 1] = temp;
        count[stones[guess - 1]]++;
    }
    fout << *max_element(count.begin(), count.end());
}