#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int num_cows;
	cin >> num_cows;

	vector<int> initial_order(num_cows);

	for (int i = 0; i < num_cows; i++) { cin >> initial_order[i]; }

	vector<int> ideal_order(num_cows);

	for (int i = 0; i < num_cows; i++) { cin >> ideal_order[i]; }

	// Map a cow's species to an array of minimum distances to the edge for that species
	// in the ideal ordering
	unordered_map<int, vector<int>> edge_arrays;

	for (int i = 0; i < num_cows; i++) {
		int min_distance_to_edge = min(i + 1, num_cows - i);

		// If an array doesn't already exist for a cow species, create a new array for
		// that species
		if (edge_arrays.count(ideal_order[i]) == 0) {
			vector<int> new_edge_array = {min_distance_to_edge};
			edge_arrays.insert(make_pair(ideal_order[i], new_edge_array));
		}

		else {
			edge_arrays.at(ideal_order[i]).push_back(min_distance_to_edge);
		}
	}

	// Map a cow's species to a prefix array that sums the contributions limited by
	// d_desirable
	unordered_map<int, vector<long long>> prefix_arrays;

	// iterating by reference is important for sorting
	for (auto &[species, edge_array] : edge_arrays) {
		// Sort edge arrays as we iterate so we can binary search over it later
		sort(edge_array.begin(), edge_array.end());

		vector<long long> new_prefix_array = {0};
		for (int distance : edge_array) {
			new_prefix_array.push_back(new_prefix_array.back() + distance);
		}

		prefix_arrays.insert(make_pair(species, new_prefix_array));
	}

	long long total_contributions = 0;

	for (long long i = 0; i < num_cows; i++) {
		int species = initial_order[i];

		// Catches edge case where a cow species exists in the initial ordering but not
		// in the ideal ordering
		if (edge_arrays.count(species) == 0) { continue; }

		// Scenario 1 computation
		long long min_distance_to_edge = min(i + 1, num_cows - i);
		vector<int> &edge_array =
		    edge_arrays.at(species);  // reference is important to save time
		int index =
		    upper_bound(edge_array.begin(), edge_array.end(), min_distance_to_edge) -
		    edge_array.begin();  // Returns breakoff point where d_cow < d_desirable

		total_contributions += prefix_arrays.at(
		    species)[index];  // Adds contributions limited by d_desirable
		total_contributions +=
		    (min_distance_to_edge) * ((long long)edge_array.size() -
		                              index);  // Adds contributions limited by d_cow

		// Scenario 2 computation
		if (initial_order[i] == ideal_order[i]) {
			total_contributions +=
			    ((i * (i + 1)) / 2) + ((num_cows - i - 1) * (num_cows - i) / 2);
		}
	}

	cout << total_contributions << endl;
}