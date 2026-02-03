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
    ll t, do_output;
    cin >> t >> do_output;
    
    while (t--) {
        ll N; cin >> N;
        
        string left_claim, right_claim;
        cin >> left_claim >> right_claim;
        v<ll> JJ, JN, NJ, NN;
        For(i, N) {
            if (left_claim[i] == 'J' && right_claim[i] == 'J') JJ.pb(i);
            else if (left_claim[i] == 'J' && right_claim[i] == 'N') JN.pb(i);
            else if (left_claim[i] == 'N' && right_claim[i] == 'J') NJ.pb(i);
            else NN.pb(i);
        }

        ll count_left_J = JJ.size() + JN.size();
        ll count_left_N = NJ.size() + NN.size();
        ll count_right_J = JJ.size() + NJ.size();
        ll count_right_N = JN.size() + NN.size();
        
        if (count_left_J != count_right_J || count_left_N != count_right_N) {
            cout << "NO" << nl;
        }
    
        else if (count_right_N % 2 != 0) {
            cout << "NO" << nl;
        }
        
        else if (count_right_J > 0 && count_right_N > 0 && JN.empty() && NJ.empty()) {
            cout << "NO" << nl;
        }
    
        else {
            cout << "YES" << nl;
            if (do_output == 1) {
                v<ll> path;
                
                if (count_right_N == 0) {
                    For(i, N) {
                        path.pb(i);
                    }
                }
                else if (count_right_J == 0) {
                    For(i, N) {
                        path.pb(i);
                    }
                }
                else {
                    ll num_bridges = JN.size();
                    ll nn_index = 0; 
                    ll jj_index = 0;
                    
                    For(b, num_bridges) {
                        path.pb(JN[b]);
                        ll nn_count = NN.size() / num_bridges + (b < (ll)(NN.size() % num_bridges) ? 1 : 0);
                        For(i, nn_count) {
                            path.pb(NN[nn_index++]);
                        }

                        path.pb(NJ[b]);
                        
                        ll jj_count = JJ.size() / num_bridges + (b < (ll)(JJ.size() % num_bridges) ? 1 : 0);
                        For(i, jj_count) {
                            path.pb(JJ[jj_index++]);
                        }
                    }
                }
                
                cout << path[0] + 1;
                for (ll i = 1; i < N; i++) {
                    cout << ss << (path[i] + 1);
                }
                cout << nl;
                

                v<ll> owner(N);
                owner[path[0]] = 0;
                f0r(i, 1, N) {
                    owner[path[i]] = owner[path[i-1]] ^ (right_claim[path[i-1]] == 'N' ? 1 : 0);
                }
                
                For(i, N) {
                    cout << (owner[path[i]] == 0 ? 'J' : 'N');
                }
                cout << nl;
            }
        }
    }
}