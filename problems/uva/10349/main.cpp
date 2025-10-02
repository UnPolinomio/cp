/*
This can be reduced to bipartite matching (max flow). Connect adjacent points of
interest with edges; one antenna can cover one edge (better than just a vertex).
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

struct Edge {
  int from, to, flow, cap;
};

struct MaxFlow {
  int n;
  vector<Edge> edges;
  vector<vector<int>> adj;

  MaxFlow(int n) : n(n), adj(n) {}

  void add_edge(int u, int v, int cap) {
    adj[u].push_back(edges.size());
    edges.push_back({u, v, 0, cap});
    adj[v].push_back(edges.size());
    edges.push_back({v, u, 0, 0});
  }

  int bfs(int s, int t) {
    vector<int> path(n, -1);
    queue<int> pending;
    pending.push(s);
    path[s] = 0;

    // find path
    bool found = false;
    while (!pending.empty() && !found) {
      int node = pending.front();
      pending.pop();

      for (int edge_idx : adj[node]) {
        Edge& edge = edges[edge_idx];
        if (edge.flow == edge.cap) continue;
        if (path[edge.to] != -1) continue;
        path[edge.to] = edge_idx;
        pending.push(edge.to);

        if (edge.to == t) found = true;
      }
    }

    if (!found) return 0;

    // find min cap in path
    int curr = t;
    int flow = INT_MAX;
    while (curr != s) {
      Edge& edge = edges[path[curr]];
      flow = min(flow, edge.cap - edge.flow);
      curr = edge.from;
    }

    // apply path
    curr = t;
    while (curr != s) {
      int edge_idx = path[curr];
      edges[edge_idx].flow += flow;
      edges[edge_idx ^ 1].flow -= flow;
      curr = edges[edge_idx].from;
    }

    return flow;
  }

  int max_flow(int s, int t) {
    int flow = 0, pushed;
    while (pushed = bfs(s, t)) flow += pushed;
    return flow;
  }
};

int n, h, w;
bool matrix[40][10];

int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

int solve() {
  MaxFlow mf(h * w + 2);

  int places = 0;  // to cover

  fore(i, 0, h) fore(j, 0, w) {
    if (!matrix[i][j]) continue;
    ++places;
    if ((i + j) % 2 != 0) continue;

    fore(p, 0, 4) {  // four directions
      int i_ = i + di[p];
      int j_ = j + dj[p];
      if (i_ < 0 || j_ < 0 || i_ >= h || j_ >= w) continue;
      if (!matrix[i_][j_]) continue;
      mf.add_edge(i * w + j, i_ * w + j_, 1);  // connect to adjacent places
    }
  }

  // connect source and sink
  fore(i, 0, h) fore(j, 0, w) {
    if ((i + j) % 2 == 0)
      mf.add_edge(h * w, i * w + j, 1);
    else
      mf.add_edge(i * w + j, h * w + 1, 1);
  }

  return places - mf.max_flow(h * w, h * w + 1);
}

int main() {
  string row;
  cin >> n;
  while (n--) {
    cin >> h >> w;
    fore(i, 0, h) {
      cin >> row;
      fore(j, 0, w) matrix[i][j] = row[j] == '*';
    }

    cout << solve() << '\n';
  }

  return 0;
}
