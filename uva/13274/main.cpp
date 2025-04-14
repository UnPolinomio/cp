/*
Solve using recursion. Try to make beautiful each child (as big as possible) and
keep the k biggest of them, if less than k children remove all of them (leaf).
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

// returns size of biggest beautiful tree rooted at root
int make_beautiful(int root, int parent, int k, vector<vector<int>>& edges) {
  if (edges[root].size() - (root != 0 ? 1 : 0) < k)  // < k children
    return 1;

  // get sizes of beautiful tree rooted at each children
  vector<int> sizes;
  for (int child : edges[root]) {
    if (child == parent) continue;
    sizes.push_back(make_beautiful(child, root, k, edges));
  }

  // keep k biggest plus the current node
  sort(all(sizes));
  reverse(all(sizes));
  return accumulate(sizes.begin(), sizes.begin() + k, 1);
}

int main() {
  int T, N, K;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cin >> N >> K;
    int u, v;
    vector<vector<int>> edges(N);
    for (int i = 1; i < N; ++i) {
      cin >> u >> v;
      --u, --v;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }

    printf("Case %d: %d\n", i, make_beautiful(0, -1, K, edges));
  }
  return 0;
}
