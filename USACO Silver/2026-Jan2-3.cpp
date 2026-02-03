// TODO : Optimize from N^2 solution

#define ll long long
#define pb push_back
#define v vector
#define p pair
#define fileread(file) freopen(((string) file + ".in").c_str(), "r", stdin); freopen(((string) file + ".out").c_str(), "w", stdout)
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define f0r(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "

#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;

    v<ll> nums(2 * N);
    unordered_set<ll> distinct;
    For(i, N) {
        cin >> nums[i];
        nums[i + N] = nums[i];
        distinct.insert(nums[i]);
    }

    v<ll> res(N, LLONG_MAX);

    For (left, N) {
        unordered_map<ll, ll> count;
        ll added = 0;
        f0r (right, left, left + N) {
            if (count[nums[right]] == 0) {
                added++;
            }
            count[nums[right]]++;

            if (added == distinct.size()) {
                f0r(i, left, right + 1) {
                    res[i % N] = min(res[i % N], (right - left) + min(i - left, right - i));
                }

                f0r(i, right + 1, left + N) {
                    res[i % N] = min(res[i % N], i - left);
                }

                break;
            }
        }
    }

    cout << res[0];
    for(ll i = 1; i < N; i++) {
        cout << ss << res[i];
    }
    cout << nl;
}