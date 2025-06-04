/*
If len is the spacing between trees, iterate looking for the line segment that
acumulates k * len distance and compute the corresponding point.
*/
#include <bits/stdc++.h>
using namespace std;
#define fore(x, a, b) for (lli x = a, __lim__ = b; x < __lim__; ++x)
#define all(x) begin(x), end(x)

using lli = long long int;
using vi = vector<lli>;
using vb = vector<bool>;

struct Point {
  double x, y;

  void print() { cout << x << ' ' << y << '\n'; }
};

double distance(Point& a, Point& b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx * dx + dy * dy);
}

Point interpolate(Point& a, Point& b, double r) {
  return {a.x + r * (b.x - a.x), a.y + r * (b.y - a.y)};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int tests, k, t;
  cin >> tests;
  cout << fixed << setprecision(2);
  fore(test, 1, tests + 1) {
    cout << "Road #" << test << ":\n";

    cin >> k >> t;
    vector<Point> points(k);
    vector<double> distances(k - 1);  // line segments lengths
    fore(i, 0, k) {
      cin >> points[i].x >> points[i].y;
      if (i > 0) distances[i - 1] = distance(points[i - 1], points[i]);
    }
    vector<double> cum_distances(k - 1);
    partial_sum(all(distances), cum_distances.begin());

    double len = cum_distances.back() / (t - 1);  // spacing between trees
    int curr_road = 0;
    points[0].print();
    fore(i, 1, t - 1) {  // print intermediate trees
      double target = len * i;
      while (cum_distances[curr_road] < target) ++curr_road;

      double ratio = target;
      if (curr_road > 0) ratio -= cum_distances[curr_road - 1];
      ratio /= distances[curr_road];

      interpolate(points[curr_road], points[curr_road + 1], ratio).print();
    }
    points.back().print();
    cout << '\n';
  }
  return 0;
}
