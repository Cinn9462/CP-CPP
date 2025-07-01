#define ll long long
#define pb push_back 
#define len(x) (ll)x.size()
#define fileread(file) ifstream fin; fin.open((string)file + ".in"); ofstream fout; fout.open((string)file + ".out")
#define NL "\n"
#define INF 1000000000000000000
#define inf 1000000001
#define VTS(v) ([](auto&& c){ cout << "["; for (auto gaiohgawoihaw = begin(c); gaiohgawoihaw != end(c); ++gaiohgawoihaw) cout << (gaiohgawoihaw != begin(c) ? ", " : "") << *gaiohgawoihaw; cout << "]\n"; })(v) // only for 1D arrays


#include <bits/stdc++.h>
using namespace std;

struct Cow {
    ll dist = inf;
    ll x, y;
    char dir;
    bool moving = true;
};

struct Block {
    ll time;
    ll blocker;
    ll blocked;
};

// returns time to collision, which cows collide
pair<ll, int> time_to_collide(Cow &north_cow, Cow &east_cow) { //
    if (north_cow.y >= east_cow.y || east_cow.x >= north_cow.x) { // if cows are out of range of each other 
        return {inf, -1};
    }

    if (east_cow.y - north_cow.y > north_cow.x - east_cow.x) { // North cow collides with path of east
        return {east_cow.y - north_cow.y, 0}; 
    }

    if (north_cow.x - east_cow.x > east_cow.y - north_cow.y) { // East cow collides with path of north
        return {north_cow.x - east_cow.x, 1}; 
    }

    return {inf, -1}; // Both cows pass each other

}

bool check_collision(Block &check, vector<Cow> &cows) {
    return (cows[check.blocker].dir == 'N' 
    && cows[check.blocked].y - cows[check.blocker].y <= cows[check.blocker].dist) ||
    (cows[check.blocker].dir == 'E' 
    && cows[check.blocked].x - cows[check.blocker].x <= cows[check.blocker].dist);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    // Inputs
    ll N; cin >> N;
    vector<Cow> cows;
    for (ll i  = 0; i < N; i++) {
        Cow c; cin >> c.dir >> c.x >> c.y;
        cows.pb(c); 
    }

    // Naively find every blockage that will occur
    vector<Block> blockOrder;
    for (ll a = 0; a < N; a++) {
        for (ll b = 0; b < N; b++) {
            
            if (cows[a].dir == 'N' && cows[b].dir == 'E') {
                auto [time, cow] = time_to_collide(cows[a], cows[b]);
                
                switch (cow) {
                    case 0: {
                        Block bk; bk.time = time; bk.blocker = b; bk.blocked = a; 
                        blockOrder.pb(bk);
                        break;
                    }
                    case 1: {
                        Block bk; bk.time = time; bk.blocker = a; bk.blocked = b; 
                        blockOrder.pb(bk);
                        break;
                    }
                }
            }
        }
    }

    // Sort collision times 
    sort(blockOrder.begin(), blockOrder.end(), [](auto &x, auto &y) {return x.time < y.time;});


    // Simulate collisions 
    for (Block bk : blockOrder) {
        if (cows[bk.blocker].moving && cows[bk.blocked].moving) {
            cows[bk.blocked].dist = bk.time;
            cows[bk.blocked].moving = false;
        }
        else if (!cows[bk.blocker].moving && cows[bk.blocked].moving && check_collision(bk, cows)) {
            cows[bk.blocked].dist = bk.time;
            cows[bk.blocked].moving = false;
        }
    }

    for (Cow &c : cows) {
        if (c.dist >= inf) {
            cout << "Infinity" << NL;
        }
        else {
            cout << c.dist << NL;
        }
    }

}