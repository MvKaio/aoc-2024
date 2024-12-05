#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    string s;
    ll ans = 0;

    vector<string> grid;

    while (getline(cin, s)) {
        stringstream ss(s);
        grid.push_back(s);
    }

    string x = "MAS";

    int n = grid.size(), m = grid[0].size();
    for (int i = 1; i + 1 < n; i++) {
      for (int j = 1; j + 1 < m; j++) {
        if (grid[i][j] == 'A') {
          int cnt = 0;
          cnt += grid[i - 1][j - 1] == 'M' && grid[i + 1][j + 1] == 'S';
          cnt += grid[i - 1][j + 1] == 'M' && grid[i + 1][j - 1] == 'S';
          cnt += grid[i - 1][j - 1] == 'S' && grid[i + 1][j + 1] == 'M';
          cnt += grid[i - 1][j + 1] == 'S' && grid[i + 1][j - 1] == 'M';
          ans += cnt >= 2;
        }
      }
    }

    cout << ans << endl;
}
