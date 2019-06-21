template <typename T> // T needs to implement +/- operators
class BIT { // Point updates, range sum queries.
	vector<T> B; public: BIT (int n) : B(n+1) { }
  // sum [0, r)
  T query(int r) { T res = T(); while (r > 0) { res += B[r], r -= (r & -r); } return res; }
  // sum [l, r)
	T query(int l, int r) { return (l == r ? T() : query(r) - query(l)); }
  // BIT[i] += val
	void add(int i, T val) { for (++i; i < B.size(); B[i] += val, i += (i & -i)); }
};

template <typename T> // T needs to implement +/- operators
class RangeBIT { // TODO untested!!
	BIT<T> B0, B1; public: RangeBIT(int n) : B0(n), B1(n) {}
	void add(int l, int r, T val) { B0.add(l, val); B0.add(r+1, -val); B1.add(l, val*(l-1)); B1.add(r+1, -val*r); }
	T get(int l, int r) { return B0.get(r) * (r) - B0.get(l-1) * (l-1) + B1.get(l-1) - B1.get(r); }
};
