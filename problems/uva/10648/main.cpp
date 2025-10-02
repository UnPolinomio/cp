/*
Using inclusion-exclusion principle over sets A_i = Box i is empty, so we can
calculate |A_1 U ...U A_m| / m^n
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using ftype = long double;

int main() {
  ftype n, m;

  int test = 1;

  cout << fixed << setprecision(7);
  while (cin >> n) {
    if (n == -1) break;
    cin >> m;
    cout << "Case " << (test++) << ": ";

    ftype ans = 0;
    ftype m_choose_k = 1;
    ftype curr_term;
    fore(k, 1, m + 1) {
      m_choose_k *= (m - (k - 1)) / k;
      curr_term = m_choose_k * pow(1 - k / m, n);
      if (k % 2 == 1)
        ans += curr_term;
      else
        ans -= curr_term;
    }

    cout << ans << '\n';
  }

  return 0;
}
