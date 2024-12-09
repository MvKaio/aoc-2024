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

using T = string;
T add(T a, T b) {
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    T ans;
    int carry = 0;
    for (int i = 0; i < max(a.size(), b.size()) || carry; i++, carry /= 10) {
        carry += (i < a.size() ? a[i] - '0' : 0) + (i < b.size() ? b[i] - '0' : 0);
        ans += '0' + (carry % 10);
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    string s;
    T ans = "0";

    cin >> s;

    vector<int> t;
    int id = 0;
    for (int i = 0; i < s.size(); i++) {
      if (i % 2 == 0) {
        for (int j = 0; j < s[i] - '0'; j++)
          t.push_back(id);
        id++;
      } else {
        for (int j = 0; j < s[i] - '0'; j++)
          t.push_back(-1);
      }
    }
    while (t.back() == -1) t.pop_back();

    for (int i = t.size() - 1, j = i; i >= 0; i = j) {
        while (j >= 0 && t[j] == t[i]) j--;
        if (t[i] != -1) {
          for (int l = 0, r = 0; l <= j; l = r) {
            while (r <= j && t[l] == t[r])
              r++;

            if (t[l] == -1) {
              if (i - j <= r - l) {
                for (int k = 0; k < (i - j); k++) {
                  t[l + k] = t[j + k + 1];
                  t[j + k + 1] = -1;
                }
                break;
              }
            }
          }
        }
    }

    for (int i = 0; i < t.size(); i++) {
        if (t[i] == -1) continue;
        ans = add(ans, to_string(i * t[i]));
    }
    cout << endl;

    cout << ans << endl;
}
