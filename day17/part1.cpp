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
    string s;

    vector<ll> a = {234359063387076, 0, 0};

    getline(cin, s);
    vector<int> prog;
    for (auto x : split(s, ',')) {
        prog.push_back(stoi(x));
    }

    vector<ll> output;
    int sp = 0;
    while (sp < prog.size()) {
        int op = prog[sp];
        ll literal = prog[sp + 1];
        ll combo = literal;
        if (combo >= 4 && combo <= 6)
            combo = a[combo - 4];

        if (op == 0) {
            if (combo > 60) a[0] = 0;
            else a[0] >>= combo;
        } else if (op == 1) {
            a[1] ^= literal;
        } else if (op == 2) {
            a[1] = combo % 8;
        } else if (op == 3) {
            if (a[0] != 0) {
                sp = literal;
            }
        } else if (op == 4) {
            a[1] = a[1] ^ a[2];
        } else if (op == 5) {
            output.push_back(combo % 8);
        } else if (op == 6) {
            if (combo > 60) a[1] = 0;
            else a[1] = a[0] >> combo;
        } else if (op == 7) {
            if (combo > 60) a[2] = 0;
            else a[2] = a[0] >> combo;
        }

        if (!(op == 3 && a[0] != 0))
            sp += 2;
    }

    for (int i = 0; i < output.size(); i++) {
        cout << output[i];
        if (i + 1 < output.size()) {
            cout << ",";
        }
    }
    cout << endl;
}
