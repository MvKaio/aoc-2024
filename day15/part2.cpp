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

  string moves;
  vector<string> grid;
  while (getline(cin, s)) {
    if (s.empty()) {
      break;
    }

    grid.push_back(s);
  }
  getline(cin, moves);

  vector<string> ngrid;
  for (auto row : grid) {
    string nrow;
    for (auto c : row) {
      if (c == '@') {
        nrow += '@';
        nrow += '.';
      } else if (c == 'O') {
        nrow += '[';
        nrow += ']';
      } else {
        nrow += c;
        nrow += c;
      }
    }
    ngrid.push_back(nrow);
  }
  grid = ngrid;

  pair<int, int> pos;
  int n = grid.size();
  int m = grid[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '@') {
        pos = {i, j};
      }
    }
  }

  vector<pair<int, int>> mv = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
  };
  string dirs = "^>v<";

  for (auto c : moves) {
    int idx = dirs.find(c);
    if (idx == string::npos) {
      continue;
    }

    int x = pos.first + mv[idx].first;
    int y = pos.second + mv[idx].second;

    if (grid[x][y] == '#') {
      continue;
    } else if (grid[x][y] == '.') {
      grid[x][y] = '@';
      grid[pos.first][pos.second] = '.';
      pos = {x, y};
      continue;
    }

    if (mv[idx].second != 0) {
      while (y >= 0 && y < m && (grid[x][y] == '[' || grid[x][y] == ']')) {
        y += mv[idx].second;
      }
      if (y >= 0 && y < m && grid[x][y] == '.') {
        while (y != pos.second) {
          swap(grid[x][y], grid[x][y - mv[idx].second]);
          y -= mv[idx].second;
        }
        pos.second += mv[idx].second;
      }
    } else {
      using T = pair<int, int>;
      queue<T> q;
      set<T> inq;
      vector<T> visited;

      auto test = [&] (int i, int j) {
        if (i < 0 || i >= n) return;
        if (grid[i][j] == '[') {
          if (!inq.count({i, j})) {
            q.push({i, j});
            inq.insert({i, j});
          }
        } else if (grid[i][j] == ']') {
          if (!inq.count({i, j - 1})) {
            q.push({i, j - 1});
            inq.insert({i, j - 1});
          }
        }
      };
      test(x, y);

      int dx = mv[idx].first;
      while (q.size()) {
        auto [x, y] = q.front(); q.pop();
        visited.push_back({x, y});
        if (x + dx < 0 || x + dx >= n) continue;
        if (grid[x + dx][y] == '#' || grid[x + dx][y + 1] == '#') continue;
        test(x + dx, y);
        test(x + dx, y + 1);
      }

      bool ok = true;
      auto bkp = grid;
      while (visited.size()) {
        auto [x, y] = visited.back(); visited.pop_back();
        if (x + dx < 0 || x + dx >= n) continue;
        ok &= grid[x + dx][y] == '.' && grid[x + dx][y + 1] == '.';
        if (grid[x + dx][y] == '.' && grid[x + dx][y + 1] == '.') {
          swap(grid[x][y], grid[x + dx][y]);
          swap(grid[x][y + 1], grid[x + dx][y + 1]);
        }
      }
      if (!ok) {
        grid = bkp;
      }

      x = pos.first + mv[idx].first;
      y = pos.second + mv[idx].second;

      if (grid[x][y] == '.') {
        grid[x][y] = '@';
        grid[pos.first][pos.second] = '.';
        pos = {x, y};
      }
    }
  }

  for (auto row : grid) {
    cout << row << endl;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '[') {
        ans += 100 * i + j;
      }
    }
  }

  cout << ans << endl;
}
