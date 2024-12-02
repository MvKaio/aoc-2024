#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int ans = 0;

    auto good = [&] (vector<int> v) {
        if (!is_sorted(v.begin(), v.end())) {
            reverse(v.begin(), v.end());
        }
        if (!is_sorted(v.begin(), v.end())) {
            return false;
        }

        bool ok = true;
        for (int i = 1; i < v.size(); i++)
            ok &= (1 <= v[i] - v[i - 1] && v[i] - v[i - 1] <= 3);

        return ok;
    };
    while (getline(cin, s)) {
        vector<int> v;
        stringstream ss(s);
        while (ss >> s) {
            v.push_back(stoi(s));
        }

        bool ok = good(v);
        ans += ok;

        if (!ok) {
            for (int i = 0; i < v.size(); i++) {
                vector<int> w = v;
                w.erase(w.begin() + i);

                if (good(w)) {
                    ok = 1; break;
                }
            }
            ans += ok;
        }
    }
    cout << ans << endl;
}
