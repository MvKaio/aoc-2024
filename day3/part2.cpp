#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    string s;
    ll ans = 0;

    bool f = true;
    while (getline(cin, s)) {
        int n = s.size();
        string x = "do()";
        string y = "don't()";
        for (int i = 0; i + 3 <= n; i++) {
            if (i + x.size() <= n && s.substr(i, x.size()) == x) {
                f = true;
            }
            if (i + y.size() <= n && s.substr(i, y.size()) == y) {
                f = false;
            }
            if (s.substr(i, 3) == "mul") {
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

              if (a != -1 && f) {
                ans += a * b;
              }
            }
        }
    }

    cout << ans << endl;
}
