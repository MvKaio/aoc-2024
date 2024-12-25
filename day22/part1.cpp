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
  while (getline(cin, s)) {
    ll x = stoll(s);

    for (int it = 0; it < 2000; it++) {
      int prv = x % 10;

      x = (x * 64) ^ x;
      x %= N;
      x = (x / 32) ^ x;
      x %= N;
      x = (x << 11) ^ x;
      x %= N;
    }
    ans += x;
  }
  cout << ans << endl;
}
