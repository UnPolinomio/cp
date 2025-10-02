/*
Keep merge sort tree, for each node keep a prefix sum array. A query is like in
ST, for a node make BS for all values <= x and return corresponding prefix sum.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;

struct ST {
  int n;
  vector<vi> tree, sums;

  ST(vi& arr) : n(arr.size()), tree(4 * n), sums(4 * n) {
    build(1, 0, n - 1, arr);
  }

  // build merge sort tree
  void build(int i, int l_range, int r_range, vi& arr) {
    if (l_range == r_range) {
      tree[i].push_back(arr[l_range]);
      sums[i].push_back(arr[l_range]);
      return;
    }
    int mid = (l_range + r_range) / 2;
    build(2 * i, l_range, mid, arr);
    build(2 * i + 1, mid + 1, r_range, arr);

    int u = 0, v = 0;
    while (u < tree[2 * i].size() && v < tree[2 * i + 1].size()) {
      if (tree[2 * i][u] < tree[2 * i + 1][v])
        tree[i].push_back(tree[2 * i][u++]);
      else
        tree[i].push_back(tree[2 * i + 1][v++]);
    }
    while (u < tree[2 * i].size()) tree[i].push_back(tree[2 * i][u++]);
    while (v < tree[2 * i + 1].size()) tree[i].push_back(tree[2 * i + 1][v++]);

    lli sum = 0;
    for (lli v : tree[i]) {
      sum += v;
      sums[i].push_back(sum);
    }
  }

  lli query(int v, int l_range, int r_range, int l, int r, lli x) {
    if (l > r) return 0;
    if (l == l_range && r == r_range) {
      auto it = upper_bound(all(tree[v]), x);
      int idx = it - tree[v].begin() - 1;  // 0, 1, ..., idx are <= x
      if (idx < 0) return 0;
      return sums[v][idx];
    }

    int mid = (l_range + r_range) / 2;
    return query(2 * v, l_range, mid, l, min(r, mid), x) +
           query(2 * v + 1, mid + 1, r_range, max(l, mid + 1), r, x);
  }
};

int main() {
  lli n, q, l, r, x;
  cin >> n;
  vi arr(n);
  fore(i, 0, n) cin >> arr[i];
  cin >> q;

  ST st(arr);
  lli b = 0;
  while (q--) {
    cin >> l >> r >> x;
    l ^= b;
    r ^= b;
    x ^= b;

    b = st.query(1, 0, n - 1, l - 1, r - 1, x);
    cout << b << '\n';
  }
  return 0;
}
