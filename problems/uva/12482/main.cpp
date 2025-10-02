/*
Add as many words as you can in the current line, then create a new line a
continue. The answer will be ceil(line_count / L).
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

int main() {
  int N, L, C;
  string s;
  while (cin >> N >> L >> C) {
    cin.ignore();

    int line_count = 0;
    int line_length = 0;
    while (N--) {
      cin >> s;
      if (line_length == 0 || line_length + 1 + s.size() > C) {
        ++line_count;
        line_length = s.size();
      } else
        line_length += 1 + s.size();
    }

    int ans = line_count / L;
    if (line_count % L != 0) ++ans;

    cout << ans << '\n';
  }
  return 0;
}
