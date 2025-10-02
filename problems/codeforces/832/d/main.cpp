/*
Try the three possible choices for f, the common node count is (d(s, f) + d(t,
f) - d(s, t) + 1) / 2. LCA is implemented with jump pointers, d(., .) uses it.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

constexpr int MAXN = 100001;
vector<int> children[MAXN];
vector<int> jump[MAXN];
int depth[MAXN];

void build_jump_table(int v = 1, int p = -1, int d = 0) {
  depth[v] = d;
  if (d > 0) jump[v].push_back(p);

  for (int i = 1; (1 << i) <= d; ++i)
    jump[v].push_back(jump[jump[v][i - 1]][i - 1]);

  for (int nxt : children[v]) build_jump_table(nxt, v, d + 1);
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);

  int diff = depth[u] - depth[v];
  for (int i = 0; (1 << i) <= diff; ++i)
    if ((1 << i) & diff) u = jump[u][i];

  if (u == v) return u;

  int i = jump[u].size() - 1;
  while (i >= 0) {
    if (jump[u][i] != jump[v][i]) u = jump[u][i], v = jump[v][i];
    i = min(i - 1, (int)jump[u].size() - 1);
  }

  return jump[u][0];
}

int distance(int u, int v) {
  int w = lca(u, v);
  return depth[u] + depth[v] - 2 * depth[w] + 1;
}

int cnt(int s, int t, int f) {
  return (distance(s, f) + distance(t, f) - distance(s, t) + 1) / 2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q, a, b, c, p;
  cin >> n >> q;
  fore(i, 2, n + 1) {
    cin >> p;
    children[p].push_back(i);
  }

  build_jump_table();

  while (q--) {
    cin >> a >> b >> c;
    int ans = max({cnt(b, c, a), cnt(a, b, c), cnt(c, a, b)});

    cout << ans << '\n';
  }

  return 0;
}
