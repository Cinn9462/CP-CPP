#include <bits/stdc++.h>
using namespace std;

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
#define all(x) x.begin(), x.end()

ostream& operator<<(ostream& os, v<ll>& arr) {
    for (ll ___a : arr) {
        os << ___a << " ";
    }
    return os;
}

struct Rect {
    ll x1, x2, y1, y2;
    Rect(ll a, ll b, ll c, ll d) : x1(a), y1(b), x2(c), y2(d) {}
    Rect() : x1(0), y1(0), x2(0), y2(0) {}
};

struct Node {
    ll mv; // min value
    ll cnt;
    Node(ll a, ll b) : mv(a), cnt(b) {}
    Node() : mv(0), cnt(0) {}
};

void combine(Node& n1, Node& n2, Node& n) {
    n.mv = min(n1.mv, n2.mv);
    n.cnt = (n1.mv == n.mv ? n1.cnt : 0) + (n2.mv == n.mv ? n2.cnt : 0);
}

bool CompY1(Rect& r1, Rect& r2) {
    return r1.y1 < r2.y1;
}
bool CompY2(Rect& r1, Rect& r2) {
    return r1.y2 < r2.y2;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    ll N; cin >> N;
    v<Rect> r_start(N);
    
    For(i, N) {
        cin >> r_start[i].x1 >> r_start[i].y1 >> r_start[i].x2 >> r_start[i].y2;
        r_start[i].x1 += 1e6;
        r_start[i].y1 += 1e6;
        r_start[i].x2 += 1e6;
        r_start[i].y2 += 1e6;
    }

    v<Rect> r_end(r_start);
    sort(all(r_start), CompY1); // order of smallest y1
    sort(all(r_end), CompY2); // order of smallest y2

    // Segtree of x coordinates with lazy prop
    v<Node> segtree(8e6);
    v<ll> lazy(8e6);

    auto build = [&](auto&& self, ll l, ll r, ll index) {
        if (l == r) {
            segtree[index] = Node(0, 1);
            return;
        }
        self(self, l, (l + r) / 2, 2*index);
        self(self, (l + r) / 2 + 1, r, 2*index+1);
        combine(segtree[2*index], segtree[2*index+1], segtree[index]);
    };

    build(build, 0, 2e6, 1);

    auto update = [&](auto&& self, ll ql, ll qr, ll left, ll right, ll index, ll modifier) -> void {

        if (lazy[index]) {
            segtree[index].mv += lazy[index];
            if (left != right) {
                lazy[2 * index] += lazy[index];
                lazy[2 * index + 1] += lazy[index];
            }
            lazy[index] = 0;
        }

        if (qr < left || ql > right) return; // query out of range
        
        if (ql <= left && qr >= right) { // query completely in range
            segtree[index].mv += modifier;
            if (left != right) {
                lazy[2 * index] += modifier;
                lazy[2 * index + 1] += modifier;
            }
            return;
        }
        
        // query partially in range
        self(self, ql, qr, left, (left + right) / 2, 2*index, modifier);
        self(self, ql, qr, (left + right) / 2 + 1, right, 2*index + 1, modifier);

        combine(segtree[2*index], segtree[2*index + 1], segtree[index]);
    };


    // timeline -> events at y1s and y2s
    ll prev_time = 0;
    ll time = 0;
    ll area = 0;
    ll sp = 0; // sp -> start pointer
    ll ep = 0; // ep -> end pointer

    while(sp < N || ep < N) {
        // Calculate area
        area += (2e6 + 1 - (segtree[1].mv == 0 ? segtree[1].cnt : 0)) * (time - prev_time);

        // Remove old nodes
        while (ep < N && r_end[ep].y2 == time) {
            update(update, r_end[ep].x1, r_end[ep].x2 - 1, 0, 2e6, 1, -1);
            ep++;
        }

        // Insert new nodes
        while (sp < N && r_start[sp].y1 == time) {
            update(update, r_start[sp].x1, r_start[sp].x2 - 1, 0, 2e6, 1, 1);
            sp++;
        }
        
        prev_time = time;
        time = min((ep < N ? r_end[ep].y2 : 1e12), (sp < N ? r_start[sp].y1 : 1e12));
    }

    cout << area << nl;
}