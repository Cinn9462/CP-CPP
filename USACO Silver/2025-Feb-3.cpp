#define ll long long
#define pb push_back 
#define v vector
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define f0r(i, begin, end) for (ll i = begin; i < end; i++) 

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, pair<ll, ll>& p) {
    return os << p.F << " " << p.S;
}
ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int main() {
    ll num_test; cin >> num_test;
    For(_i, num_test) {
        ll x, y, x_goal, y_goal;
        cin >> x >> y >> x_goal >> y_goal;

        pair<ll, ll> start, goal;
        start = MP (x, y);
        goal = MP(x_goal, y_goal);

        if (x > x_goal || y > y_goal) {
            cout << -1 << endl;
            continue;
        }

        ll count = 0;

        while(goal.F > start.F && goal.S > start.S) { // Smaller must have been added to greater
            if (goal.F > goal.S) {
                count += goal.F / goal.S;
                goal.F %= goal.S;
            }

            else {
                count += goal.S / goal.F;
                goal.S %= goal.F;
            }

        }

        // At the end, numbers must be expressed as [a, n*a + b] or [n*b + a, b]

        // cout << goal << endl;

        if (goal.F == start.F && (goal.S - start.S) % goal.F == 0) {
            cout << (count + (goal.S - start.S) / goal.F) << endl;
        }

        else if (goal.S == start.S && (goal.F - start.F) % goal.S == 0) {
            cout << (count + (goal.F - start.F) / goal.S) << endl;
        }

        else {
            cout << -1 << endl;
        }
    }
}