#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<string> split(string s, char token) {
    stringstream ss(s);
    vector<string> res;
    while (getline(ss, s, token)) res.push_back(s);
    return res;
}

int main() {
    string s;
    ll ans = 0;

    set<pair<int, int>> bad;

    vector<string> lines;
    while (getline(cin, s)) {
        stringstream ss(s);
        lines.push_back(s);

        if (s.find('|') != string::npos) {
            int x, y;
            char z;
            ss >> x >> z >> y;
            bad.emplace(y, x);
        } else {
            vector<int> line;
            auto v = split(s, ',');
            for (auto x : v) line.push_back(stoi(x));

            bool ok = true;
            int n = line.size();
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                    if (bad.count({line[i], line[j]})) ok = false;

            if (ok && n > 0)
                ans += line[n/2];
        }
    }


    cout << ans << endl;
}
