// Basic Imports
#include <bits/stdc++.h>
using namespace std;
// Mini testing framework
template <typename T>
void _assertEquals(T expected, T actual, int line) {
	if (expected != actual) {
		cerr << "LINE " << line << ": assertion failed.\n";
		cerr << "  Expected: " << expected << "\n";
		cerr << "  Actual:   " << actual << endl;
		exit(-1);
	}
}
#define assertEquals(expected, actual) _assertEquals(expected, actual, __LINE__)

template <typename T> class Segtree {
	int n; vector<T> data; function<T(T,T)> merge;
	void build() { for (int i = n - 1; i > 0; --i) data[i] = merge(data[i<<1], data[i<<1|1]); }
	public:
		Segtree(int n, function<T(T,T)> f) : n(n), data(2*n), merge(f) { build(); }
		Segtree(int n, T val, function<T(T,T)> f) : n(n), data(2*n, val), merge(f) { build(); }
		Segtree(vector<T>& init, function<T(T,T)> f) : n(init.size), data(2*n), merge(f) {
			copy(init.begin(), init.end(), data.begin() + n); build();
		}
		T get(int idx) { return data[n+idx]; }
		void set(int idx, T value) { for (data[idx += n] = value; idx > 1; idx >>= 1) data[idx>>1] = merge(data[idx], data[idx^1]); }
		T query(int l, int r) {
			if (l==r) return get(l);;
			// Track left and right results separately to preserve order.
		 	T resl, resr; bool initl = false, initr = false;
			for (l += n, r += (n+1); l < r; l >>= 1, r >>= 1) {
				if (l&1) resl = initl ? merge(resl, data[l++]) : (initl = true, data[l++]);
				if (r&1) resr = initr ? merge(data[--r], resr) : (initr = true, data[--r]);
			}
			// Only merge if both were initialized.
			if (!initl) return resr;
			if (!initr) return resl;
			return merge(resl, resr);
		}	
};

void testSum() {
	cerr << "Testing sum segtree" << endl;
	Segtree<int> tree(10, [](int x, int y){return x+y;});
	assertEquals(0, tree.query(0, 9));
	tree.set(0,2);
	assertEquals(2, tree.query(0, 9));
	assertEquals(0, tree.query(1, 9));
	tree.set(1,3);
	assertEquals(5, tree.query(0, 1));
	assertEquals(5, tree.query(0, 9));
	assertEquals(0, tree.query(2, 9));
	tree.set(5,2);
	tree.set(9,20);
	assertEquals(27, tree.query(0, 9));
	assertEquals(3, tree.query(1,1));
	tree.set(5, tree.get(5) - 3);
	assertEquals(-1, tree.query(5,5));
	assertEquals(24, tree.query(0, 9));
	tree.set(0, tree.get(0) - 30);
	assertEquals(-6, tree.query(0, 9));
	assertEquals(22, tree.query(1, 9));
	cerr << "All tests passed!" << endl;
}

void testMax() {
	cerr << "Testing max segtree" << endl;
	Segtree<int> tree(10, [](int x, int y) {return max(x,y);});
	assertEquals(0, tree.query(0, 9));
	tree.set(0, 4);
	assertEquals(4, tree.query(0, 9));
	tree.set(9, 10);
	assertEquals(10, tree.query(0, 9));
	tree.set(1, 4);
	assertEquals(4, tree.query(0, 1));
	tree.set(4, -9);
	tree.set(5, -3);
	assertEquals(-9, tree.query(4, 4));
	assertEquals(-3, tree.query(5, 5));
	assertEquals(-3, tree.query(4, 5));
	assertEquals(0, tree.query(4, 6));
	cerr << "All tests passed!" << endl;
}

void testMin() {
	cerr << "Testing min segtree" << endl;
	Segtree<int> tree(10, -5, [](int x, int y) {return min(x,y);});
	assertEquals(-5, tree.query(0, 9));
	tree.set(0, 4);
	assertEquals(-5, tree.query(0, 9));
	tree.set(9, -10);
	assertEquals(-10, tree.query(0, 9));
	tree.set(1, 4);
	assertEquals(4, tree.query(0, 1));
	tree.set(4, -9);
	tree.set(5, -3);
	assertEquals(-9, tree.query(4, 4));
	assertEquals(-3, tree.query(5, 5));
	assertEquals(-9, tree.query(4, 5));
	assertEquals(-9, tree.query(4, 6));
	cerr << "All tests passed!" << endl;
}

int main() {
	// Testing
	testSum();
	testMax();
	testMin();
	return 0;
}
