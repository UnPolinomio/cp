/*
Make binary search over max people per score, to get the min that needs <= p
scores
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

// returns needed scores if max_per_score people are allowed in a single one
lli needed_scores(vi& instruments, lli max_per_score) {
  lli ans = 0;
  for (lli cnt : instruments) {
    ans += cnt / max_per_score;
    if (cnt % max_per_score != 0) ++ans;
  }

  return ans;
}

lli solve(vi& instruments, lli p) {
  lli l = 1, r = 1000;
  while (l < r) {  // binary search over max_per_score
    lli mid = (l + r) / 2;
    if (needed_scores(instruments, mid) > p)
      l = mid + 1;
    else
      r = mid;
  }

  return l;
}

int main() {
  lli p, n;
  while (cin >> p >> n) {
    vi instruments(n);
    for (lli& el : instruments) cin >> el;
    cout << solve(instruments, p) << '\n';
  }
  return 0;
}
