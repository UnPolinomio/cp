/*
Build a lazy ST for min value with add range updates. Print highest node x with
indegree 0 and decrease (using ST) indegree for v > x except for removed edges.
*/

#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
constexpr int INF = 10000000;

class SegTree {
 private:
  int n;
  vector<int> mn, lazy;

  void push(int node) {
    mn[2 * node] += lazy[node];
    lazy[2 * node] += lazy[node];
    mn[2 * node + 1] += lazy[node];
    lazy[2 * node + 1] += lazy[node];
    lazy[node] = 0;
  }

  void update(int node, int l_range, int r_range, int l, int r, int x) {
    if (l > r) return;

    if (l == l_range && r == r_range) {
      mn[node] += x;
      lazy[node] += x;
      return;
    }
    push(node);

    int m = (l_range + r_range) / 2;
    update(2 * node, l_range, m, l, min(r, m), x);
    update(2 * node + 1, m + 1, r_range, max(l, m + 1), r, x);
    mn[node] = min(mn[2 * node], mn[2 * node + 1]);
  }

  // returns of index of last zero element
  int get_highest_zero_idx(int node, int l_range, int r_range) {
    if (mn[node] > 0) return -1;
    if (l_range == r_range) return l_range;
    push(node);
    int m = (l_range + r_range) / 2;
    int right_idx = get_highest_zero_idx(2 * node + 1, m + 1, r_range);
    if (right_idx != -1) return right_idx;
    return get_highest_zero_idx(2 * node, l_range, m);
  }

 public:
  SegTree(int n) : n(n), mn(4 * n), lazy(4 * n) {}
  void increase(int l, int r, int x) { update(1, 0, n - 1, l, r, x); }
  int get_next() { return get_highest_zero_idx(1, 0, n - 1); }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T, N, M, a, b;
  cin >> T;
  while (T--) {
    cin >> N >> M;
    SegTree tree(N + 1);
    fore(i, 1, N + 1) tree.increase(i, i, i - 1);  // initial indegrees

    vector<vector<int>> adj(N + 1);

    while (M--) {  // read removed edges
      cin >> a >> b;
      tree.increase(b, b, -1);
      adj[a].push_back(b);
    }

    fore(i, 0, N) {
      int node = tree.get_next();  // highest 0 indegree node
      cout << node << ' ';

      tree.increase(node + 1, N, -1);  // v > node decrease indegree
      for (int v : adj[node]) tree.increase(v, v, 1);  // except removed edges
      tree.increase(node, node, INF);  // make INF to get next 0 indegree node
    }

    cout << '\n';
  }
  return 0;
}
