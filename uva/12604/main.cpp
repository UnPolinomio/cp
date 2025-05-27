/*
Modular differences are preserved on shift. Compute KMP prefix function on the
difference array to find mathches, for each match check corresponding shift.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

int sigma[128];
int sigma_sz;

// adds modular differences for string s to the end of arr
void process_string(string& s, vector<int>& arr) {
  for (int i = 1; i < s.size(); ++i) {
    int prev = sigma[s[i - 1]];
    int curr = sigma[s[i]];
    arr.push_back((curr - prev + sigma_sz) % sigma_sz);
  }
}

vector<int> prefix_function(vector<int>& arr) {
  vector<int> pi(arr.size(), 0);
  for (int i = 1; i < arr.size(); ++i) {
    int j = pi[i - 1];
    while (j > 0 && arr[i] != arr[j]) j = pi[j - 1];
    if (arr[i] == arr[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

int main() {
  int t;
  string A, W, S;
  cin >> t;
  while (t--) {
    cin >> A >> W >> S;
    for (int i = 0; i < A.size(); ++i) sigma[A[i]] = i;
    sigma_sz = A.size();

    vector<int> arr;
    process_string(W, arr);  // add pattern differences
    arr.push_back(127);      // unused char
    process_string(S, arr);  // add text differences
    auto pi = prefix_function(arr);
    int pattern_sz = W.size() - 1;

    vector<int> shifts(sigma_sz);
    // if pattern_sz == 0 we want to check every char in S (including first)
    for (int i = pattern_sz + (pattern_sz == 0 ? 0 : 1); i < pi.size(); ++i) {
      if (pi[i] != pattern_sz) continue;  // find just full match
      int occ_pos = i - 2 * pattern_sz;
      int prev = sigma[W[0]];
      int curr = sigma[S[occ_pos]];
      // for this match we would need to make this shift
      int shift = (curr - prev + sigma_sz) % sigma_sz;
      ++shifts[shift];
    }

    vector<int> unique_shifts;
    for (int i = 0; i < sigma_sz; ++i)
      if (shifts[i] == 1) unique_shifts.push_back(i);

    if (unique_shifts.size() == 0)
      cout << "no solution";
    else if (unique_shifts.size() == 1)
      cout << "unique:";
    else
      cout << "ambiguous:";

    for (int shift : unique_shifts) cout << ' ' << shift;

    cout << '\n';
  }
  return 0;
}
