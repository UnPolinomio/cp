/*
DP over the tree. For each node save min cost to visit all friends in subtree
and return to the node, and min cost to visit all without having to return.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using Edge = pair<int, int>;  // (to, weight)
constexpr int MAXN = 100001;

vector<vector<Edge>> adj;
vector<bool> friends;

int returns[MAXN], stays[MAXN];  // min cost having/not having to return
void dfs(int v, int p, vector<vector<Edge>>& adj) {
  returns[v] = 0;
  stays[v] = 0;
  for (auto [nxt, w] : adj[v]) {  // for each child
    if (nxt == p) continue;
    dfs(nxt, v, adj);
    if (!friends[nxt]) continue;  // that has a friend in its subtree
    friends[v] = true;
    returns[v] += returns[nxt] + w;

    stays[v] = max(stays[v], returns[nxt] + w - stays[nxt]);  // best saved cost
  }
  stays[v] = returns[v] - stays[v];  // final (not having to return) cost
}

int main() {
  int n, f, a, b, c, l;
  while (cin >> n >> f) {
    adj.assign(n + 1, vector<Edge>());
    fore(i, 1, n) {
      cin >> a >> b >> c;
      adj[a].emplace_back(b, c);
      adj[b].emplace_back(a, c);
    }
    friends.assign(n + 1, false);
    while (f--) {
      cin >> l;
      friends[l] = true;
    }

    dfs(1, 0, adj);
    cout << stays[1] << '\n';
  }
  return 0;
}
