#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
  map<string, int> value;

  enum Op { AND, OR, XOR };

  vector<tuple<int, int, Op, int>> edges;
  while (getline(cin, s)) {
    if (s.empty())
      continue;
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
      if (op == "AND")
        o = AND;
      if (op == "OR")
        o = OR;
      if (op == "XOR")
        o = XOR;

      edges.emplace_back(u, v, o, to);
    }
  }

  int n = labels.size();
  vector<tuple<int, int, Op>> gate(n);
  vector<bool> is_input(n, true);
  for (int i = 0; i < n; i++) {
    is_input[i] = labels[i][0] == 'x' || labels[i][0] == 'y';
  }
  for (auto [u, v, o, to] : edges) {
    gate[to] = {u, v, o};
  }

  auto format = [&] (char tp, int i) {
    string name = to_string(i);
    if (name.size() == 1)
      name = string(1, tp) + "0" + name;
    else
      name = tp + name;
    return name;
  };

  const int N = 44;
  vector<int> used;
  auto run_test = [&] (ll x, ll y) {
    value = map<string, int>();
    for (int i = 0; i < N; i++) {
      value[format('x', i)] = (x >> i) & 1;
      value[format('y', i)] = (y >> i) & 1;
    }

    auto eval = [&](auto &&self, int u) -> int {
      if (value.count(labels[u]))
        return value[labels[u]];

      if (is_input[u])
        return value[labels[u]];

      int ans = 0;
      auto [v, w, o] = gate[u];
      int x = self(self, v);
      int y = self(self, w);
      if (o == AND)
        ans = x & y;
      if (o == OR)
        ans = x | y;
      if (o == XOR)
        ans = x ^ y;

      return value[labels[u]] = ans;
    };

    for (int i = 0; i < n; i++) {
      if (labels[i][0] == 'z') {
        eval(eval, i);
      }
    }

    string ans;
    for (auto [k, v] : value) {
      if (k[0] == 'z') ans += char(v + '0');
      if (v != 0) used.push_back(get(k));
    }

    reverse(ans.begin(), ans.end());
    ll z = 0;
    for (int i = 0; i < ans.size(); i++) {
      z = z * 2 + (ans[i] - '0');
    }

    return z;
  };

  auto flip = [&] (int i, int j) {
    swap(gate[i], gate[j]);
  };

  auto test_acyclic = [&]() {
    vector<vector<int>> adj(n);
    for (int to = 0; to < n; to++) {
      if (!is_input[to]) {
        auto [u, v, o] = gate[to];
        adj[to].push_back(u);
        adj[to].push_back(v);
      }
    }

    vector<int> vis(n);
    auto dfs = [&](auto &&self, int u) -> bool {
      vis[u] = 1;
      for (int v : adj[u]) {
        if (vis[v] == 1)
          return false;
        if (vis[v] == 0 && !self(self, v))
          return false;
      }
      vis[u] = 2;
      return true;
    };

    for (int i = 0; i < n; i++) {
      if (vis[i] == 0 && !dfs(dfs, i))
        return false;
    }
    return true;
  };

  flip(get("z11"), get("vkq"));
  flip(get("mmk"), get("z24"));
  flip(get("qdq"), get("pvb"));
  flip(get("hqh"), get("z38"));

  vector<string> flipped = {"z11", "vkq", "mmk", "z24", "qdq", "pvb", "hqh", "z38"};
  sort(flipped.begin(), flipped.end());
  string answer;
  for (string s : flipped) {
    answer += s;
    answer += ',';
  }
  answer.pop_back();
  cout << answer << endl;

  /** Used to look for problematic bits */
  for (int X = 0; X + 5 < N; X++) {
    cout << "X = " << X << endl;
    for (int i = 1; i <= 127; i++) {
      for (int j = 1; j <= 127; j++) {
        ll x = ll(i) << X;
        ll y = ll(j) << X;
        if (x + y != run_test(x, y)) {
          cout << "X = " << X << " i = " << i << " j = " << j << endl;
          cout << "Failed " << x << " " << y << endl;
          return 0;
        }
      }
    }
  }

  /** Used to identify possible gates for the swap */
  const int B = 7;
  for (int i = 1; i <= 31; i++) {
    for (int j = 1; j <= 31; j++) {
      ll x = ll(i) << B;
      ll y = ll(j) << B;
      run_test(x, y);
    }
  }

  auto wrong = used;
  for (int i = B; i < B + 8; i++)
    wrong.push_back(get(format('z', i)));
  sort(wrong.begin(), wrong.end());
  wrong.erase(unique(wrong.begin(), wrong.end()), wrong.end());
  for (int i : wrong) {
    for (int j : wrong) {
      if (i == j || is_input[i] || is_input[j]) continue;
      flip(i, j);
      if (test_acyclic()) {
        bool ok = true;
        for (int i = 1; i <= 31; i++) {
          for (int j = 1; j <= 31; j++) {
            ll x = ll(i) << B;
            ll y = ll(j) << B;
            ok &= x + y == run_test(x, y);
            if (!ok)
              break;
          }
          if (!ok)
            break;
        }
        if (ok) {
          cout << "Found! " << labels[i] << " " << labels[j] << endl;
          return 0;
        }
      }
      flip(i, j);
    }
  }

  return 0;
}
