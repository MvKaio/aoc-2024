#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    string s;
    ll ans = 0;

    while (getline(cin, s)) {
        stringstream ss(s);

        int n = s.size();
        for (int i = 0; i + 3 <= n; i++) {
            if (s.substr(i, 3) != "mul") continue;
            int a = -1, b = -1;
            for (int va = 1; va <= 3; va++) {
                for (int vb = 1; vb <= 3; vb++) {
                    if (i + 3 + 1 + va + 1 + vb + 1 <= n) {
                        bool ok = true;
                        ok &= s[i + 3] == '(';
                        for (int j = 0; j < va; j++)
                            ok &= isdigit(s[i + 3 + 1 + j]);
                        ok &= s[i + 3 + 1 + va] == ',';
                        for (int j = 0; j < vb; j++)
                            ok &= isdigit(s[i + 3 + 1 + va + 1 + j]);
                        ok &= s[i + 3 + 1 + va + 1 + vb] == ')';

                        if (ok) {
                            a = stoi(s.substr(i + 3 + 1, va));
                            b = stoi(s.substr(i + 3 + 1 + va + 1, vb));
                        }
                    }
                }
            }

            if (a != -1) {
                ans += a * b;
            }

        }

    }

    cout << ans << endl;
}
