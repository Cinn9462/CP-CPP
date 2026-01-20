#include <bits/stdc++.h>
using namespace std;

vector<long long> psum(const vector<int> &arr) {
	vector<long long> psum = {0};
	for (int i = 0; i < arr.size(); i++) {
        psum.push_back(psum.back() + arr[i]);
    }
	// or partial_sum(begin(a),end(a),begin(psum)+1);
	return psum;
}

int main() {
	int N, Q;
	cin >> N >> Q;
	vector<int> nums(N);
	for (int i = 0; i < N; i++) {
        cin >> nums[i];
    }
	vector<long long> prefix_arr = psum(nums);
	for (int i = 0; i < Q; ++i) {
		int l, r;
		cin >> l >> r;
		cout << prefix_arr[r] - prefix_arr[l - 1] << "\n";
	}
}