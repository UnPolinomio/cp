/*
Sort array and solve recursively: find the best pivot that minimizes
the difference between the sum of the left and right sides, then solve subarrays
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

vector<int> nums;
vector<int> partials;

void solve(int start, int end) {
  if (end <= start) return;
  if (end == start + 1) {
    cout << nums[start];
    return;
  }

  int best_diff = INT_MAX, best_pivot = 0, best_left = 0;
  for (int i = start; i < end; ++i) {
    while (i < end - 1 && nums[i + 1] == nums[i]) ++i;  // last item with value

    int left = partials[i] - partials[start];
    int right = partials[end] - partials[i + 1];
    int diff = abs(left - right);

    if (diff < best_diff || (diff == best_diff && left > best_left))
      best_diff = diff, best_pivot = i, best_left = left;
  }

  cout << nums[best_pivot];
  cout << "(";
  solve(start, best_pivot);
  if (best_pivot - start > 0 && end - best_pivot - 1 > 0) cout << ',';
  solve(best_pivot + 1, end);
  cout << ")";
}

int main() {
  int tests, n;
  cin >> tests;
  fore(test, 1, tests + 1) {
    cout << "Case #" << test << ": ";
    cin >> n;
    nums.resize(n);
    partials.resize(n + 1);
    for (int& el : nums) cin >> el;
    sort(all(nums));
    partial_sum(all(nums), partials.begin() + 1);
    solve(0, nums.size());
    cout << '\n';
  }
  return 0;
}
