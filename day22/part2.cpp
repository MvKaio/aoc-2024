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

const int N = 16777216;

int main() {
  ll ans = 0;

  string s;
  vector<vector<int>> p, t;
  while (getline(cin, s)) {
    ll x = stoll(s);

    t.emplace_back();
    p.emplace_back();
    for (int it = 0; it < 2000; it++) {
      int prv = x % 10;

      x = (x * 64) ^ x;
      x %= N;
      x = (x / 32) ^ x;
      x %= N;
      x = (x << 11) ^ x;
      x %= N;

      if (it > 0) {
        t.back().push_back((x % 10) - prv);
        p.back().push_back(x % 10);
      }
    }
  }

  int S = 19;
  int MX = S*S*S*S;

  vector<map<vector<int>, int>> mp(t.size());
  for (int i = 0; i < t.size(); i++) {
    for (int j = 0; j + 4 <= t[i].size(); j++) {
      vector<int> a(t[i].begin() + j, t[i].begin() + j + 4);
      if (!mp[i].count(a)) {
        mp[i][a] = p[i][j + 3];
      }
    }
  }

  for (int mask = 0; mask < MX; mask++) {
    vector<int> a;
    for (int i = 0, x = mask; i < 4; i++, x /= S) {
      a.push_back(x % S + (-9));
    }

    int at = 0;
    for (int i = 0; i < t.size(); i++) {
      if (mp[i].count(a)) {
        at += mp[i][a];
      }
    }
    ans = max(ans, (ll)at);
  }


  cout << ans << endl;
}
