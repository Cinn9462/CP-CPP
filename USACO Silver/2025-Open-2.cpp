// TODO: Figure out why I get undefined behavior on USACO servers

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
#define un_map unordered_map
#define un_set unordered_set

#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, pair<ll, ll>& p) {
    return os << "[" << p.F << " " << p.S << "]";
}
ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct PairHash {
    size_t operator()(const pair<ll,ll>& p) const {
        return hash<ll>()(p.F) ^ (hash<ll>()(p.S) << 1);
    }
};

struct Node {
    ll num;
    bool A = false;
    bool B = false;
    Node() = default; 
    Node(ll a) : num(a) {}
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll num_cows, a, b;

    cin >> num_cows >> a >> b;

    un_set<ll> ids;
    un_map<ll, Node> cows;

    ll ID, n;
    For(i, num_cows) {
        cin >> n >> ID;
        cows.insert({ID, Node(n)});
        ids.insert(ID);
    }

    if (a == b) {
        ll result = 0;
        for (ll i : ids) {
            if (ids.count(a - i)) {
                result += min(cows[i].num, cows[a - i].num);
            }
        }
        cout << result / 2 << nl;
        return 0;
    }

    for (ll i : ids) {
        cows[i].A = ids.count(a - i);
        cows[i].B = ids.count(b - i);
    }

    ll result = 0;
    for (ll i : ids) {
        ll curr = i;
        while (cows[curr].A && !cows[curr].B || !cows[curr].A && cows[curr].B) {
            if (cows[curr].A && !cows[curr].B) {
                // Edge case where i is pairing with itself
                if (curr + curr == a) {
                    result += cows[curr].num / 2;
                    break;
                }

                result += min(cows[curr].num, cows[a - curr].num);
                // cout << result << ss << curr << ss << a - curr << nl;
                cows[a - curr].num = max(0LL, cows[a - curr].num - cows[curr].num);
                cows[curr].A = false;
                cows[a - curr].A = false;

                curr = a - curr;
            }
            else if (!cows[curr].A && cows[curr].B) {
                // Edge case where i is pairing with itself
                if (curr + curr == b) {
                    result += cows[curr].num / 2;
                    break;
                }

                result += min(cows[curr].num, cows[b - curr].num);
                // cout << result << ss << curr << ss << b - curr << nl;
                cows[b - curr].num = max(0LL, cows[b - curr].num - cows[curr].num);
                cows[curr].B = false;
                cows[b - curr].B = false;

                curr = b - curr;
            }
        }
    }

    cout << result << nl;
}