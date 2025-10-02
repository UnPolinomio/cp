/*
Use Sprague-Grundy. To compute groundy number for one pile memo[i][mask]
represents the number for state i stones and available movements in mask
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;
using ii = pair<lli, lli>;

// removed set bits for moves more that max allowed
lli clean_moves(lli moves, lli max_allowed, lli max_prev_allowed) {
  for (int i = max_allowed + 1; i <= max_prev_allowed; ++i)
    if (moves & (1LL << i))  // usar 1LL en vez de 1
      moves ^= (1LL << i);
  return moves;
}

map<ii, lli> memo;
lli get_grundy(lli cnt, lli moves) {
  if (moves == 0) return 0;
  if (memo.count({cnt, moves})) return memo[{cnt, moves}];

  set<int> grundies;
  for (lli move = 1; move <= cnt; ++move) {
    if (!(moves & (1LL << move))) continue;  // try to make each available move
    int next_cnt = cnt - move;
    int next_moves = clean_moves(moves ^ (1LL << move), next_cnt, cnt);
    grundies.insert(get_grundy(next_cnt, next_moves));
  }
  int mex = 0;
  while (grundies.count(mex)) ++mex;

  return memo[{cnt, moves}] = mex;
}

int main() {
  int n, s;
  cin >> n;
  int xor_sum = 0;
  while (n--) {
    cin >> s;
    xor_sum ^= get_grundy(s, ((1LL << s) - 1LL) << 1);  // usar 1LL aquí también
  }
  if (xor_sum != 0)  // winner
    cout << "NO\n";
  else
    cout << "YES\n";
  return 0;
}
