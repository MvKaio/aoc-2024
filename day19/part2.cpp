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
  const int N = 71;
  vector<pair<int, int>> bytes;

  string s;
  while (getline(cin, s)) {
    int x = stoi(split(s, ',')[0]);
    int y = stoi(split(s, ',')[1]);
    bytes.push_back({x, y});
  }

  vector<int> dx = {0, 1, 0, -1};
  vector<int> dy = {1, 0, -1, 0};

  auto check = [&](int qt) {
    vector grid(N, vector<int>(N, 0));
    for (int i = 0; i < qt; i++) {
      auto [x, y] = bytes[i];
      grid[x][y] = 1;
    }

    vector dist(N, vector<int>(N, N * N));
    queue<pair<int, int>> q;
    dist[0][0] = 0;
    q.push({0, 0});
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N)
          continue;
        if (grid[nx][ny] == 1)
          continue;
        if (dist[nx][ny] > dist[x][y] + 1) {
          dist[nx][ny] = dist[x][y] + 1;
          q.push({nx, ny});
        }
      }
    }
    return dist[N - 1][N - 1] == N*N;
  };

  int lo = 1, hi = bytes.size();
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    if (check(mid)) hi = mid;
    else lo = mid + 1;
  }

  cout << bytes[lo - 1].first << " " << bytes[lo - 1].second << endl;
}
