#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
  string s;
  map<string, int> id;

  vector<string> labels;
  auto get = [&](string u) {
    if (id.count(u))
      return id[u];
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
  vector<int> deg(n);
  for (auto [a, b] : edges)
    deg[a]++, deg[b]++;

  sort(edges.begin(), edges.end());

  auto has = [&](int a, int b) {
    if (binary_search(edges.begin(), edges.end(), pair<int, int>{a, b}))
      return true;
    return binary_search(edges.begin(), edges.end(), pair<int, int>{b, a});
  };

  int ans = 0;
  string answer;
  vector<int> cur;
  int mn_deg = n;
  auto go = [&](auto &&self, int i) -> void {
    if (i == n) {
	  if (cur.size() > ans) {
		ans = cur.size();
		vector<string> tokens;
		for (auto u : cur)
		  tokens.push_back(labels[u]);
		sort(tokens.begin(), tokens.end());
		answer.clear();
		for (auto u : tokens) {
		  answer += u;
		  answer += ',';
		}
		answer.pop_back();
	  }

      return;
    }
    if (1 + mn_deg < ans)
      return;
    self(self, i + 1);
    bool can_add = true;
    for (auto u : cur) {
      if (!has(u, i)) {
        can_add = false;
        break;
      }
    }

    if (can_add) {
      cur.push_back(i);
      int old = mn_deg;
      mn_deg = min(mn_deg, deg[i]);
      self(self, i + 1);
      cur.pop_back();
      mn_deg = old;
    }
  };
  go(go, 0);

  cout << ans << endl;
  cout << answer << endl;
}
