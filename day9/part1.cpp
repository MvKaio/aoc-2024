#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

    for (int i = 0; i < t.size(); i++) {
        while (t.back() == -1) t.pop_back();
        if (i >= t.size()) break;
        if (t[i] == -1) swap(t[i], t.back());
    }
    while (t.back() == -1) t.pop_back();

    for (int i = 0; i < t.size(); i++) {
        ans = add(ans, to_string(i * t[i]));
    }

    cout << ans << endl;
}
