#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;

using lli = long long int;
using It = vector<lli>::iterator;

vector<lli> generate_sums(It first, It last) {
  int n = last - first;
  vector<lli> sums;
  for (int mask = 1; mask < (1 << n); ++mask) {
    lli sum = 0;
    for (int i = 0; i < n; ++i)
      if (mask & (1 << i)) sum += first[i];
    sums.push_back(sum);
  }
  return sums;
}

int main() {
  lli n, x;
  cin >> n >> x;
  vector<lli> nums(n);
  for (auto &el : nums) cin >> el;

  int left_cnt = n / 2;

  auto left = generate_sums(nums.begin(), nums.begin() + left_cnt);
  auto right = generate_sums(nums.begin() + left_cnt, nums.end());

  sort(all(left));

  lli ans = upper_bound(all(left), x) - lower_bound(all(left), x);

  for (auto num : right) {
    if (num == x) ++ans;
    ans += upper_bound(all(left), x - num) - lower_bound(all(left), x - num);
  }

  cout << ans << '\n';

  return 0;
}
