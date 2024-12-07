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

int main() {
    string s;
    ll ans = 0;

    vector<string> lines;
    while (getline(cin, s)) {
        lines.push_back(s);

        vector<string> tokens = split(s, ':');

        ll tot = stoll(tokens[0]);

        stringstream ss(tokens[1]);
        vector<ll> v;
        ll x;
        while (ss >> x) {
            v.push_back(x);
        }

        ll n = v.size();
        for (ll i = 0; i < (1 << (n - 1)); i++) {
            ll val = v[0];
            for (ll j = 1; j < n; j++) {
                if (i >> (j - 1) & 1) {
                    val += v[j];
                } else {
                    val *= v[j];
                }
            }

            if (val == tot) {
                ans += tot;
                break;
            }
        }

    }

    cout << ans << endl;
}
