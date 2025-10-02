/*
Make a greedy strategy. Prefer the following actions in this order: make tie a
win, make a lost a win, make a lost a tie. While we have money left make actions
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

int main() {
  int N, G, s, r;
  while (cin >> N >> G) {
    int max_score = 0;
    vector<int> lost;  // budget needed to win that match
    while (N--) {
      cin >> s >> r;
      if (s > r)
        max_score += 3;  // win
      else if (s == r) {
        if (G) {
          max_score += 3;  // tie made win
          --G;
        } else {
          max_score += 1;  // tie
        }
      } else {
        lost.push_back(r - s);
      }
    }
    sort(lost.begin(), lost.end());
    for (int price : lost) {
      if (G < price) break;
      if (G >= price + 1) {  // lost made win
        max_score += 3;
        G -= price + 1;
      } else if (G == price) {  // lost made tie
        max_score += 1;
        --G;
      }
    }
    cout << max_score << '\n';
  }
  return 0;
}
