/*
Make a ST that counts the # of matches () that can be done and remaining ), (
in a given range. Then combine can be done efficiently as in the method below.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

struct Node {
  int matched, open, close;  // # of (), (, ) resp.
};

constexpr int MAXN = 1000001;
Node tree[2 * MAXN];

// returns the result of combining the string represented by two nodes.
Node combine(Node& left, Node& right) {
  Node out;
  int new_matches = min(left.open, right.close);
  out.matched = left.matched + right.matched + new_matches;
  out.open = left.open + right.open - new_matches;
  out.close = left.close + right.close - new_matches;
  return out;
}

void build(string& s) {
  for (int i = 0; i < s.size(); ++i) {  // fill leaves
    if (s[i] == '(') tree[MAXN + 1 + i].open = 1;
    if (s[i] == ')') tree[MAXN + 1 + i].close = 1;
  }

  for (int i = MAXN - 1; i > 0; --i)  // fill all segment tree
    tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
}

int query(int l, int r) {
  Node left{}, right{};  // helpers to combine chosen nodes in the tree

  for (l += MAXN, r += MAXN; l <= r; l >>= 1, r >>= 1) {
    if (l & 1) left = combine(left, tree[l++]);
    if (!(r & 1)) right = combine(tree[r--], right);
  }

  return 2 * combine(left, right).matched;  // length is twice the number of ()
}

int main() {
  int m, l, r;
  string s;
  cin >> s >> m;
  build(s);
  while (m--) {
    cin >> l >> r;
    cout << query(l, r) << '\n';
  }
  return 0;
}
