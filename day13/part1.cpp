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

    vector<string> a;
    while (getline(cin, s)) {
        if (s.empty()) continue;
        a.push_back(s);

        string t1 = s, t2, p;
        getline(cin, t2);
        getline(cin, p);

        t1 = split(t1, ':')[1];
        int x1 = stoi(split(split(t1, ',')[0],'+')[1]);
        int y1 = stoi(split(split(t1, ',')[1],'+')[1]);

        t2 = split(t2, ':')[1];
        int x2 = stoi(split(split(t2, ',')[0],'+')[1]);
        int y2 = stoi(split(split(t2, ',')[1],'+')[1]);

        p = split(p, ':')[1];
        int X = stoi(split(split(p, ',')[0],'=')[1]);
        int Y = stoi(split(split(p, ',')[1],'=')[1]);

        for (int i = 0; i <= 100; i++) {
            int lx = X - i * x1;
            int ly = Y - i * y1;
            if (lx % x2 == 0 && ly % y2 == 0 && lx / x2 == ly / y2) {
                ans += 3 * i + lx / x2;
                break;
            }
        }

    }

    cout << ans << endl;
}
