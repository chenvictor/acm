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


int main() {
	// Testing
	assertEquals(true, 1+1==2);

	cerr << "All tests passed!" << endl;
	return 0;
}
