#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

void solve(string& str) {
  vector<vector<int>> dp(str.size(), vector<int>(str.size(), 0));
  vector<vector<int>> path(str.size(), vector<int>(str.size(), 0));  // chosen

  // build dp table
  for (int len = 2; len <= str.size(); ++len) {
    for (int i = 0; i < str.size(); ++i) {
      int j = i + len - 1;         // substring s[i..j]
      if (j >= str.size()) break;  // not remaining substrings for that length

      if (str[i] == str[j]) {  // Same beginning and end
        path[i][j] = 0;
        dp[i][j] = dp[i + 1][j - 1];
        continue;
      }

      int opt1 = 1 + dp[i][j - 1];  // insert at beginning
      int opt2 = 1 + dp[i + 1][j];  // insert at end

      dp[i][j] = min(opt1, opt2);

      if (opt1 < opt2)
        path[i][j] = 1;
      else
        path[i][j] = 2;
    }
  }

  // reconstruct answer
  int i = 0, j = str.size() - 1;
  cout << dp[i][j] << ' ';

  string left;

  while (i < j) {  // traverse path
    if (path[i][j] == 0) {
      left.push_back(str[i]);
      ++i;
      --j;
    } else if (path[i][j] == 1) {
      left.push_back(str[j]);
      --j;
    } else {
      left.push_back(str[i]);
      ++i;
    }
  }

  cout << left;
  if (i == j) cout << str[i];  // middle letter
  reverse(all(left));
  cout << left << '\n';
}

int main() {
  string str;
  while (cin >> str) solve(str);

  return 0;
}
