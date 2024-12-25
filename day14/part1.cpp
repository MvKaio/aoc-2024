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
  string s;

  const int N = 101;
  const int M = 103;

  vector grid(N, string(M, '.'));

  vector<array<int, 2>> ps, vs;

  array<int, 4> cnt;
  while (getline(cin, s)) {
    auto tokens = split(s, ' ');
    array<int, 2> p, v;
    for (auto &s : tokens)
      s = split(s, '=')[1];
    p[0] = stoi(split(tokens[0], ',')[0]);
    p[1] = stoi(split(tokens[0], ',')[1]);

    v[0] = stoi(split(tokens[1], ',')[0]);
    v[1] = stoi(split(tokens[1], ',')[1]);

    auto f = p;
    f[0] += v[0] * 100;
    f[0] = (f[0] % N + N) % N;
    f[1] += v[1] * 100;
    f[1] = (f[1] % M + M) % M;

    if (f[0] == N/2 || f[1] == M/2) continue;

    int quadrant = 2*(f[0] >= N/2) + (f[1] >= M/2);
    grid[f[0]][f[1]] = '#';
    cnt[quadrant]++;
  }
  ans = cnt[0] * cnt[1] * cnt[2] * cnt[3];


  cout << ans << endl;
}
