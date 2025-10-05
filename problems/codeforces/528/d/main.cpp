/*
For each char c, mark positions in S with a c near them. Compute convolution
with reversed T (c chars are 1's) and sum over all chars -> total matched chars
*/
#include <bits/stdc++.h>
using namespace std;

using C = complex<double>;
using vl = vector<long long int>;
using vi = vector<int>;

const double PI = acos(-1.0);

void dft_iterative(vector<C>& a, bool inv = false) {
  int n = a.size();
  if (n == 1) return;

  int L = __builtin_ctz(n);

  vector<C> roots(n);
  for (int i = 0; i < n / 2; ++i)
    roots[n / 2 + i] = polar(1.0, 2.0 * PI * i / n * (inv ? -1.0 : 1.0));
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

vl multiply(const vl& A, const vl& B) {
  int n = A.size(), m = B.size();
  if (n == 1 && m == 1) return {A[0] * B[0]};
  vector<C> a(n), b(m);
  for (int i = 0; i < n; ++i) a[i] = A[i];
  for (int i = 0; i < m; ++i) b[i] = B[i];

  int sz = n + m - 1;
  int L = 1 << (32 - __builtin_clz(sz - 1));
  a.resize(L);
  b.resize(L);
  dft_iterative(a);
  dft_iterative(b);
  vector<C> c(L);
  for (int i = 0; i < L; ++i) c[i] = a[i] * b[i];
  dft_iterative(c, true);

  vl C(sz);
  for (int i = 0; i < sz; ++i) C[i] = llround(real(c[i]));
  return C;
}

string s, t;
int k, N, M;

// convolution of s and t^R using 0's and 1's (c = 1) and k width for c's in s
vl char_convolution(char c) {
  vl S(N), T(M);

  // difference array to mark if there's a c near (k width) the curr position
  for (int i = 0; i < N; ++i) {
    if (s[i] != c) continue;
    int l = max(i - k, 0);
    int r = i + k + 1;
    ++S[l];
    if (r < N) --S[r];
  }
  for (int i = 1; i < N; ++i) S[i] += S[i - 1];
  for (int i = 0; i < N; ++i) S[i] = (S[i] > 0) ? 1 : 0;

  // reverse t
  for (int i = 0; i < M; ++i)
    if (t[M - 1 - i] == c) T[i] = 1;

  return multiply(S, T);
}

int main() {
  cin >> N >> M >> k >> s >> t;

  vector<int> acc(N - M + 1);
  for (char c : {'A', 'T', 'G', 'C'}) {
    vl res = char_convolution(c);
    for (int i = 0; i < acc.size(); ++i)  // add # of c's matched on position i
      acc[i] += res[M - 1 + i];
  }

  int ans = 0;
  for (int i = 0; i < acc.size(); ++i)  // total chars matched == |s| ?
    if (acc[i] == M) ++ans;
  cout << ans << '\n';

  return 0;
}
