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

void testRangeBIT() {
	cerr << "Testing range BIT..." << endl;
	RangeBIT<int> rBit(10);
	assertEquals(0, rBit.get(0, 9));
	rBit.add(0, 1, 2);
	assertEquals(2, rBit.get(0, 0));
	assertEquals(2, rBit.get(1, 1));
	assertEquals(0, rBit.get(2, 2));
	for (int i = 1; i < 10; ++i)
		assertEquals(4, rBit.get(0, i));
	rBit.add(0, 9, -2);
	assertEquals(-16, rBit.get(0, 9));
	assertEquals(0, rBit.get(0, 0));
	assertEquals(0, rBit.get(1, 1));
	for (int i = 2; i < 10; ++i)
		assertEquals(-2, rBit.get(i, i));
	assertEquals(0, rBit.get(0, 1));
	for (int i = 2; i < 10; ++i)
		assertEquals((i-1)*-2, rBit.get(0, i));
	assertEquals(-4, rBit.get(3, 4));
	assertEquals(-4, rBit.get(5, 6));
	assertEquals(-8, rBit.get(4, 7));
	cerr << "All tests passed!" << endl;
}

void testBIT() {
	cerr << "Testing BIT..." << endl;
	BIT<int> bit(10);
	assertEquals(0, bit.get(0, 9));
	bit.add(0,2);
	assertEquals(2, bit.get(0, 9));
	assertEquals(0, bit.get(1, 9));
	bit.add(1,3);
	assertEquals(5, bit.get(0, 1));
	assertEquals(5, bit.get(0, 9));
	assertEquals(0, bit.get(2, 9));
	bit.add(5,2);
	bit.add(9,20);
	assertEquals(27, bit.get(0, 9));
	assertEquals(3, bit.get(1,1));
	bit.add(5,-3);
	assertEquals(-1, bit.get(5,5));
	assertEquals(24, bit.get(0, 9));
	bit.add(0,-30);
	assertEquals(-6, bit.get(0, 9));
	assertEquals(22, bit.get(1, 9));
	cerr << "All tests passed!" << endl;

}

int main() {
	// Testing
	testBIT();
	testRangeBIT();
	return 0;
}
