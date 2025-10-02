/*
Using Euler tour technique operations become queries on a lazy segment tree.
We need range sum queries and swap range updates.
*/

#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

struct ST {
  int n;
  vector<int> tree;
  vector<bool> swaps;

  ST(int n, vb& arr) : n(n) {
    tree.assign(4 * n, 0);
    swaps.assign(4 * n, 0);

    build(1, 0, n - 1, arr);
  }

  void recalc(int v) { tree[v] = tree[v << 1] + tree[(v << 1) + 1]; }

  // make swap in current node and add that operation to lazy
  void apply(int v, int l_range, int r_range) {
    int count = r_range - l_range + 1;
    tree[v] = count - tree[v];
    swaps[v] = swaps[v] ^ 1;
  }

  void push(int v, int l_range, int r_range) {
    if (!swaps[v]) return;
    int mid = (l_range + r_range) / 2;
    apply(v << 1, l_range, mid);
    apply((v << 1) + 1, mid + 1, r_range);
    swaps[v] = false;
  }

  void build(int vertex, int l_range, int r_range, vb& arr) {
    if (l_range == r_range) {
      tree[vertex] = arr[l_range];
      return;
    }
    int mid = (l_range + r_range) / 2;
    build(vertex << 1, l_range, mid, arr);
    build((vertex << 1) + 1, mid + 1, r_range, arr);
    recalc(vertex);
  }

  int query(int vertex, int l_range, int r_range, int l, int r) {
    if (l > r) return 0;
    if (l == l_range && r == r_range) return tree[vertex];
    push(vertex, l_range, r_range);

    int mid = (l_range + r_range) / 2;
    return query(vertex << 1, l_range, mid, l, min(r, mid)) +
           query((vertex << 1) + 1, mid + 1, r_range, max(l, mid + 1), r);
  }

  void update(int vertex, int l_range, int r_range, int l, int r) {
    if (l > r) return;
    if (l == l_range && r == r_range) {
      apply(vertex, l_range, r_range);
      return;
    }
    push(vertex, l_range, r_range);
    int mid = (l_range + r_range) / 2;
    update(vertex << 1, l_range, mid, l, min(r, mid));
    update((vertex << 1) + 1, mid + 1, r_range, max(l, mid + 1), r);
    recalc(vertex);
  }
};

class Lights {
 private:
  void build_tour(int node, int prev) {
    eulerian[timer] = state[node];
    start[node] = timer++;
    for (int next : children[node]) build_tour(next, node);
    end[node] = timer;
  }

 public:
  int n;
  int timer = 0;
  vi start, end;  // ranges for each node in eulerian tour vector
  vb eulerian;    // tree values in eulerian tour order
  vb state;       // data read from input
  vector<vector<int>> children;
  ST* st;

  Lights(int n)
      : n(n),
        children(n + 1),
        state(n + 1),
        start(n + 1),
        end(n + 1),
        eulerian(n) {}

  void init() {
    build_tour(1, 0);
    st = new ST(n, eulerian);
  }

  int query(int node) {
    return st->query(1, 0, n - 1, start[node], end[node] - 1);
  }

  void update(int node) { st->update(1, 0, n - 1, start[node], end[node] - 1); }
};

int main() {
  int n, p, t, q;

  // read data
  cin >> n;
  Lights lights(n);

  fore(i, 2, n + 1) {
    cin >> p;
    lights.children[p].push_back(i);
  }

  fore(i, 1, n + 1) {
    cin >> t;
    lights.state[i] = t;
  }

  lights.init();

  // answer queries
  string type;
  int v;
  cin >> q;
  while (q--) {
    cin >> type >> v;
    if (type == "get")
      cout << lights.query(v) << '\n';
    else
      lights.update(v);
  }

  return 0;
}
