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
  ll ans = 0;
  vector<string> grid;

  string s;
  vector<string> buffer;

  vector<vector<int>> vs;
  vector<bool> locks;
  while (getline(cin, s)) {
    if (s.empty()) {
      vector<int> v;
      bool key = true;
      for (int j = 0; j < 5; j++) {
        int cnt = 0;
        for (int i = 0; i < buffer.size(); i++) {
          cnt += buffer[i][j] == '#';

          if (i + 1 < buffer.size() && buffer[i][j] == '.' && buffer[i + 1][j] == '#') {
            key = false;
          }
        }

        v.push_back(cnt);
      }
      vs.push_back(v);
      locks.push_back(key);
      buffer.clear();
    } else {
      buffer.push_back(s);
    }
  }
  if (buffer.size()) {
    vector<int> v;
    bool key = true;
    for (int j = 0; j < 5; j++) {
      int cnt = 0;
      for (int i = 0; i < buffer.size(); i++) {
        cnt += buffer[i][j] == '#';

        if (i + 1 < buffer.size() && buffer[i][j] == '.' && buffer[i + 1][j] == '#') {
          key = false;
        }
      }

      v.push_back(cnt);
    }
    vs.push_back(v);
    locks.push_back(key);
  }

  for (int i = 0; i < vs.size(); i++) if (locks[i]) {
    for (int j = 0; j < vs.size(); j++) if (!locks[j]) {
      bool fit = true;
      for (int k = 0; k < 5; k++)
        fit &= vs[i][k] + vs[j][k] <= 7;
      if (fit) ans++;
    }
  }

  cout << ans << endl;
}
