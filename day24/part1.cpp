#include <bits/stdc++.h>
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
  map<string, int> value;

  enum Op {
    AND, OR, XOR
  };

	vector<tuple<int, int, Op, int>> edges;
	while (getline(cin, s)) {
    if (s.empty()) continue;
    if (s[3] == ':') {
      string name = s.substr(0, 3);
      get(name);
      value[name] = s[5] - '0';
    } else {
      stringstream ss(s);
      string a, op, b, out;
      ss >> a >> op >> b >> out >> out;

      int u = get(a);
      int v = get(b);
      int to = get(out);
      Op o;
      if (op == "AND") o = AND;
      if (op == "OR") o = OR;
      if (op == "XOR") o = XOR;

      edges.emplace_back(u, v, o, to);
    }
	}

  int n = labels.size();
  vector<vector<tuple<int, int, Op>>> adj(n);
  for (auto [u, v, o, to] : edges) {
    adj[to].emplace_back(u, v, o);
  }

  auto eval = [&] (auto&& self, int u) -> int {
    if (value.count(labels[u])) return value[labels[u]];

    int ans = 0;
    for (auto [v, w, o] : adj[u]) {
      int x = self(self, v);
      int y = self(self, w);
      if (o == AND) ans = x & y;
      if (o == OR) ans = x | y;
      if (o == XOR) ans = x ^ y;
    }

    return value[labels[u]] = ans;
  };

  map<string, int> ret;
  for (int i = 0; i < n; i++) {
    if (labels[i][0] == 'z') {
      ret[labels[i]] = eval(eval, i);
    }
  }

  string ans;
  for (auto [k, v] : ret) {
    ans += char(v + '0');
  }

  reverse(ans.begin(), ans.end());
  long long val = 0;
  for (int i = 0; i < ans.size(); i++) {
    val = val * 2 + (ans[i] - '0');
  }

  cout << val << endl;
}
