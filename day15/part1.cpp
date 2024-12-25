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
    }

    if (grid[x][y] == 'O') {
      while (x > 0 && x < n && y > 0 && y < m && grid[x][y] == 'O') {
        x += mv[idx].first;
        y += mv[idx].second;
      }
      if (x > 0 && x < n && y > 0 && y < m && grid[x][y] == '.') {
        grid[x][y] = 'O';
        grid[pos.first + mv[idx].first][pos.second + mv[idx].second] = '@';
        grid[pos.first][pos.second] = '.';
        pos = {pos.first + mv[idx].first, pos.second + mv[idx].second};
      }
    } else if (grid[x][y] == '.') {
      grid[x][y] = '@';
      grid[pos.first][pos.second] = '.';
      pos = {x, y};
    }

  }

  for (auto row : grid) {
    cout << row << endl;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'O') {
        ans += 100 * i + j;
      }
    }
  }

  cout << ans << endl;
}
