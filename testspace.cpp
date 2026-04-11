#include <iostream>
using namespace std;
#define MAX 1000

int tree[MAX] = {0};  // To store segment tree
int lazy[MAX] = {0};  // To store pending updates

void updateRangeUtil(int si, int ss, int se, int us, int ue, int diff) {
    if (lazy[si] != 0) {

        tree[si] += (se-ss+1)*lazy[si];

        if (ss != se) {
            lazy[si*2 + 1]   += lazy[si];
            lazy[si*2 + 2]   += lazy[si];
        }
        lazy[si] = 0;
    }

    if (ss>se || ss>ue || se<us) return;

    if (ss>=us && se<=ue) {
        tree[si] += (se-ss+1)*diff;

        if (ss != se) {
            lazy[si*2 + 1]   += diff;
            lazy[si*2 + 2]   += diff;
        }
        return;
    }


    int mid = (ss+se)/2;
    updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
    updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);

    tree[si] = tree[si*2+1] + tree[si*2+2];
}

int getSumUtil(int ss, int se, int qs, int qe, int si) {
    if (lazy[si] != 0) {
        tree[si] += (se-ss+1)*lazy[si];
        if (ss != se) {
            lazy[si*2+1] += lazy[si];
            lazy[si*2+2] += lazy[si];
        }

        lazy[si] = 0;
    }

    if (ss>se || ss>qe || se<qs) return 0;

    if (ss>=qs && se<=qe)
        return tree[si];

    int mid = (ss + se)/2;
    return getSumUtil(ss, mid, qs, qe, 2*si+1) +
           getSumUtil(mid+1, se, qs, qe, 2*si+2);
}