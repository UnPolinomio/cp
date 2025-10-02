/*
For each level, store nodes in preorder and their cumulative xor (26 letters).
Queries use binary search on levels, similar to Euler tour subtree queries.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) (x).begin(), (x).end()

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

constexpr int MAX_NODES = 500001;

int in_time[MAX_NODES];
int out_time[MAX_NODES];

// levels[lvl]: stores (in_time, cumulative xor mask) for each node at this lvl
vector<pair<int, int>> levels[MAX_NODES];
vector<int> children[MAX_NODES];
string tags;

int t = 0;
void populate_dfs(int node, int parent, int level = 1) {
  in_time[node] = ++t;

  // add cumulative xor mask for this node at the current level
  int last = levels[level].empty() ? 0 : levels[level].back().second;
  last ^= 1 << (tags[node - 1] - 'a');
  levels[level].emplace_back(t, last);

  // DFS on all children except the parent
  for (int next : children[node]) {
    if (next == parent) continue;
    populate_dfs(next, node, level + 1);
  }

  out_time[node] = t;
}

bool query(int v, int h) {
  // find all nodes at level h in the subtree rooted at v using in/out times
  auto start = lower_bound(all(levels[h]), make_pair(in_time[v], 0));
  auto end = lower_bound(all(levels[h]), make_pair(out_time[v] + 1, 0));

  if (end - start == 0) return true;  // no nodes at this level in the subtree

  --end;
  int mask = end->second;
  if (start != levels[h].begin()) {  // remove prefix xor mask
    --start;
    mask ^= start->second;
  }

  // at most one letter with odd count (palindrome check)
  return __builtin_popcount(mask) < 2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  int parent;
  for (int node = 2; node <= n; ++node) {
    cin >> parent;
    children[parent].push_back(node);
  }
  cin >> tags;

  populate_dfs(1, -1);

  int v, h;
  while (m--) {
    cin >> v >> h;
    if (query(v, h))
      cout << "Yes\n";
    else
      cout << "No\n";
  }

  return 0;
}
