/*
Build min & max sparse tables. For each peak: BS to find the first peak to the
left and right, get the max of the mins of heights between the current peak and
both adjacent peaks, the diff with current peak height will give prominence.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;
using Op = function<int(int, int)>;

constexpr int MAXN = 100001;
int lg[MAXN];
void precompute_lg() {
  lg[1] = 0;
  for (int i = 2; i < MAXN; ++i) lg[i] = lg[i / 2] + 1;
}

struct SparseTable {
  vector<vector<int>> table;
  Op op;  // max or min

  SparseTable(vector<int>& arr, Op op) : op(op) {
    int n = arr.size();
    table.assign(lg[n] + 1, vector<int>(n));
    table[0] = arr;
    for (int l = 1; l <= lg[arr.size()]; ++l) {
      for (int i = 0; i + (1 << l) <= arr.size(); ++i)
        table[l][i] = op(table[l - 1][i], table[l - 1][i + (1 << (l - 1))]);
    }
  }

  int get(int i, int j) {
    int len = j - i + 1;
    int k = lg[len];
    return op(table[k][i], table[k][j - (1 << k) + 1]);
  }
};

int N;
vector<int> heights;

// finds the first j s.t. heights[j] > heights[i] for j > i
// if no such j exists, returns N-1
int find_peak_right(int i, SparseTable& maxs) {
  int L = i + 1;
  int R = N - 1;

  while (L < R) {
    int mid = (L + R) / 2;
    if (maxs.get(i, mid) <= heights[i])
      L = mid + 1;
    else
      R = mid;
  }

  return L;
}

// finds the leftmost j s.t. heights[j:i] has values <= heights[i]
int find_peak_left(int i, SparseTable& maxs) {
  int L = 0, R = i;
  while (L < R) {
    int mid = (L + R) / 2;
    if (maxs.get(mid, i) > heights[i])
      L = mid + 1;
    else
      R = mid;
  }

  return L;
}

int main() {
  precompute_lg();
  while (cin >> N) {
    bool first = true;
    heights.resize(N);
    for (int i = 0; i < N; ++i) cin >> heights[i];
    SparseTable maxs(heights, [](int a, int b) { return max(a, b); });
    SparseTable mins(heights, [](int a, int b) { return min(a, b); });

    for (int i = 1; i < N - 1; ++i) {
      if (heights[i - 1] >= heights[i] || heights[i + 1] >= heights[i])
        continue;  // not peak

      int left = find_peak_left(i, maxs);
      int right = find_peak_right(i, maxs);
      int prominence = heights[i] - max(mins.get(left, i), mins.get(i, right));
      if (prominence >= 150000) {
        if (first)
          first = false;
        else
          cout << ' ';
        cout << i + 1;
      }
    }
    cout << '\n';
  }
  return 0;
}
