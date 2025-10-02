/*
Using a lazy segment tree, each node has three counts for mod 3 (0, 1, 2).
We need range sum query and increase +1 range query (increase is a rotation).
*/

#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;
using State = array<lli, 3>;

struct ST {
  int N;
  vector<State> tree;  // current values
  vi lazy;             // need to propagate to children

  ST(int N) : N(N) {
    tree.assign(4 * N, {0, 0, 0});
    lazy.assign(4 * N, 0);

    build(1, 0, N - 1);
  }

  // Update node tree value
  void recalc_node(int v) {
    for (int i : {0, 1, 2}) tree[v][i] = tree[2 * v][i] + tree[2 * v + 1][i];
  }

  void build(int vertex, int l_range, int r_range) {
    if (l_range == r_range) {
      tree[vertex][0] = 1;
      return;
    }

    int mid = (l_range + r_range) / 2;
    build(2 * vertex, l_range, mid);
    build(2 * vertex + 1, mid + 1, r_range);
    recalc_node(vertex);
  }

  // used when increased node v
  void rotate(int v) {
    int tmp = tree[v][0];
    tree[v][0] = tree[v][2];
    tree[v][2] = tree[v][1];
    tree[v][1] = tmp;
  }

  void push(int v) {
    for (int i = 0; i < lazy[v]; ++i) {
      rotate(2 * v);
      rotate(2 * v + 1);
    }

    lazy[2 * v] += lazy[v];
    lazy[2 * v] %= 3;  // three increments have no effect
    lazy[2 * v + 1] += lazy[v];
    lazy[2 * v + 1] %= 3;

    lazy[v] = 0;
  }

  // Sum range query
  State query(int vertex, int l_range, int r_range, int l, int r) {
    if (l > r) return {0, 0, 0};
    if (l == l_range && r == r_range) return tree[vertex];

    push(vertex);

    int mid = (l_range + r_range) / 2;
    State left = query(2 * vertex, l_range, mid, l, min(r, mid));
    State right = query(2 * vertex + 1, mid + 1, r_range, max(l, mid + 1), r);

    left[0] += right[0];
    left[1] += right[1];
    left[2] += right[2];

    return left;
  }

  // Increase range query
  void update(int vertex, int l_range, int r_range, int l, int r) {
    if (l > r) return;
    if (l == l_range && r == r_range) {
      rotate(vertex);
      ++lazy[vertex];
      return;
    }

    push(vertex);

    int mid = (l_range + r_range) / 2;
    update(2 * vertex, l_range, mid, l, min(r, mid));
    update(2 * vertex + 1, mid + 1, r_range, max(l, mid + 1), r);

    recalc_node(vertex);
  }
};

int main() {
  int N, Q;
  cin >> N >> Q;

  ST st(N);
  int t, a, b;
  while (Q--) {
    cin >> t >> a >> b;

    if (t == 0)
      st.update(1, 0, N - 1, a, b);
    else {
      State state = st.query(1, 0, N - 1, a, b);
      cout << state[0] << '\n';  // print 0 mod 3
    }
  }

  return 0;
}
