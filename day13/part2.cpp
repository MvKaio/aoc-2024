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

    const ll add = 10000000000000;

    vector<string> a;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        a.push_back(s);

        string t1 = s, t2, p;
        getline(cin, t2);
        getline(cin, p);

        t1 = split(t1, ':')[1];
        ll a1 = stoi(split(split(t1, ',')[0],'+')[1]);
        ll a2 = stoi(split(split(t1, ',')[1],'+')[1]);

        t2 = split(t2, ':')[1];
        ll b1 = stoi(split(split(t2, ',')[0],'+')[1]);
        ll b2 = stoi(split(split(t2, ',')[1],'+')[1]);

        p = split(p, ':')[1];
        ll c1 = add + stoi(split(split(p, ',')[0],'=')[1]);
        ll c2 = add + stoi(split(split(p, ',')[1],'=')[1]);

        ll qt_x = (c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
        ll qt_y = (c1 * a2 - c2 * a1) / (b1 * a2 - b2 * a1);

        if (qt_x < 0 || qt_y < 0) {
            continue;
        }
        if (qt_x * a1 + qt_y * b1 != c1 || qt_x * a2 + qt_y * b2 != c2) {
            continue;
        }

        ans += qt_x * 3 + qt_y;
    }

    cout << ans << endl;
}
