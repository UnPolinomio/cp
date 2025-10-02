/*
Use D&C on arr, find the answer in the L and R subarrays. Precalc the ordered
partial sums of R (keep idx info), for each partial sum on L make bs in R (>=X).
*/

#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

lli arr[500000];
lli n, x;

map<lli, int> get_partial_sums(int l, int r) {
  lli sum = 0;
  map<lli, int> ans;

  // add all partial sums keeping the min index that made them
  while (l <= r) {
    sum += arr[l];

    if (!ans.count(sum)) ans[sum] = l;

    ++l;
  }

  // cumulative min on values in reverse order
  int idx = INT_MAX;
  for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
    idx = min(idx, it->second);
    it->second = idx;
  }

  return ans;
}

int solve(int l, int r) {
  if (l == r) return arr[l] >= x ? 1 : INT_MAX;
  int mid = (l + r) / 2;

  int ans = min(solve(l, mid), solve(mid + 1, r));
  auto sums = get_partial_sums(mid + 1, r);

  lli sum = 0;  // partial sum on left subarray
  while (mid >= l) {
    sum += arr[mid];
    auto it = sums.lower_bound(x - sum);  // we need at least x-sum to be >=x
    if (it != sums.end()) ans = min(ans, it->second - mid + 1);
    --mid;
  }

  return ans;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n >> x;

    fore(i, 0, n) cin >> arr[i];

    int ans = solve(0, n - 1);
    if (ans == INT_MAX)
      cout << "-1\n";
    else
      cout << ans << '\n';
  }

  return 0;
}
