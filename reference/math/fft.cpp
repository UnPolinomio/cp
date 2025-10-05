#include <bits/stdc++.h>
using namespace std;

using C = complex<double>;
using vl = vector<long long int>;
using vi = vector<int>;

vector<C> dft_recursive(const vector<C>& a, bool inv = false) {
  int n = a.size();
  if (n == 1) return a;

  vector<C> a0(n / 2);
  vector<C> a1(n / 2);
  for (int i = 0; i < n / 2; ++i) {
    a0[i] = a[2 * i];
    a1[i] = a[2 * i + 1];
  }

  vector<C> y0 = dft_recursive(a0, inv);
  vector<C> y1 = dft_recursive(a1, inv);

  C wn = polar(1.0, 2.0 * M_PI / n * (inv ? -1.0 : 1.0));
  C w = 1;
  vector<C> y(n);
  for (int i = 0; i < n / 2; ++i) {
    y[i] = y0[i] + w * y1[i];
    y[n / 2 + i] = y0[i] - w * y1[i];
    w *= wn;
  }

  if (inv)
    for (int i = 0; i < n; ++i) y[i] /= 2.0;

  return y;
}

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
  vl A = {1, 1, 1};
  vl B = {1, 4, 5, 6, 7, 8, 3, 5, 7};

  vl result = multiply(A, B);

  cout << "Result: ";
  for (int i = 0; i < result.size(); ++i) cout << result[i] << ' ';

  cout << '\n';

  return 0;
}
