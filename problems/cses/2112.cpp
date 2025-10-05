/*
Compute convolution of binary vector and its reverse using fft.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using C = complex<double>;
using vl = vector<long long int>;
using vi = vector<int>;

void dft_iterative(vector<C>& a, bool inv = false) {
  int n = a.size();
  if (n == 1) return;

  int L = __builtin_ctz(n);

  vector<C> roots(n);
  for (int i = 0; i < n / 2; ++i)
    roots[n / 2 + i] = polar(1.0, 2.0 * M_PI * i / n * (inv ? -1.0 : 1.0));
  for (int i = n / 2 - 1; i > 0; --i) roots[i] = roots[2 * i];

  vi rev(n);
  for (int i = 1; i < n; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
  for (int i = 0; i < n; ++i)
    if (i < rev[i]) swap(a[i], a[rev[i]]);

  for (int len = 1; len < n; len *= 2) {
    for (int i = 0; i < n; i += 2 * len) {
      for (int j = 0; j < len; ++j) {
        C z = a[i + len + j] * roots[len + j];
        a[i + len + j] = a[i + j] - z;
        a[i + j] += z;
      }
    }
  }

  if (inv)
    for (int i = 0; i < n; ++i) a[i] /= n;
}

vector<C> convolution(vector<C> a, vector<C> b) {
  int final_size = a.size() - 1 + b.size();
  if (final_size == 1) return {a[0] * b[0]};

  int N = 1 << (32 - __builtin_clz(final_size - 1));
  a.resize(N);
  b.resize(N);
  dft_iterative(a);
  dft_iterative(b);

  vector<C> c(N);
  for (int i = 0; i < N; ++i) c[i] = a[i] * b[i];
  dft_iterative(c, true);
  c.resize(final_size);

  return c;
}

vl multiply(vl& A, vl& B) {
  int n = A.size(), m = B.size();
  vector<C> a(n), b(m);
  for (int i = 0; i < n; ++i) a[i] = A[i];
  for (int i = 0; i < m; ++i) b[i] = B[i];
  vector<C> c = convolution(a, b);
  vl C(c.size());
  for (int i = 0; i < C.size(); ++i) C[i] = llround(real(c[i]));
  return C;
}

int main() {
  string s;
  cin >> s;
  int n = s.size();
  vl p(n), pr(n);
  for (int i = 0; i < n; ++i) p[i] = s[i] - '0', pr[n - 1 - i] = s[i] - '0';

  vl prod = multiply(p, pr);
  for (int k = 1; k < n; ++k) cout << prod[n - 1 + k] << ' ';
  cout << '\n';

  return 0;
}
