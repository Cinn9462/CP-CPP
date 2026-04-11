#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define roF(i, start) for (ll i = start; i >= 0; i--)
#define FOR(i, begin, end) for (ll i = begin; i < end; i++) 
#define nl "\n"
#define ss " "

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

int main () {
    ll N; cin >> N;
    v<ll> nums(N);
    v<string> type(N);
    unordered_map<ll, ll> compression;
    For (i, N) cin >> type[i] >> nums[i];

    v<ll> arr(nums); sort(arr.begin(), arr.end());
    arr.resize(unique(arr.begin(), arr.end()) - arr.begin());
    
    For(i, arr.size()) compression[arr[i]] = i;
    For(i, N) if(type[i] != "K") nums[i] = compression[nums[i]];


    v<ll> segtree(4*N);
    bool flag = false;

    auto count = [&](auto&& self, ll qright, ll left, ll right, ll index) -> ll {
        
        if (left > qright) return 0;

        if (qright >= right) return segtree[index];

        return self(self, qright, left, (left + right) / 2, 2*index) + self(self, qright, (left + right) / 2 + 1, right, 2*index + 1);
    };

    auto update = [&](auto&& self, ll left, ll right, ll index, ll qindex, bool type) -> bool { // false = delete, true = insert
        bool valid = false;
        
        if (left == right && !segtree[index] && type) return ++segtree[index];
        else if (left == right && segtree[index] && !type) return !--segtree[index];
        else if (left == right) return false;

        if (qindex <= (left + right) / 2) {
            valid = self(self, left, (left + right) / 2, 2*index, qindex, type);
        }
        else {
            valid = self(self, (left + right) / 2 + 1, right, 2*index + 1, qindex, type);
        }
        
        if (valid) segtree[index] += (type) ? 1 : -1;
        return valid;
    };

    auto kth = [&](auto&& self, ll left, ll right, ll index, ll modifier, ll target) -> ll {
        if (left == right) {    
            return left;
        }

        if (modifier + segtree[2*index] < target) {
            return self(self, (left + right) / 2 + 1, right, 2*index+1, modifier + segtree[2*index], target);
        }
        else {
            return self(self, left, (left + right) / 2, 2*index, modifier, target);
        }
    };

    For(i, N) {
        if (type[i] == "I") update(update, 0, N, 1, nums[i], true);
        if (type[i] == "D") update(update, 0, N, 1, nums[i], false);
        if (type[i] == "K") {
            ll n = kth(kth, 0, N, 1, 0, nums[i]);
            cout << (n < arr.size() ? to_string(arr[n]) : "invalid") << nl;
        }
        if (type[i] == "C") cout << count(count, nums[i] - 1, 0, N, 1) << nl;
    }
}