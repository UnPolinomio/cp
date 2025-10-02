/*
Iterate over suffixes sums (taking into account powers of 10) we count
repetitions mod 2019.
 */
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

constexpr lli MOD = 2019;

lli cnt[MOD];

int main() {
  string s;
  cin >> s;
  reverse(s.begin(), s.end());

  cnt[0] = 1;

  lli ans = 0;
  lli sum = 0;
  lli power = 1;

  for (char c : s) {
    sum += power * (c - '0');
    sum %= MOD;
    power *= 10;
    power %= MOD;

    ans += cnt[sum];
    ++cnt[sum];
  }

  cout << ans << '\n';

  return 0;
}
