/*
Keep all edges with ppa exactly equal to the highest ppa. The answer is the size
of the largest connected component.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vb = vector<bool>;

// returns size of connected component
int get_size(int v, vb& visited, vector<vector<int>>& adj) {
  int ans = 1;
  visited[v] = true;

  for (int nxt : adj[v])
    if (!visited[nxt]) ans += get_size(nxt, visited, adj);

  return ans;
}

int main() {
  int n, m, a, b, ppa;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;

    int max_ppa = INT_MIN;
    vector<pair<int, int>> edges;  // edges with highest ppa
    while (m--) {
      cin >> a >> b >> ppa;
      if (ppa < max_ppa) continue;
      if (ppa > max_ppa) {
        edges.clear();
        max_ppa = ppa;
      }
      edges.emplace_back(a, b);
    }

    vector<vector<int>> adj(n);
    vb visited(n, false);
    for (auto [a, b] : edges) {
      adj[a - 1].push_back(b - 1);
      adj[b - 1].push_back(a - 1);
    }

    int max_size = 0;
    for (int i = 0; i < n; ++i)
      if (!visited[i]) max_size = max(max_size, get_size(i, visited, adj));

    cout << max_size << '\n';
  }
  return 0;
}
