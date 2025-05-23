/*
If we remove some edge, we have two trees; it's optimal to create an edge
between their centers. Try removing every edge and compute new diameter.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;

vector<vector<int>> adj;

constexpr int MAXN = 2501;
int neighbors_cnt[MAXN];

// returns size of tree, populate leaves queue for that subtree
int populate_neighbors(int v, int p, int root, queue<int>& leaves) {
  neighbors_cnt[v] = adj[v].size();
  if (v == root) --neighbors_cnt[v];
  if (neighbors_cnt[v] == 1) leaves.push(v);
  if (neighbors_cnt[v] == 0) leaves.push(v);

  int size = 1;
  for (int nxt : adj[v]) {
    if (nxt == p) continue;
    size += populate_neighbors(nxt, v, root, leaves);
  }
  return size;
}

int get_center(int v, int ignore, int& diameter) {
  queue<int> leaves;
  int n = populate_neighbors(v, ignore, v, leaves);

  diameter = 0;
  while (n > 2) {
    ++diameter;

    fore(i, 0, leaves.size()) {
      int leaf = leaves.front();
      leaves.pop();
      --n;

      for (int v : adj[leaf]) {
        if (v == ignore) continue;
        --neighbors_cnt[v];
        if (neighbors_cnt[v] == 1) leaves.push(v);
      }
    }
  }

  diameter *= 2;
  if (n == 2) ++diameter;
  return leaves.front();
}

vector<pair<int, int>> edges;
void solve() {
  int best_remove = -1;         // edge idx
  int best_distance = INT_MAX;  // best diameter
  int best_a, best_b;           // centers corresponding to that cut

  for (int i = 0; i < edges.size(); ++i) {
    int diameter_a, diameter_b;
    int center_a = get_center(edges[i].first, edges[i].second, diameter_a);
    int center_b = get_center(edges[i].second, edges[i].first, diameter_b);

    int distance = max(diameter_a, diameter_b);
    distance = max(distance, (diameter_a + 1) / 2 + (diameter_b + 1) / 2 + 1);

    if (distance < best_distance) {
      best_distance = distance;
      best_remove = i;
      best_a = center_a, best_b = center_b;
    }
  }

  cout << best_distance << '\n';
  cout << edges[best_remove].first << ' ' << edges[best_remove].second << '\n';
  cout << best_a << ' ' << best_b << '\n';
}

int main() {
  int T, n, a, b;
  cin >> T;
  while (T--) {
    cin >> n;
    adj.assign(n + 1, vector<int>{});
    edges.resize(n - 1);
    fore(i, 0, n - 1) {
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
      edges[i] = {a, b};
    }

    solve();
  }
  return 0;
}
