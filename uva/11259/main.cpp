/*
Compute dp[v] not taking into account limits d_i. For a query use inclusion -
exclusion principle for events A_i = we used more than d_i coins of type c_i
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;

constexpr lli MAXV = 100001;
lli c[4];
lli cnt[MAXV];  // cnt[v] = # of ways to obtain v with no limits d_i
void build_dp() {
  fill(cnt, cnt + MAXV, 0LL);
  cnt[0] = 1;
  for (int i = 0; i < 4; ++i)
    for (lli v = c[i]; v < MAXV; ++v) cnt[v] += cnt[v - c[i]];
}

lli d[4];
lli solve(lli v) {
  lli ans = 0;
  for (int msk = 0; msk < (1 << 4); ++msk) {  // try all subsets of four coins
    lli new_v = v;
    for (int i = 0; i < 4; ++i) {
      if (!(msk & (1 << i))) continue;
      new_v -= (d[i] + 1) * c[i];  // used d_i + 1 coins of type c_i
    }
    if (new_v < 0) continue;
    if (__builtin_popcount(msk) % 2 == 0)  // inclusion-exclusion
      ans += cnt[new_v];
    else
      ans -= cnt[new_v];
  }
  return ans;
}

int main() {
  lli t, q, v;
  cin >> t;
  while (t--) {
    cin >> c[0] >> c[1] >> c[2] >> c[3] >> q;
    build_dp();
    while (q--) {
      cin >> d[0] >> d[1] >> d[2] >> d[3] >> v;
      cout << solve(v) << '\n';
    }
  }

  return 0;
}
