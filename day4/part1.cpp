#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    string s;
    ll ans = 0;

    vector<string> grid;

    while (getline(cin, s)) {
        stringstream ss(s);
        grid.push_back(s);
    }

    string x = "XMAS", revx = "SAMX";

    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 4 <= m; j++) {
            if (grid[i].substr(j, 4) == x) ans++;
            if (grid[i].substr(j, 4) == revx) ans++;
        }
    }
    for (int j = 0; j < m; j++) {
        for (int i = 0; i + 4 <= n; i++) {
            string s = "";
            for (int k = 0; k < 4; k++) s += grid[i + k][j];
            if (s == x) ans++;
            if (s == revx) ans++;
        }
    }
    for (int i = 0; i + 4 <= n; i++) {
        for (int j = 0; j + 4 <= m; j++) {
            string s = "";
            for (int k = 0; k < 4; k++) s += grid[i + k][j + k];
            if (s == x) ans++;
            if (s == revx) ans++;
        }
    }
    for (int i = 0; i + 4 <= n; i++) {
        for (int j = m - 1; j - 3 >= 0; j--) {
            string s = "";
            for (int k = 0; k < 4; k++) s += grid[i + k][j - k];
            if (s == x) ans++;
            if (s == revx) ans++;
        }
    }

    cout << ans << endl;
}
