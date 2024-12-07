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

ll pot(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) {
            ans *= a;
        }
        a *= a;
        b >>= 1;
    }
    return ans;
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
        for (ll i = 0; i < pot(3, n); i++) {
            ll val = v[0];
            for (ll j = 1, ops = i; j < n; j++, ops /= 3) {
                if (ops % 3 == 0) {
                    val += v[j];
                } else if (ops % 3 == 1) {
                    val *= v[j];
                } else {
                    val = val * pot(10, to_string(v[j]).size()) + v[j];
                }
                if (val > tot) {
                    break;
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
