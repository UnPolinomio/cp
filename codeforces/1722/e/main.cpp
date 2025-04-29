/*
Create a matrix s.t. A[w][h] is the area of all the rectangles w x h. Then
build a 2D suffix matrix. Each query is a query in this suffix matrix.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;
using Mat = vector<vi>;

constexpr int MAXN = 1001;

void fill_prefix_sums(Mat& dp) {
  fore(i, 1, dp.size()) fore(j, 1, dp.size()) {
    dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
  }
}

int main() {
  int t, n, q;
  cin >> t;

  lli w, h, W, H;
  while (t--) {
    cin >> n >> q;
    Mat dp(MAXN, vi(MAXN, 0));

    while (n--) {  // add rectangles to matrix
      cin >> w >> h;
      dp[w][h] += w * h;
    }

    fill_prefix_sums(dp);  // dp is now a 2D suffix matrix

    while (q--) {
      cin >> h >> w >> H >> W;
      --H, --W;  // < H, W

      // query on suffix matrix
      lli ans = dp[H][W] - dp[h][W] - dp[H][w] + dp[h][w];
      cout << ans << '\n';
    }
  }
  return 0;
}
