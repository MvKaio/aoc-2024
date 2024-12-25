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

  vector<string> grid;
  while (getline(cin, s)) {
    grid.push_back(s);
  }

  int n = grid.size();
  int m = grid[0].size();

  int dx[] = {-1, 0, 1, 0};
  int dy[] = {0, 1, 0, -1};

  using T = tuple<int, int, int>;
  priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
  vector dist(n, vector(m, vector(4, INT_MAX)));

  pair<int, int> pos, target;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'S') {
        pos = {i, j};
      }
      if (grid[i][j] == 'E') {
        target = {i, j};
      }
    }
  }
  auto dijkstra = [&]() {
    while (!pq.empty()) {
      auto [d, t] = pq.top();
      pq.pop();

      auto [x, y, k] = t;
      if (dist[x][y][k] < d) {
        continue;
      }

      int nk = (k + 1) % 4;
      if (dist[x][y][nk] > d + 1000) {
        dist[x][y][nk] = d + 1000;
        pq.emplace(d + 1000, T{x, y, nk});
      }

      nk = (k + 3) % 4;
      if (dist[x][y][nk] > d + 1000) {
        dist[x][y][nk] = d + 1000;
        pq.emplace(d + 1000, T{x, y, nk});
      }

      int nx = x + dx[k];
      int ny = y + dy[k];

      if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
        continue;
      }

      if (grid[nx][ny] == '#') {
        continue;
      }

      if (dist[nx][ny][k] > d + 1) {
        dist[nx][ny][k] = d + 1;
        pq.emplace(d + 1, T{nx, ny, k});
      }
    }
  };

  dist[pos.first][pos.second][1] = 0;
  pq.emplace(0, T{pos.first, pos.second, 1});
  dijkstra();

  auto s_dist = dist;
  dist.assign(n, vector(m, vector(4, INT_MAX)));
  for (int i = 0; i < 4; i++) {
    dist[target.first][target.second][i] = 0;
    pq.emplace(0, T{target.first, target.second, i});
  }
  dijkstra();
  auto t_dist = dist;

  ll best = t_dist[pos.first][pos.second][3];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < 4; k++) {
        int nk = (k + 2) % 4;
        if (ll(s_dist[i][j][k]) + t_dist[i][j][nk] == best) {
          ans++;
          break;
        }
      }
    }
  }


  cout << ans << endl;
}
