/*
Try all producers prices and keep that one that give the lowest angriness.
Sort so this can be done efficiently.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

vector<int> producers, consumers;

pair<int, int> solve() {
  sort(all(producers));
  sort(all(consumers));
  int price = 0, angry = producers.size();  // best options so far

  int j = 0;
  for (int i = 0; i < producers.size(); ++i) {
    while (j < consumers.size() && consumers[j] < producers[i]) ++j;
    int n_angry = j + producers.size() - i - 1;
    if (n_angry < angry) price = producers[i], angry = n_angry;
  }
  return {price, angry};
}

int main() {
  int t, p, c;
  cin >> t;
  while (t--) {
    cin >> p >> c;
    producers.resize(p);
    consumers.resize(c);
    for (int& el : producers) cin >> el;
    for (int& el : consumers) cin >> el;

    auto ans = solve();
    cout << ans.first << ' ' << ans.second << '\n';
  }
  return 0;
}
