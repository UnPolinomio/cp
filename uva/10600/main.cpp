/*
We're looking for MST, do Kruskal for lowest cost. Try removing one tree edge
each at a time and do kruskal, keep the lowest of these to get the second MST.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

struct DSU {
  vector<int> parent;
  vector<int> size;

  DSU(int n) : parent(n), size(n, 1) { iota(all(parent), 0); }

  int find(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v]);
  }

  void join(int i, int j) {
    i = find(i), j = find(j);
    if (i == j) return;
    if (size[i] < size[j]) swap(i, j);
    parent[j] = i;
    size[i] += size[j];
  }
};

using Edge = pair<int, pair<int, int>>;  // (cost, nodes)

// kruskal algorithm ignoring an edge, returns weight of mst and selected edges
// on tree array
int mst(int n, vector<Edge>& edges, vector<Edge>* tree, Edge ignore) {
  DSU dsu(n);
  int ans = 0;
  for (int i = 0; i < edges.size(); ++i) {
    if (edges[i] == ignore) continue;
    auto [cost, nodes] = edges[i];
    if (dsu.find(nodes.first) == dsu.find(nodes.second)) continue;
    ans += cost;
    dsu.join(nodes.first, nodes.second);
    if (tree) tree->push_back(edges[i]);
  }

  if (dsu.size[dsu.find(0)] != n)  // no mst exists
    return INT_MAX;

  return ans;
}

int main() {
  int T, N, M;
  cin >> T;
  while (T--) {
    cin >> N >> M;
    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
      cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
      --edges[i].second.first, --edges[i].second.second;
    }
    sort(all(edges));

    vector<Edge> tree;
    cout << mst(N, edges, &tree, {0, {0, 0}}) << ' ';  // first mst

    int second_mst = INT_MAX;
    for (Edge edge : tree)  // try removing each edge
      second_mst = min(second_mst, mst(N, edges, nullptr, edge));
    cout << second_mst << '\n';
  }
  return 0;
}
