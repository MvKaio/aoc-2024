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
    ll ans = 0;

    vector<string> lines;
    while (getline(cin, s)) {
        lines.push_back(s);
    }

    auto grid = lines;
    int n = grid.size(), m = grid[0].size();

    map<char, vector<pair<int, int>>> mp;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if (grid[i][j] != '.') {
            mp[grid[i][j]].push_back({i, j});
        }
    }

    auto dist = [&] (int i, int j, int i1, int j1) {
        return abs(i - i1) + abs(j - j1);
    };

    vector<vector<int>> has(n, vector<int>(m, false));
    for (auto [_, v] : mp) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v.size(); j++) if (i != j) {
                auto [x1, y1] = v[i];
                auto [x2, y2] = v[j];

                int dx = x2 - x1, dy = y2 - y1;
                int g = __gcd(abs(dx), abs(dy));
                dx /= g;
                dy /= g;

                int x = x1;
                int y = y1;
                while (x >= 0 && x < n && y >= 0 && y < m) {
                    has[x][y] = true;
                    x += dx;
                    y += dy;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans += has[i][j];
        }
        cout << endl;
    }


    cout << ans << endl;
}
