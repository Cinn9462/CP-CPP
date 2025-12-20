#define ll long long
#define pb push_back 
#define v vector
#define p pair
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define INF 1000000000000000000
#define inf 1000000001
#define MP(x, y) make_pair(x, y)
#define F first
#define S second
#define For(i, end) for (ll i = 0; i < end; i++)
#define f0r(i, begin, end) for (ll i = begin; i < end; i++)
#define NL "\n"

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

struct Node {
    ll parent;
    ll length;
    unordered_set<ll> children;

    Node(ll _p, ll _l, unordered_set<ll> _c) : parent(_p), length(_l), children(_c) {}
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll num_words; cin >> num_words;

    vector<Node> words = {Node(-1, 0, {})};

    ll _p;
    ll num_unique = 1;
    f0r(i, 1, num_words + 1) {
        cin >> _p;
        
        if (words[_p].children.size() == 0) {
            num_unique--;
        }
        
        words[_p].children.insert(i);
    
        words.pb(Node(_p, words[_p].length + 1, {}));
        num_unique++;
    }

    ll read_word;
    For (_i, num_unique) {
        cin >> read_word;
        ll earliest_node = read_word;
        ll earlier_node = read_word;
        
        // Find earliest node where there is a split
        while(earliest_node != -1 && words[earliest_node].children.size() <= 1) {
            earlier_node = earliest_node;
            earliest_node = words[earliest_node].parent;
        }

        if (earliest_node == -1) { // If last word in wordbank
            cout << 0 << NL;
        }

        else {
            cout << words[earliest_node].length + 1 << NL;

            // Remove word from shared node
            words[earliest_node].children.erase(earlier_node);
        }
    }
}