/*
We can directly compute possible child blood types given parents. To guess a
parent we try all blood types and check wether the given child type is valid.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

vector<string> abo_types{"A", "B", "O", "AB"};
vector<string> abo_alleles{"A", "B", "O"};
using Blood = pair<int, bool>;  // (abo_type, rh)

vector<int> get_abo_alleles(int abo_type) {
  if (abo_type == 0) return {0, 2};
  if (abo_type == 1) return {1, 2};
  if (abo_type == 2) return {2};
  if (abo_type == 3) return {0, 1};
}

int get_abo_type(int allele_a, int allele_b) {
  if (allele_a == allele_b) return allele_a;
  if (allele_a > allele_b) swap(allele_a, allele_b);
  if (allele_b == 2) return allele_a;
  return 3;  // AB
}

// returns possible resulting abo types and wether both rh or just -
pair<vector<bool>, bool> combine(const Blood& a, const Blood& b) {
  vector<bool> valid_abo_type(4);
  for (int x : get_abo_alleles(a.first))
    for (int y : get_abo_alleles(b.first))
      valid_abo_type[get_abo_type(x, y)] = true;

  return {valid_abo_type, a.second || b.second};
}

// parses blood type from input string
Blood parse_blood_type(string& s) {
  if (s.size() == 3) return {3, s[2] == '+'};
  int type;
  if (s[0] == 'A') type = 0;
  if (s[0] == 'B') type = 1;
  if (s[0] == 'O') type = 2;

  return {type, s[1] == '+'};
}

void print_child(pair<vector<bool>, bool>& options) {
  int count = 0;
  for (int i = 0; i < 4; ++i)
    if (options.first[i]) ++count;

  bool use_braces = options.second || count > 1;

  bool first = true;
  for (int i = 0; i < 4; ++i) {
    if (!options.first[i]) continue;
    if (first) {
      if (use_braces) cout << '{';
      first = false;
    } else {
      cout << ", ";
    }
    cout << abo_types[i] << "-";
    if (options.second) cout << ", " << abo_types[i] << "+";
  }
  if (use_braces) cout << "}";
}

void print_parent(const Blood& parent, const Blood& child) {
  bool first = true;
  for (int j = 0; j < 4; ++j) {
    for (int rh = 0; rh <= 1; ++rh) {
      auto options = combine(parent, Blood{j, rh == 1});
      if (!options.first[child.first]) continue;
      if (!options.second && child.second) continue;
      if (first) {
        first = false;
        cout << '{';
      } else {
        cout << ", ";
      }
      cout << abo_types[j] << (rh == 1 ? '+' : '-');
    }
  }

  if (first)
    cout << "IMPOSSIBLE";
  else
    cout << '}';
}

int main() {
  string a, b, c;
  for (int test = 1;; ++test) {
    cin >> a >> b >> c;
    if (a == "E") break;

    cout << "Case " << test << ": ";

    if (c == "?") {
      cout << a << ' ' << b << ' ';
      auto options = combine(parse_blood_type(a), parse_blood_type(b));
      print_child(options);
    } else if (a == "?") {
      print_parent(parse_blood_type(b), parse_blood_type(c));
      cout << ' ' << b << ' ' << c;
    } else {  // b == ?
      cout << a << ' ';
      print_parent(parse_blood_type(a), parse_blood_type(c));
      cout << ' ' << c;
    }
    cout << '\n';
  }
  return 0;
}
