/*
Capacity is the area of the polygon times the width. Compute initial water and
simulate the spent and rain water to detect lack/excess of water.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;

using Point = pair<lli, lli>;
using Polygon = vector<Point>;
double area(const Polygon& poly) {
  lli res = 0;
  for (int i = 0, n = poly.size(); i < n; ++i) {
    int j = (i + 1) % n;
    res += poly[i].first * poly[j].second - poly[i].second * poly[j].first;
  }
  return abs(res) / 2.0;
}

int main() {
  lli t, n, w;
  double initial_percentage, spent_water, rain_water;
  cin >> t;
  while (t--) {
    cin >> n;
    Polygon poly(n);
    for (Point& p : poly) cin >> p.first >> p.second;
    cin >> w >> initial_percentage >> spent_water >> rain_water;

    double capacity = area(poly) * w;
    double water = capacity * (initial_percentage / 100.0);

    water -= spent_water;
    if (water < 0) {
      cout << "Lack of water. ";
      water = 0;
    }

    water += rain_water;
    if (water > capacity) {
      cout << "Excess of water. ";
      water = capacity;
    }

    int final_percentage = int(water / capacity * 100.0);
    cout << "Final percentage: " << final_percentage << "%\n";
  }
  return 0;
}
