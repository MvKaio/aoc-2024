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
  string s;
  getline(cin, s);

  vector<string> grid;
  ll ans = 0;
  while (getline(cin, s)) {
    grid.push_back(s);
  }

  int n = grid.size();
  int m = grid[0].size();

  vector<int> dx = {-1, 0, 1, 0};
  vector<int> dy = {0, 1, 0, -1};

  pair<int, int> start, end;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'S') {
        start = {i, j};
      } else if (grid[i][j] == 'E') {
        end = {i, j};
      }
    }
  }

  auto bfs = [&] () {
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    q.push(start);
    dist[start.first][start.second] = 0;
    while (!q.empty()) {
      auto [i, j] = q.front();
      q.pop();
      for (int k = 0; k < 4; k++) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
        if (grid[ni][nj] == '#') continue;
        if (dist[ni][nj] != -1) continue;
        dist[ni][nj] = dist[i][j] + 1;
        q.push({ni, nj});
      }
    }
    return dist[end.first][end.second];
  };
  int d = bfs();

  for (int bi = 0; bi < n; bi++) {
    for (int bj = 0; bj < m; bj++) if (grid[bi][bj] == '#') {
      grid[bi][bj] = '.';
      int cur = bfs();
      if (cur != -1 && cur <= d - 100) {
        ans++;
      }
      grid[bi][bj] = '#';
    }
  }

  cout << ans << endl;
}
