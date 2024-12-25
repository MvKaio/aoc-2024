#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<string> split(const string &s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

string trim(string s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !isspace(ch);
    }));

    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), s.end());

    return s;
}

int main() {
  ll ans = 0;
  string s;

  const int N = 101;
  const int M = 103;

  vector<array<int, 2>> ps, vs;
  for (int it = 0; it < 500; it++) {
    getline(cin, s);
    auto tokens = split(s, ' ');
    array<int, 2> p, v;
    for (auto &s : tokens)
      s = split(s, '=')[1];
    p[0] = stoi(split(tokens[0], ',')[0]);
    p[1] = stoi(split(tokens[0], ',')[1]);

    v[0] = stoi(split(tokens[1], ',')[0]);
    v[1] = stoi(split(tokens[1], ',')[1]);

    ps.push_back(p);
    vs.push_back(v);
  }

  for (int i = 1; ; i++) {
    vector grid(N, string(M, '.'));
    for (int j = 0; j < ps.size(); j++) {
      auto [p, v] = make_pair(ps[j], vs[j]);
      auto f = p;
      f[0] += v[0] * i;
      f[0] = (f[0] % N + N) % N;
      f[1] += v[1] * i;
      f[1] = (f[1] % M + M) % M;
      grid[f[0]][f[1]] = '#';
    }

    int factor = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (grid[i][j] != '#') continue;

        for (auto [i1, j1] : vector<pair<int, int>> {
            {i - 1, j - 1}, {i - 1, j}, {i - 1, j + 1},
            {i, j - 1}, {i, j + 1},
            {i + 1, j - 1}, {i + 1, j}, {i + 1, j + 1}
          }) {
          if (i1 < 0 || i1 >= N || j1 < 0 || j1 >= M) {
            continue;
          }
          if (grid[i1][j1] == '#') {
            factor++;
          }
        }
      }
    }

    if (factor > 500) {
      for (auto s : grid) cout << s << endl;
      cout << "grid " << i << endl;
      break;
    }
  }

  cout << ans << endl;
}
