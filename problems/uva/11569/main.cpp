/*
We just need to know which letters are present. Use DP for alphabet in ascending
order: save max possible length s.t. c is the last char and the number of ways.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

constexpr int sigma = 27;

void solve(vb& present) {
  vector<int> max_length(sigma), cnt(sigma);
  int total_max_length = 0, total_cnt = 0;
  for (int i = 1; i < sigma; ++i) {  // dp[i]
    if (!present[i]) continue;
    max_length[i] = 1, cnt[i] = 1;
    for (int j = 1; j < i && 5 * j <= 4 * i; ++j) {  // check letters before
      if (!present[j]) continue;
      int new_length = max_length[j] + 1;  // new length with j before i
      if (new_length > max_length[i]) {
        max_length[i] = new_length;
        cnt[i] = cnt[j];
      } else if (new_length == max_length[i])
        cnt[i] += cnt[j];
    }

    if (max_length[i] > total_max_length) {  // update global max length
      total_max_length = max_length[i];
      total_cnt = cnt[i];
    } else if (max_length[i] == total_max_length)
      total_cnt += cnt[i];
  }

  cout << total_max_length << ' ' << total_cnt << '\n';
}

int main() {
  int N;
  string s;
  cin >> N;
  cin.ignore();
  while (N--) {
    getline(cin, s);
    vb present(sigma, false);
    for (char c : s)
      if ('A' <= c && c <= 'Z') present[c - 'A' + 1] = true;
    solve(present);
  }
  return 0;
}
