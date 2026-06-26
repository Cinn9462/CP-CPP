    #include <bits/stdc++.h>
    using namespace std;

    #define ll long long
    #define v vector
    #define pb push_back
    #define all(x) x.begin(), x.end()
    #define For(i, a) for(ll i = 0; i < a; i++)
    #define FOR(i, a, b) for(ll i = a; i < b; i++)
    #define roF(i, a) for(ll i = a; i >= 0; i--)
    #define ROF(i, a, b) for(ll i = a; i >= b; i--)
    #define ss " "
    #define nl "\n"

    int main() {
        ll N, K; cin >> N >> K;
        v<ll> nums;
        ll a, b, c, d, e, f;
        cout << "and 1 2" << endl;
        cin >> a;
        cout << "or 1 2" << endl;
        cin >> b;
        cout << "and 1 3" << endl;
        cin >> c;
        cout << "or 1 3" << endl;
        cin >> d;
        cout << "and 2 3" << endl;
        cin >> e;
        cout << "or 2 3" << endl;
        cin >> f;

        nums.pb((a + b + c + d + e + f) / 2 - e - f); // 1
        nums.pb((a + b + c + d + e + f) / 2 - c - d); // 2
        nums.pb((a + b + c + d + e + f) / 2 - a - b); // 3

        FOR(i, 4, N + 1) {
            cout << "and 1 " << i << endl;
            cin >> a;
            cout << "or 1 " << i << endl;
            cin >> b;
            nums.pb(a + b - nums[0]);
        }
        sort(all(nums));
        cout << "finish " <<  nums[K - 1] << endl;
        return 0;
    }