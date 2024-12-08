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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool ok = false;
            for (auto [_, v] : mp) {
                for (int i1 = 0; !ok && i1 < v.size(); i1++) {
                    for (int j1 = 0; !ok && j1 < v.size(); j1++) if (i1 != j1) {
                        int dx1 = v[i1].first - i, dy1 = v[i1].second - j;
                        int dx2 = v[j1].first - i, dy2 = v[j1].second - j;
                        if (2*dx1 == dx2 && 2*dy1 == dy2) {
                            ok = true;
                        }
                    }
                }
                if (ok) break;
            }
            ans += ok;
        }
    }


    cout << ans << endl;
}
