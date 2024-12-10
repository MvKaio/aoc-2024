#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    string s;
    ll ans = 0;

    vector<string> grid;
    while (getline(cin, s)) {
        grid.push_back(s);
    }

    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (grid[i][j] == '0') {
            queue<pair<int, int>> q;
            vector vis(n, vector<bool>(m, false));
            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};
            q.push({i, j});
            vis[i][j] = true;

            vector<pair<int, int>> path;

            vector score(n, vector<int>(m, 0ll));
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                path.emplace_back(x, y);

                if (grid[x][y] == '9') {
                    score[x][y] = 1;
                }
                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny] && grid[nx][ny] == grid[x][y] + 1) {
                        vis[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }

            reverse(path.begin(), path.end());
            for (auto [x, y] : path) {
                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == grid[x][y] + 1) {
                        score[x][y] += score[nx][ny];
                    }
                }
            }

            ans += score[i][j];
        }
    }


    cout << ans << endl;
}
