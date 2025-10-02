/*
This is a maximum bipartite matching problem. We must match each of the first n
letters in the alphabet with n problems, each one has k_i options (edges).
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;

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
vector<vector<string>> names;
vector<vector<int>> names_idx;  // (problem, letter) -> index in names

void solve(int n) {
  MaxFlow mf(2 + n + n);
  fore(i, 0, n) fore(j, 0, names[i].size()) {
    int letter = names[i][j][0] - 'A';
    if (letter >= n) continue;  // just first n letters in the alphabet
    names_idx[i][letter] = j;
    mf.add_edge(letter, n + i, 1);  // edges in the bipartite graph
  }
  int s = 2 * n, t = 2 * n + 1;
  fore(i, 0, n) mf.add_edge(s, i, 1);      // source to letters
  fore(i, n, 2 * n) mf.add_edge(i, t, 1);  // problems to sink

  mf.max_flow(s, t);

  for (int i = 0; i < n; ++i) {
    for (auto idx : mf.adj[i]) {
      Edge& edge = mf.edges[idx];
      if (edge.flow != 1) continue;
      int problem = edge.to - n;
      cout << names[problem][names_idx[problem][i]] << '\n';
      break;
    }
  }
}

void capitalize(string& s) {
  s[0] = toupper(s[0]);
  fore(i, 1, s.size()) s[i] = tolower(s[i]);
}

int main() {
  int T, n, k;
  string s;
  cin >> T;
  fore(t, 1, T + 1) {
    cin >> n;
    names.assign(n, vector<string>{});
    names_idx.assign(n, vector<int>(26));

    fore(i, 0, n) {
      cin >> k;
      while (k--) {
        cin >> s;
        capitalize(s);
        names[i].push_back(s);
      }
    }
    cout << "Case #" << t << ":\n";
    solve(n);
  }
  return 0;
}
