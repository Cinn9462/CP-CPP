#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define v vector
#define pb push_back
#define all(x) x.begin(), x.end()
#define For(i, a) for(ll i = 0; i < a; i++)
#define FOR(i, a, b) for(ll i = a; i < b; i++)
#define ss " "
#define nl "\n"

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N; v<ll> nums(N); For(i, N) cin >> nums[i];
    if (N < 10) {
        For(i, N) {
            FOR(j, i + 1, N) {
                bool inc = false;
                bool dec = false;
                swap(nums[i], nums[j]);
                FOR(k, 1, N) {
                    if (nums[k] < nums[k - 1]) inc = true;
                    if (nums[k] > nums[k - 1]) dec = true;
                }
                if(inc && dec && nums[i] != nums[j]) {
                    cout << i + 1 << ss << j + 1 << nl;
                    return 0;
                }
                swap(nums[i], nums[j]);
            }
        }
        cout << -1 << nl;
    }
    else {
        ll li = max_element(all(nums)) - nums.begin();
        ll l = nums[li];
        ll lfreq = count(all(nums), l);
        if (lfreq == N) {
            cout << -1 << nl;
            return 0;
        }
        if (nums[0] == l && nums.back() == l) {
            if (lfreq == 2) {
                cout << 0 + 1 << ss << 1 + 1 << nl;
                return 0;
            }
            else {
                ll r = 0;
                FOR(i, 1, N - 1) {
                    if (nums[i] == l) li = i;
                    else r = i;
                }
                cout << li + 1 << ss << r + 1 << nl;
            }
        }
        else if (lfreq == 1) {
            ll r = 0;
            FOR(i, 1, N - 1) {
                if (nums[i] != l) r = i;
            }
            cout << li + 1 << ss << r + 1<< nl;
        }
        else if (nums[0] == l) {
            FOR(i, 1, N - 1) {
                if (nums[i] == l) li = i;
            }
            cout << li + 1<< ss << N - 1 + 1 << nl;
        }
        else if (nums.back() == l) {
            FOR(i, 1, N - 1) {
                if (nums[i] == l) li = i;
            }
            cout << li + 1<< ss << 0 + 1<< nl;
        }
        else {
            ll r = 0;
            FOR(i, 1, N - 1) {
                if (nums[i] != l) r = i;
            }
            cout << li + 1<< ss << r + 1<< nl;
        }
    }
}