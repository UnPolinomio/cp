/*
Using dynamic programming compute the number of ways to destroy all the robots
activated in a given bitmask. Transition is done taking submasks with size -1.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;

int weapons[17];  // input matrix using bits
int n;

int acum_weapons[1 << 16];  // available weapons if bitmask robots destroyed
void build_acum_weapons() {
  acum_weapons[0] = weapons[0];
  fore(msk, 1, 1 << n) {
    int bit = 31 - __builtin_clz(msk);  // add this bit robot to be destroyed
    acum_weapons[msk] = acum_weapons[msk ^ (1 << bit)] | weapons[bit + 1];
  }
}

lli dp[1 << 16];  // number of ways to destroy robots in mask
void build_dp() {
  dp[0] = 1;
  fore(msk, 1, 1 << n) {
    dp[msk] = 0;
    for (int i = 0; i < n; ++i) {
      if (!(msk & (1 << i))) continue;  // i-th robot not in mask
      // if i-th robot can be destroyed with other mask robots weapons
      if (acum_weapons[msk ^ (1 << i)] & (1 << i))
        dp[msk] += dp[msk ^ (1 << i)];
    }
  }
}

int main() {
  int t;
  char ch;
  cin >> t;
  fore(test, 1, t + 1) {
    cin >> n;
    fore(weapon, 0, n + 1) {
      int state = 0;
      for (int i = 0; i < n; ++i) {
        cin >> ch;
        if (ch == '1') state ^= 1 << i;
      }
      weapons[weapon] = state;
    }

    build_acum_weapons();
    build_dp();

    cout << "Case " << test << ": " << dp[(1 << n) - 1] << '\n';
  }
  return 0;
}
