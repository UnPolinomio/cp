/*
Given 1st and 2nd lamp heights you can solve a recurrence that gives you any
lamp height. Make bs on the second lamp height checking all have >=0 heights.
*/

#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

int N;
double a;

// height of the n-th (zero indexed) lamp if the second lamp height is h
double height(double h, int n) { return h * n - a * (n - 1) + n * (n - 1); }

// if second lamp height is h, are all heights non-negative?
bool valid(double h) {
  for (int n = 0; n < N; ++n) {
    double curr = height(h, n);
    if (curr < 0) return false;
  }
  return true;
}

int main() {
  while (cin >> N >> a) {
    double l = 0;
    double r = a;

    fore(i, 0, 30) {
      double mid = (l + r) / 2;
      if (valid(mid))
        r = mid;
      else
        l = mid;
    }

    double ans = height(r, N - 1);

    cout << fixed << setprecision(2) << ans << '\n';
  }

  return 0;
}
