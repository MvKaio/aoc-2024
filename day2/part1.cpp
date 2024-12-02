#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int ans = 0;
    while (getline(cin, s)) {
        vector<int> v;
        stringstream ss(s);
        while (ss >> s) {
            v.push_back(stoi(s));
        }

        if (!is_sorted(v.begin(), v.end())) {
            reverse(v.begin(), v.end());
        }
        if (!is_sorted(v.begin(), v.end())) {
            continue;
        }

        bool ok = true;
        for (int i = 1; i < v.size(); i++)
            ok &= (1 <= v[i] - v[i - 1] && v[i] - v[i - 1] <= 3);

        ans += ok;
    }
    cout << ans << endl;
}
