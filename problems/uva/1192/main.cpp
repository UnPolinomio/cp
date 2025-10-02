/*
Using dp[i][j] = max score alignment for first i and j letters of both strings.
In the transition we have three posibilities (gaps and match/mismatch).
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

constexpr int s_match = 5, s_mismatch = -4, s_gap = -7;
int score(string& a, string& b) {
  vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));
  for (int i = 1; i <= a.size(); ++i) dp[i][0] = dp[i - 1][0] + s_gap;
  for (int i = 1; i <= b.size(); ++i) dp[0][i] = dp[0][i - 1] + s_gap;

  for (int i = 1; i <= a.size(); ++i) {
    for (int j = 1; j <= b.size(); ++j) {
      int s1 = dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? s_match : s_mismatch);
      int s2 = dp[i - 1][j] + s_gap;
      int s3 = dp[i][j - 1] + s_gap;
      dp[i][j] = max({s1, s2, s3});
    }
  }

  return dp[a.size()][b.size()];
}

int main() {
  string line;
  string query, data;

  getline(cin, query);
  getline(cin, query);

  vector<string> best_sequences;
  int max_score = INT_MIN;

  while (getline(cin, line)) {
    if (line[0] != '>') continue;
    getline(cin, data);

    int similarity = score(query, data);
    if (similarity < max_score) continue;

    if (similarity > max_score) {
      max_score = similarity;
      best_sequences.clear();
    }
    best_sequences.push_back(data);
  }

  cout << "The query sequence is:" << '\n';
  cout << query << "\n\n";
  cout << "The most similar sequences are:" << "\n\n";

  for (int i = 0; i < best_sequences.size(); ++i) {
    cout << best_sequences[i] << '\n';
    cout << "The similarity score is: " << max_score << '\n';
    if (i < best_sequences.size() - 1) cout << '\n';
  }

  return 0;
}
