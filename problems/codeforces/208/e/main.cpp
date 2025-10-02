/*
Using jump pointers get the p-ancestor of v; we want all nodes with same depth
as v in the subtree rooted at the ancestor. offline answer can be done with sack
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

constexpr int MAXN = 100001;
vector<vector<int>> children;

// fill depth and subtree sizes
int depth[MAXN] = {0};
int subsize[MAXN] = {0};
void fill_data(int v, int p, int d = 1) {
  depth[v] = d;
  subsize[v] = 1;
  for (int next : children[v]) {
    if (next == p) continue;
    fill_data(next, v, d + 1);
    subsize[v] += subsize[next];
  }
}

// aux function for sack dfs
int cnt[MAXN];
void add(int v, int p, int x, int avoid = -1) {
  cnt[depth[v]] += x;
  for (int next : children[v]) {
    if (next == p || next == avoid) continue;
    add(next, v, x);
  }
}

// dfs uses sack technique to answer all queries offline
using Query = pair<int, int>;  // ( depth, answer )
vector<Query> queries;
vector<int> pending[MAXN];

bool visited_solve[MAXN] = {0};
void dfs_solve(int v, int p, bool keep) {
  visited_solve[v] = true;
  int max_size = -1, max_id = -1;

  for (int next : children[v])  // find biggest child
    if (next != p && subsize[next] > max_size)
      max_size = subsize[next], max_id = next;

  for (int next : children[v])  // solve for small children
    if (next != p && next != max_id) dfs_solve(next, v, 0);

  // solve for this node
  if (max_id != -1) dfs_solve(max_id, v, true);
  add(v, p, 1, max_id);

  for (int idx : pending[v])  // answer queries for this node
    queries[idx].second = cnt[queries[idx].first];

  if (!keep) add(v, p, -1);  // remove data if needed
}

// jump pointers table
vector<int> jump[MAXN];

void fill_jump_table(int v, int p) {
  if (p != -1) jump[v].push_back(p);

  for (int i = 1; (1 << i) < depth[v]; ++i)
    jump[v].push_back(jump[jump[v][i - 1]][i - 1]);

  for (int next : children[v])
    if (next != p) fill_jump_table(next, v);
}

int find_k_ancestor(int v, int k) {
  for (int i = 0; (1 << i) <= k; ++i)
    if ((1 << i) & k) v = jump[v][i];
  return v;
}

int main() {
  int n, m, v, p;
  cin >> n;
  children.resize(n + 1);

  // read data
  int parent;
  for (int node = 1; node <= n; ++node) {
    cin >> parent;
    if (parent == 0) continue;
    children[parent].push_back(node);
  }

  fore(i, 1, n + 1) if (depth[i] == 0) {
    fill_data(i, -1);
    fill_jump_table(i, -1);
  }

  // save queries
  cin >> m;
  while (m--) {
    cin >> v >> p;
    if (p >= depth[v]) {  // no p-ancestor
      queries.push_back({-1, 1});
      continue;
    }

    int pth = find_k_ancestor(v, p);
    pending[pth].push_back(queries.size());
    queries.push_back({depth[v], -1});
  }

  // answer queries with sack
  fore(i, 1, n + 1) if (visited_solve[i] == false) dfs_solve(i, -1, false);

  // print answers
  for (Query& query : queries) cout << (query.second - 1) << '\n';

  return 0;
}
