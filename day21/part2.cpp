#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<string> numeric = {"789", "456", "123", " 0A"};
  vector<string> directional = {" ^A", "<v>"};
  using ll = long long;
  const ll INF = 1e17;
  int dx[] = {0, 1, -1, 0};
  int dy[] = {1, 0, 0, -1};
  string moves = ">v^<";

  auto get_pos = [&] (int x, int y) -> size_t { return x * 3 + y; };
  auto get_loc = [&] (char c, bool num = false) {
    if (num == false) {
      for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
          if (directional[i][j] == c)
            return get_pos(i, j);
    } else {
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
          if (numeric[i][j] == c)
            return get_pos(i, j);
    }
    return string::npos;
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

  // 25 robots + a numerical pad
  const int N = 25 + 1;
  vector dist(N, vector(12, vector(12, INF)));
  for (int lvl = 0; lvl < N; lvl++) {
    bool last_lvl = lvl == N - 1;
    int L = last_lvl ? 12 : 6;
    if (lvl == 0) {
      for (int i = 1; i < L; i++) {
        for (int j = 1; j < L; j++) {
          dist[0][i][j] = abs(i/3 - j/3) + abs(i%3 - j%3);
        }
      }
    } else {
      for (int i = 0; i < L; i++) {
        vector state(6, vector(L, INF));
        using T = pair<int, int>;
        priority_queue<pair<ll, T>, vector<pair<ll, T>>, greater<pair<ll, T>>> pq;
        state[get_loc('A')][i] = 0;
        pq.push({0, {get_loc('A'), i}});
        while (pq.size()) {
          auto [d, u] = pq.top(); pq.pop();
          auto [prv, at] = u;
          if (d > state[prv][at]) continue;
          for (char c : moves) {
            if (invalid(at, c, last_lvl)) continue;
            int nxt = next_pos(at, c);
            int loc = get_loc(c);
            ll step_dist = dist[lvl - 1][prv][loc] + 1;
            if (state[loc][nxt] > state[prv][at] + step_dist) {
              state[loc][nxt] = state[prv][at] + step_dist;
              pq.push({state[loc][nxt], {loc, nxt}});
            }
          }
        }
        for (int j = 0; j < L; j++) {
          for (int prv = 0; prv < 6; prv++) {
            dist[lvl][i][j] = min(dist[lvl][i][j], state[prv][j] + dist[lvl - 1][prv][get_loc('A')]);
          }
        }
      }
    }
  }

  ll ans = 0;
  for (int n_codes = 0; n_codes < 5; n_codes++) {
    string s; cin >> s;
    int num = stoi(s.substr(0, 3));
    ll len = 0;

    int at = get_loc('A', true);
    for (int it = 0; it < 4; it++) {
      char nxt = s[it];
      len += dist[N - 1][at][get_loc(nxt, true)] + 1;
      at = get_loc(nxt, true);
    }

    cout << len << endl;
    ans += num * len;
  }

  cout << ans << endl;
}
