#include <bits/stdc++.h>
using namespace std;

using C = complex<double>;
using vl = vector<long long int>;
using vi = vector<int>;

vector<C> dft_recursive(const vector<C>& a, bool inv = false) {
  int n = a.size();
  if (n == 1) return a;

  // subproblems
  vector<C> a0(n / 2);
  vector<C> a1(n / 2);
  for (int i = 0; i < n / 2; ++i) {
    a0[i] = a[2 * i];
    a1[i] = a[2 * i + 1];
  }

  vector<C> y0 = dft_recursive(a0, inv);
  vector<C> y1 = dft_recursive(a1, inv);

  // combine solutions to odd and even positions
  C wn = polar(1.0, 2.0 * M_PI / n * (inv ? -1.0 : 1.0));
  C w = 1;
  vector<C> y(n);
  for (int i = 0; i < n / 2; ++i) {
    y[i] = y0[i] + w * y1[i];
    y[n / 2 + i] = y0[i] - w * y1[i];
    w *= wn;
  }

  if (inv)  // should divide by n (equiv divide by two in each recursion level)
    for (int i = 0; i < n; ++i) y[i] /= 2.0;

  return y;
}

void dft_iterative(vector<C>& a, bool inv = false) {
  int n = a.size();
  if (n == 1) return;

  int L = __builtin_ctz(n);

  vector<C> roots(n);  // [n/2^(k+1), n/2^k) = (n/2^k)-th unity roots (1st half)
  for (int i = 0; i < n / 2; ++i)
    roots[n / 2 + i] = polar(1.0, 2.0 * M_PI * i / n * (inv ? -1.0 : 1.0));
  for (int i = n / 2 - 1; i > 0; --i) roots[i] = roots[2 * i];

  vi rev(n);  // rev[i] = i (as L bit) reversed
  for (int i = 1; i < n; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
  for (int i = 0; i < n; ++i)
    if (i < rev[i]) swap(a[i], a[rev[i]]);

  for (int len = 1; len < n; len *= 2) {    // combining arrays of size len
    for (int i = 0; i < n; i += 2 * len) {  // start of those two arrays
      for (int j = 0; j < len; ++j) {       // iterate over their positions
        C z = a[i + len + j] * roots[len + j];
        a[i + len + j] = a[i + j] - z;
        a[i + j] += z;
      }
    }
  }

  if (inv)
    for (int i = 0; i < n; ++i) a[i] /= n;
}

vl multiply(const vl& A, const vl& B) {
  // to complex vector
  int n = A.size(), m = B.size();
  if (n == 1 && m == 1) return {A[0] * B[0]};
  vector<C> a(n), b(m);
  for (int i = 0; i < n; ++i) a[i] = A[i];
  for (int i = 0; i < m; ++i) b[i] = B[i];

  // fft
  int sz = n + m - 1;
  int L = 1 << (32 - __builtin_clz(sz - 1));
  a.resize(L);
  b.resize(L);
  dft_iterative(a);
  dft_iterative(b);
  vector<C> c(L);
  for (int i = 0; i < L; ++i) c[i] = a[i] * b[i];
  dft_iterative(c, true);

  // back to reals
  vl C(sz);
  for (int i = 0; i < sz; ++i) C[i] = llround(real(c[i]));
  return C;
}

int main() {
  vl A = {1, 1, 1};
  vl B = {1, 4, 5, 6, 7, 8, 3, 5, 7};

  vl result = multiply(A, B);

  cout << "Result: ";
  for (int i = 0; i < result.size(); ++i) cout << result[i] << ' ';

  cout << '\n';

  return 0;
}
