/*
Solve recursively. We always remove a child of an infected node. There are at
most two options which can be calculated recursively, take the best of the two.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

vector<vector<int>> adj;
using State = pair<int, int>;  // (saved nodes, size of subtree)

// returns the state, saved nodes considering tree rooted at node with only the
// root infected
State solve(int node, int parent) {
  vector<State> st;
  for (int next : adj[node]) {
    if (next == parent) continue;
    st.push_back(solve(next, node));
  }

  if (st.size() == 0)  // no children
    return {0, 1};
  if (st.size() == 1) {  // one children, we must delete it
    return {st[0].second - 1, st[0].second + 1};
  }

  int op1 = st[0].second - 1 + st[1].first;  // option 1: remove first child
  int op2 = st[1].second - 1 + st[0].first;  // option 2: remove second child

  return {max(op1, op2), st[0].second + st[1].second + 1};
}

int main() {
  int t, n, u, v;
  cin >> t;
  while (t--) {
    cin >> n;
    adj.assign(n, vector<int>{});
    fore(i, 1, n) {
      cin >> u >> v;
      --u, --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    State st = solve(0, -1);
    cout << st.first << '\n';
  }

  return 0;
}
