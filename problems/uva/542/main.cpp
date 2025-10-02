/*
A state gives the probability for an outcome in each node. Combine two nodes
to get the probabilities in the children node. Do 4 steps.
*/

#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

using State = array<double, 16>;

double probs[16][16];

State combine(State& s, State& t) {
  State state = {};

  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      double prob = s[i] * t[j];
      state[i] += prob * probs[i][j];
      state[j] += prob * probs[j][i];
    }
  }

  return state;
}

int main() {
  vector<string> countries(16);
  for (int i = 0; i < 16; ++i) cin >> countries[i];

  for (int i = 0; i < 16; ++i)
    for (int j = 0; j < 16; ++j) {
      cin >> probs[i][j];
      probs[i][j] /= 100;
    }

  vector<State> states(16, State{});
  for (int i = 0; i < 16; ++i) states[i][i] = 1;  // initial state

  // after 4 steps we get final node
  for (int step = 1; step <= 4; ++step) {
    vector<State> new_states;
    for (int i = 0; i < states.size(); i += 2) {
      State tmp = combine(states[i], states[i + 1]);
      new_states.push_back(tmp);
    }
    swap(states, new_states);
  }

  // print result
  for (int i = 0; i < 16; ++i) {
    cout << countries[i] << string(11 - countries[i].length(), ' ')
         << "p=" << fixed << setprecision(2) << states[0][i] * 100 << "%"
         << '\n';
  }

  return 0;
}
