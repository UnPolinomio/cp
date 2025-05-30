/*
Speed changes cost depends on min/max velocity achieved. Sort edges by speed,
for each l find smallest r s.t. [l, r] connects src and dest using DSU, keep min
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

struct DSU {
  vector<int> parent, sz;

  DSU(int n) : parent(n), sz(n, 1) { iota(parent.begin(), parent.end(), 0); }

  int find(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v]);
  }

  void join(int u, int v) {
    u = find(u), v = find(v);
    if (sz[u] < sz[v]) swap(u, v);
    parent[v] = u;
    sz[u] += sz[v];
  }

  bool same(int u, int v) { return find(u) == find(v); }
};

using Road = array<int, 3>;  // (speed, start, end)

int best_energy_change(int n, vector<Road>& roads, int src, int dest) {
  int best_diff = INT_MAX;

  for (int l = 0; l < roads.size(); ++l) {
    DSU dsu(n + 1);

    int r = l;
    while (r < roads.size() && !dsu.same(src, dest)) {
      dsu.join(roads[r][1], roads[r][2]);
      ++r;
    }

    if (!dsu.same(src, dest)) break;

    // we connected src and dest with [l, r) so abs(|v_min - v_max|) is cost
    best_diff = min(best_diff, roads[r - 1][0] - roads[l][0]);
  }

  return best_diff;
}

int main() {
  int n, m, start, stop, k, src, dest;
  while (cin >> n >> m) {
    vector<Road> roads(m);
    for (auto& road : roads) cin >> road[1] >> road[2] >> road[0];
    sort(roads.begin(), roads.end());

    cin >> start >> stop >> k;

    while (k--) {
      cin >> src >> dest;
      cout << start + stop + best_energy_change(n, roads, src, dest) << '\n';
    }
  }

  return 0;
}
