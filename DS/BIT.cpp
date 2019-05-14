template <typename T> // T needs to implement +/- operators
class BIT { // Point updates, range sum queries.
	vector<T> B; public: BIT (int n) : B(n+1) {}
	T get(int r) { T res = B[++r]; while(r) res += B[r -= (r & -r)]; return res; }
	T get(int l, int r) { return l ? get(r) - get(l-1) : get(r); }
	void add(int i, T val) { B[++i] += val; while(i <= B.size()) B[i += (i & -i)] += val; }
};
template <typename T> // T needs to implement +/- operators
class RangeBIT {
	BIT<T> B0, B1; public: RangeBIT(int n) : B0(n), B1(n) {}
	void add(int l, int r, T val) { B0.add(l, val); B0.add(r+1, -val); B1.add(l, val*(l-1)); B1.add(r+1, -val*r); }
	T get(int l, int r) { return B0.get(r) * (r) - B0.get(l-1) * (l-1) + B1.get(l-1) - B1.get(r); }
};
