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

    getline(cin, s);
    vector<int> prog;
    for (auto x : split(s, ',')) {
        prog.push_back(stoi(x));
    }

    auto runit = [&](ll x) {
      vector<ll> a = {x, 0, 0};
      vector<ll> output;
      int sp = 0;
      while (sp < prog.size()) {
        int op = prog[sp];
        ll literal = prog[sp + 1];
        ll combo = literal;
        if (combo >= 4 && combo <= 6)
          combo = a[combo - 4];

        if (op == 0) {
          if (combo > 60)
            a[0] = 0;
          else
            a[0] >>= combo;
        } else if (op == 1) {
          a[1] ^= literal;
        } else if (op == 2) {
          a[1] = combo % 8;
        } else if (op == 3) {
          if (a[0] != 0) {
            sp = literal;
          }
        } else if (op == 4) {
          a[1] = a[1] ^ a[2];
        } else if (op == 5) {
          output.push_back(combo % 8);
        } else if (op == 6) {
          if (combo > 60)
            a[1] = 0;
          else
            a[1] = a[0] >> combo;
        } else if (op == 7) {
          if (combo > 60)
            a[2] = 0;
          else
            a[2] = a[0] >> combo;
        }

        if (!(op == 3 && a[0] != 0))
          sp += 2;
      }

      string res;
      for (int i = 0; i < output.size(); i++) {
        res += to_string(output[i]);
        if (i + 1 < output.size()) {
          res += ",";
        }
      }
      return res;
    };

    int n = prog.size();
    const int N = 12;

    auto value = [&] (int mask) {
      int b = (mask & 7) ^ 3;
      int c = (mask >> b) & 7;
      return b ^ c ^ 5;
    };
    auto next = [&] (int mask) {
      return mask >> 3;
    };
    auto fits = [&] (int nmask, int mask) {
      return ((next(mask) ^ nmask) & ((1 << (N - 3)) - 1)) == 0;
    };

    vector dp(n + 1, vector(1 << N, 0));
    for (int mask = 0; mask < (1 << N); mask++) {
      if (value(mask) == prog[0]) {
        dp[0][mask] = true;
      }
    }

    for (int i = 1; i < n; i++) {
      for (int mask = 0; mask < (1 << N); mask++) if (dp[i - 1][mask]) {
        for (int nmask = 0; nmask < (1 << N); nmask++) {
          if (value(nmask) == prog[i] && fits(nmask, mask)) {
            dp[i][nmask] = true;
          }
        }
      }
    }

    int mask = 0;
    while (mask < (1 << N) && !dp[n - 1][mask]) {
      mask++;
    }

    ll ans = mask;
    for (int i = n - 2; i >= 0; i--) {
      for (int nmask = 0; nmask < (1 << N); nmask++) if (dp[i][nmask]) {
        if (dp[i][nmask] && fits(mask, nmask)) {
          ans = (ans << 3) | (nmask & 7);
          mask = nmask;
          break;
        }
      }
    }

    cout << ans << endl;
    cout << runit(ans) << endl;
}
