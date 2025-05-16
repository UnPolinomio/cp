/*
Split rows (columns) into blocks of contiguous free cells. Each rook occupies
exactly one block of each type, to get non-attacking use maximum bipartite match
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

constexpr int MAXN = 100;
bool board[MAXN][MAXN];

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

int lr_blocks[MAXN][MAXN], tb_blocks[MAXN][MAXN];  // left-right and top-bottom
int solve(int n) {
  int node_idx = 2;

  // enumerate horizontal blocks
  fore(i, 0, n) {
    int j = 0;
    while (j < n) {
      while (j < n && !board[i][j]) ++j;
      while (j < n && board[i][j]) lr_blocks[i][j++] = node_idx;
      if (board[i][j - 1]) ++node_idx;
    }
  }

  // enumerate vertical blocks
  int tb_start = node_idx;
  fore(j, 0, n) {
    int i = 0;
    while (i < n) {
      while (i < n && !board[i][j]) ++i;
      while (i < n && board[i][j]) tb_blocks[i++][j] = node_idx;
      if (board[i - 1][j]) ++node_idx;
    }
  }

  MaxFlow mf(node_idx);

  fore(i, 2, tb_start) mf.add_edge(0, i, 1);         // source to lr blocks
  fore(i, tb_start, node_idx) mf.add_edge(i, 1, 1);  // tb blocks to sink

  fore(i, 0, n) fore(j, 0, n) {  // bipartite graph edges
    if (!board[i][j]) continue;
    // add edge for each free cell from its lr block to its tb block
    mf.add_edge(lr_blocks[i][j], tb_blocks[i][j], 1);
  }

  return mf.max_flow(0, 1);
}

int main() {
  int n;
  char ch;
  while (cin >> n) {
    fore(i, 0, n) fore(j, 0, n) {
      cin >> ch;
      board[i][j] = ch == '.';
    }

    cout << solve(n) << '\n';
  }

  return 0;
}
