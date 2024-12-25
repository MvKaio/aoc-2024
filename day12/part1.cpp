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
            int acc = 0;
            vector vis(n, vector<bool>(m, false));
            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};
            q.push({i, j});
            vis[i][j] = true;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();

                if (grid[x][y] == '9') {
                    acc++;
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

            ans += acc;
        }
    }


    cout << ans << endl;
}
