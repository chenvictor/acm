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

class DSU {
	vector<int> p, s; int c;
	public:
		DSU (int n) : p(n), s(n, 1) { c = n; for(int i = 0; i < n; ++i) p[i] = i; }
		int find(int x) { return (p[x] == x) ? p[x] : p[x] = find(p[x]); }
		int size(int x) { return s[find(x)]; } int count() { return c; }
		void join(int x, int y) {
			if (find(x) == find(y)) return;; if (s[p[x]] > s[p[y]]) swap(p[x], p[y]);
			p[p[x]] = p[y]; s[p[y]] += s[p[x]]; c--;
		}
};

int main() {
	// Testing
	DSU test(20);
	assertEquals(20, test.count());
	for (int i = 0; i < 20; i++) assertEquals(1, test.size(i));
	test.join(0, 1);
	assertEquals(19, test.count());
	assertEquals(2, test.size(0));
	assertEquals(2, test.size(1));

	test.join(0, 1);
	assertEquals(19, test.count());
	assertEquals(2, test.size(0));
	assertEquals(2, test.size(1));
	
	test.join(3, 4);
	assertEquals(18, test.count());
	assertEquals(2, test.size(0));
	assertEquals(2, test.size(1));
	assertEquals(2, test.size(3));
	assertEquals(2, test.size(4));

	test.join(3, 0);
	assertEquals(17, test.count());
	assertEquals(4, test.size(0));
	assertEquals(4, test.size(1));
	assertEquals(4, test.size(3));
	assertEquals(4, test.size(4));
	
	for (int i = 0; i < 20; i++) {
		if (i == 0 || i == 1 || i == 3 || i == 4) continue;
		assertEquals(1, test.size(i));
	}
	for (int i = 0; i < 20; i++) {
		test.join(0, i);
	}
	assertEquals(1, test.count());
	for (int i = 0; i < 20; i++) {
		assertEquals(20, test.size(i));
	}
	

	cerr << "All tests passed!" << endl;
	return 0;
}

