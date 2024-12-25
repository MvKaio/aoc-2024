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

  vector<string> patterns = split(s, ',');
  for (auto &x : patterns) {
    x = trim(x);
  }

  ll ans = 0;
  while (getline(cin, s)) {
    if (s.empty()) {continue;}

    int n = s.size();
    vector dp(n + 1, 0ll);
    dp[n] = 1;

    for (int i = n - 1; i >= 0; i--) {
      for (auto &pattern : patterns) {
        int m = pattern.size();
        if (i + m <= n && s.substr(i, m) == pattern) {
          dp[i] += dp[i + m];
        }
      }
    }
    ans += dp[0];
  }
  cout << ans << endl;

}
