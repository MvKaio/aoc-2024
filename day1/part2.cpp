#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    vector<int> list1, list2;
    int a, b;
    while (cin >> a >> b) {
        list1.push_back(a);
        list2.push_back(b);
    }
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());
    ll ans = 0;
    for (int i = 0; i < list1.size(); i++) {
        int cnt = upper_bound(list2.begin(), list2.end(), list1[i]) - lower_bound(list2.begin(), list2.end(), list1[i]);
        ans += list1[i] * cnt;
    }
    cout << ans << endl;
}
