/*
Compute with fft convolution of ~A~A as powers of two and reversed bit
representation of ~B. That gives sums of ~A_i & ~B_i = 31 - (A_i | B_i).
*/
#include <bits/stdc++.h>
using namespace std;

using C = complex<double>;
using vl = vector<long long int>;
using vi = vector<int>;

double PI = acos(-1.0);

void dft_iterative(vector<C>& a, bool inv = false) {
  int n = a.size();
  if (n == 1) return;

  int L = __builtin_ctz(n);

  vector<C> roots(n);  // [n/2^(k+1), n/2^k) = (n/2^k)-th unity roots (1st half)
  for (int i = 0; i < n / 2; ++i)
    roots[n / 2 + i] = polar(1.0, 2.0 * PI * i / n * (inv ? -1.0 : 1.0));
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

int N;

int main() {
  cin >> N;
  vi A(N), B(N);
  for (int& el : A) cin >> el;
  for (int& el : B) cin >> el;

  // duplicate bitwise negation of A and make a vector with active powers of two
  vl A_powers;
  A_powers.reserve(2 * 5 * N);
  for (int i = 0; i < N; ++i)
    for (int j = 4; j >= 0; --j) A_powers.push_back((~A[i]) & (1 << j));
  for (int i = 0; i < 5 * N; ++i) A_powers.push_back(A_powers[i]);

  // reverse bit representation of bitwise negation of B
  vl B_reversed;
  B_reversed.reserve(5 * N);
  for (int i = N - 1; i >= 0; --i)
    for (int j = 0; j < 5; ++j)
      B_reversed.push_back(((~B[i]) & (1 << j)) ? 1 : 0);

  vl conv = multiply(A_powers, B_reversed);

  int ans = 0;
  int start = 5 * N - 1;              // first position of interest
  for (int i = 0; i < 5 * N; i += 5)  // each five positions, a new rotation
    ans = max(ans, 31 * N - (int)conv[start + i]);  // take negation (31 - x)

  cout << ans << '\n';

  return 0;
}
