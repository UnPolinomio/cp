/*
Find last letter that occurs by the first time. Repeat n times. If this can't be
done you can find exactly the non-appearing string.
*/
#include <bits/stdc++.h>

using namespace std;

int n, k;
string s;

string solve() {
  int j = 0;

  string fail;

  for (int i = 0; i < n; ++i) {
    vector<bool> found(k, false);
    int remaining = k;

    while (j < s.size() && remaining > 0) {
      int f = s[j] - 'a';
      ++j;
      if (found[f]) continue;
      found[f] = true;
      --remaining;
      if (remaining == 0) fail.push_back('a' + f);
    }

    if (j == s.size() && remaining > 0) {
      int f = 0;
      while (found[f]) ++f;
      fail += string(n - i, 'a' + f);
      return fail;
    }
  }

  return "";
}

int main() {
  int t, m;
  cin >> t;
  while (t--) {
    cin >> n >> k >> m >> s;
    string ans = solve();
    if (ans.size())
      cout << "NO\n" << ans << '\n';
    else
      cout << "YES\n";
  }
}
