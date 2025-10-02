/*
Flow network: source → clubs → people → parties → sink with capacity 1 except
for the last segment limited by max allowed per party. Max-flow gives solution.
*/

#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

struct Edge {
  int from, to, flow, cap;
};

struct MaxFlow {
  int n;
  vector<Edge> edges;
  vector<vector<int>> adj;

  MaxFlow(int n) : n(n), adj(n) {}

  void add_edge(int u, int v, int cap) {
    adj[u].push_back(edges.size());
    edges.push_back({u, v, 0, cap});
    adj[v].push_back(edges.size());
    edges.push_back({v, u, 0, 0});
  }

  int bfs(int s, int t) {
    vector<int> path(n, -1);
    queue<int> pending;
    pending.push(s);
    path[s] = 0;

    // find path
    bool found = false;
    while (!pending.empty() && !found) {
      int node = pending.front();
      pending.pop();

      for (int edge_idx : adj[node]) {
        Edge& edge = edges[edge_idx];
        if (edge.flow == edge.cap) continue;
        if (path[edge.to] != -1) continue;
        path[edge.to] = edge_idx;
        pending.push(edge.to);

        if (edge.to == t) found = true;
      }
    }

    if (!found) return 0;

    // find min cap in path
    int curr = t;
    int flow = INT_MAX;
    while (curr != s) {
      Edge& edge = edges[path[curr]];
      flow = min(flow, edge.cap - edge.flow);
      curr = edge.from;
    }

    // apply path
    curr = t;
    while (curr != s) {
      int edge_idx = path[curr];
      edges[edge_idx].flow += flow;
      edges[edge_idx ^ 1].flow -= flow;
      curr = edges[edge_idx].from;
    }

    return flow;
  }

  int max_flow(int s, int t) {
    int flow = 0, pushed;
    while (pushed = bfs(s, t)) flow += pushed;
    return flow;
  }
};

struct Person {
  string name;
  int party;
  vector<int> clubs;
};

int main() {
  int T;
  string line;
  cin >> T;
  getline(cin, line);
  getline(cin, line);

  string name, party, club;
  fore(test, 0, T) {
    if (test != 0) cout << '\n';

    // read data
    int party_cnt = 0;
    unordered_map<string, int> party_to_idx, clubs_to_idx;
    vector<Person> people;
    vector<string> clubs;

    while (getline(cin, line)) {
      if (line.empty()) break;

      istringstream iss(line);
      iss >> name >> party;
      if (!party_to_idx.count(party)) party_to_idx[party] = party_cnt++;
      people.push_back({name, party_to_idx[party], {}});

      while (iss >> club) {
        if (!clubs_to_idx.count(club)) {
          clubs_to_idx[club] = clubs.size();
          clubs.push_back(club);
        }

        people.back().clubs.push_back(clubs_to_idx[club]);
      }
    }

    // create flow network
    MaxFlow mf(clubs.size() + people.size() + party_cnt + 2);

    // index for each type of node
    int club_idx = 0;
    int person_idx = clubs.size();
    int party_idx = clubs.size() + people.size();
    int source_idx = clubs.size() + people.size() + party_cnt;

    // clubs -> people
    for (int i = 0; i < people.size(); ++i)
      for (int club : people[i].clubs)
        mf.add_edge(club_idx + club, person_idx + i, 1);

    int critial_edges = mf.edges.size();  // relevant edges to print solution

    // people -> parties
    for (int i = 0; i < people.size(); ++i)
      mf.add_edge(person_idx + i, party_idx + people[i].party, 1);

    // source -> clubs
    fore(i, club_idx, person_idx) mf.add_edge(source_idx, i, 1);

    // parties -> sink
    int max_per_party = (clubs.size() - 1) / 2;
    fore(i, party_idx, source_idx)
        mf.add_edge(i, source_idx + 1, max_per_party);

    // found solution with all club assigned?
    if (mf.max_flow(source_idx, source_idx + 1) != clubs.size()) {
      cout << "Impossible.\n";
      continue;
    }

    // print found solution
    for (int i = 0; i < critial_edges; i += 2) {
      Edge& edge = mf.edges[i];
      if (edge.flow != 1) continue;  // edge is not used

      cout << people[edge.to - person_idx].name << ' '
           << clubs[edge.from - club_idx] << '\n';
    }
  }
  return 0;
}
