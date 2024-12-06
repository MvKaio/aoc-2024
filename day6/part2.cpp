#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    string s;
    ll ans = 0;

    set<pair<int, int>> bad;

    vector<string> lines;
    while (getline(cin, s)) {
        stringstream ss(s);
        lines.push_back(s);
    }

    int n = lines.size(), m = lines[0].size();
    vector vis(n, vector(m, false));

    pair<int, int> pos;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (lines[i][j] != '.' && lines[i][j] != '#') {
                pos = {i, j};
                break;
            }
        }

    int dir = 0;
    if (lines[pos.first][pos.second] == '^') dir = 0;
    if (lines[pos.first][pos.second] == '>') dir = 1;
    if (lines[pos.first][pos.second] == 'v') dir = 2;
    if (lines[pos.first][pos.second] == '<') dir = 3;

    auto [x, y] = pos;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    auto loops = [&] (int x, int y, int dir) {
        set<tuple<int, int, int>> st;
        while (true) {
            if (st.count({x, y, dir})) {
                return true;
            }
            st.insert({x, y, dir});
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
            if (lines[nx][ny] == '#') {
                dir = (dir + 1) % 4;
                continue;
            }
            x = nx;
            y = ny;
        }
        return false;
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (lines[i][j] != '.') continue;
            lines[i][j] = '#';
            if (loops(x, y, dir)) {
                ans++;
            }
            lines[i][j] = '.';
        }

    cout << ans << endl;
}
