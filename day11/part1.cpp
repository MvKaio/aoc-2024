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
  getline(cin, s);
  stringstream ss(s);

  vector<int> a;
  int x;
  while (ss >> x) {
    a.push_back(x);
  }

  int n = a.size();

  map<ll, ll> mp;
  for (int i = 0; i < n; i++) {
    mp[a[i]]++;
  }

  for (int it = 0; it < 25; it++) {
    map<ll, ll> nmp;
    for (auto [a, c] : mp) {
      string s = to_string(a);
      if (a == 0) {
        nmp[1] += c;
      } else if (s.size() % 2 == 0) {
        ll l = stoll(s.substr(0, s.size() / 2));
        ll r = stoll(s.substr(s.size() / 2));
        nmp[l] += c;
        nmp[r] += c;
      } else {
        nmp[a * 2024] += c;
      }
    }
    mp = nmp;
  }
  for (auto [_, c] : mp) {
    ans += c;
  }

  cout << ans << endl;
}
