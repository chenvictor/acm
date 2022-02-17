/**
 * Source: Simon Lindholm
 * add line mx+b
 * query max point at x
 * O(log n)
 **/
struct Line {
  mutable ll m, b, p;
  bool operator<(const Line& o) const {
    return m > o.m; // > for query min!
  }
  bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line,less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	static ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
    auto& [m,b,p] = *x;
		if (y == end()) { return p = inf, 0; }
    auto [ym,yb,yp] = *y;
    return (p = m==ym ? (b > yb ? inf : -inf)
                      : div(yb-b, m-ym)) >= yp;
	}
	void add(ll m, ll b) {
		auto z = insert({m, b, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
    auto [m,b,_] = *lower_bound(x);
    return m*x+b;
	}
};

