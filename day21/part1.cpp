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

const int INF = 0x3f3f3f3f;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
string moves = ">v<^";

int main() {
  string s;

  vector<string> numeric = {
    "789",
    "456",
    "123",
    " 0A"
  };

  vector<string> directional = {
    " ^A",
    "<v>",
  };

  auto get_pos = [&] (int x, int y) {
    return x * 3 + y;
  };

  auto next_pos = [&] (int pos, char c) {
    int idx = moves.find(c);
    int x = pos / 3, y = pos % 3;
    int nx = x + dx[idx], ny = y + dy[idx];
    return get_pos(nx, ny);
  };

  auto invalid = [&] (int pos, char c, bool num=false) {
    int idx = moves.find(c);
    int x = pos / 3, y = pos % 3;
    int n = num ? 4 : 2;

    x += dx[idx], y += dy[idx];
    if (x < 0 || x >= n || y < 0 || y >= 3) return true;

    if (num) {
      return numeric[x][y] == ' ';
    } else {
      return directional[x][y] == ' ';
    }
  };
  auto print_state = [&] (int i, array<int, 3> id) {
    cout << "State " << i << ": ";
    for (int j = 0; j < 3; j++) {
      int x = id[j] / 3, y = id[j] % 3;
      cout << "(" << x << ", " << y << ") ";
    }
    cout << endl;
  };


  auto next_state = [&] (array<int, 3> id, char c) -> pair<array<int, 3>, char> {
    int idx = moves.find(c);
    if (idx != string::npos) {
      if (invalid(id[0], c)) return {id, ' '};
      id[0] = next_pos(id[0], c);
      return {id, ' '};
    } else {
      int x = id[0] / 3, y = id[0] % 3;
      c = directional[x][y];
      if (c == ' ') return {id, ' '};

      idx = moves.find(c);
      if (idx != string::npos) {
        if (invalid(id[1], c)) return {id, ' '};
        id[1] = next_pos(id[1], c);
        return {id, ' '};
      } else {
        x = id[1] / 3, y = id[1] % 3;
        c = directional[x][y];
        if (c == ' ') return {id, ' '};

        idx = moves.find(c);
        if (idx != string::npos) {
          if (invalid(id[2], c, true)) return {id, ' '};
          id[2] = next_pos(id[2], c);
          return {id, ' '};
        } else {
          x = id[2] / 3, y = id[2] % 3;
          c = numeric[x][y];
          if (c == ' ') return {id, ' '};

          return {id, c};
        }
      }
    }
  };

  ll ans = 0;
  for (int it = 0; it < 5; it++) {
    string s; cin >> s;
    int n = s.size();

    array<int, 3> id;
    id[0] = get_pos(0, 2);
    id[1] = get_pos(0, 2);
    id[2] = get_pos(3, 2);

    vector dist(n + 1, vector(6, vector(6, vector(12, INF))));
    dist[0][id[0]][id[1]][id[2]] = 0;
    using T = pair<int, array<int, 3>>;
    queue<T> q;
    q.push({0, id});
    while (q.size()) {
      auto [i, pos] = q.front(); q.pop();
      int d = dist[i][pos[0]][pos[1]][pos[2]];
      if (i == n) continue;

      for (auto c : "^><vA") {
        auto [nxt, chr] = next_state(pos, c);
        if (chr != ' ') {
          if (chr == s[i]) {
            if (dist[i + 1][nxt[0]][nxt[1]][nxt[2]] == INF) {
              dist[i + 1][nxt[0]][nxt[1]][nxt[2]] = d + 1;
              q.push({i + 1, nxt});
            }
          }
        } else if (nxt != pos) {
          if (dist[i][nxt[0]][nxt[1]][nxt[2]] == INF) {
            dist[i][nxt[0]][nxt[1]][nxt[2]] = d + 1;
            q.push({i, nxt});
          }
        }
      }
    }

    int best = INF;
    array<int, 3> ans_pos;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 12; k++) {
          if (dist[n][i][j][k] < best) {
            best = dist[n][i][j][k];
            ans_pos = {i, j, k};
          }
        }
      }
    }

    int num = 0;
    for (int i = 0; i < n; i++) {
      if (isdigit(s[i])) num = num * 10 + (s[i] - '0');
    }

    ans += best * num;
  }

  cout << ans << endl;
}
