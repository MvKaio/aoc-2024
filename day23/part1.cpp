#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
	string s;
	map<string, int> id;

	vector<string> labels;
	auto get = [&] (string u) {
		if (id.count(u)) return id[u];
		int sz = id.size();
		labels.push_back(u);
		return id[u] = sz;
	};

	vector<pair<int, int>> edges;
	while (getline(cin, s)) {
		string a = s.substr(0, 2);
		string b = s.substr(3, 2);

		edges.emplace_back(get(a), get(b));
	}

	int n = labels.size();
	sort(edges.begin(), edges.end());

	auto has = [&] (int a, int b) {
		if (binary_search(edges.begin(), edges.end(), pair<int, int>{a, b})) return true;
		return binary_search(edges.begin(), edges.end(), pair<int, int>{b, a});
	};

	int ans = 0;
	for (int i = 0; i < n; i++) {
	for (int j = i; j < n; j++) {
		if (!has(i, j)) continue;
	for (int k = j; k < n; k++) {
		if (!has(i, k)) continue;
		if (!has(j, k)) continue;
		bool starts_with_t = false;

		starts_with_t |= labels[i][0] == 't';
		starts_with_t |= labels[j][0] == 't';
		starts_with_t |= labels[k][0] == 't';

		ans += starts_with_t;
	}
	}
	}

	cout << n << endl;
	cout << labels[0] << endl;
	cout << ans << endl;
}
