#include <bits/stdc++.h>
using namespace std;

int num_col;
int num_trains;

void ahead(int i, int j, vector<string> &grid) {
    if (j < num_col - 3 && grid[i][j + 1] == '.' && grid[i][j + 2] == '.' && grid[i][j + 3] == '.') {
        grid[i][j + 1] = 's';
        grid[i][j + 2] = 's';
        grid[i][j + 3] = 's';
    }
    return;
}

int main () {
    int T;
    cin >> T;
    while (T--) {
        cin >> num_col >> num_trains;

        vector<string> grid(3);
        cin >> grid[0];
        cin >> grid[1];
        cin >> grid[2];

        for (int i = 0; i < num_col - 1; i += 3) {
            if (grid[1][i] == 's' && grid[1][i + 1] == '.' || grid[1][i + 1] == 's') {
                ahead(0, i, grid);
                ahead(1, i, grid);
                ahead(2, i, grid);
            }

            if (grid[0][i] == 's' && grid[0][i + 1] == '.' || grid[0][i + 1] == 's') {
                ahead(0, i, grid);
                ahead(1, i, grid);
            }

            if (grid[2][i] == 's' && grid[2][i + 1] == '.' || grid[2][i + 1] == 's') {
                ahead(1, i, grid);
                ahead(2, i, grid);
            }
        }

        bool found = false;

        for (int i = 0; i < 3; i++) {
            int index = num_col - 1;
            while (grid[i][index] == '.') index--;
            if (grid[i][index] == 's' && !found) {
                cout << "YES\n";
                found = true;
            }
        }
        
        if (!found) {
            cout << "NO\n";
        }
    }
}  