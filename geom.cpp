#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
#define fori(n) for(int i =	0; i < n; ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9; const ld PI = acos(-1);
#define ff first
#define ss second

// Max area quadrilateral OR area of triangle (d=0)
// source: https://en.wikipedia.org/wiki/Heron's_formula
// source: https://en.wikipedia.org/wiki/Bretschneider's_formula
ld maxAreaQuad(ld a, ld b, ld c, ld d=0) {
  ld s = (a+b+c+d)/2; return sqrt((s-a)*(s-b)*(s-c)*(s-d));
}

template <typename T>
class Point {
  static complex<T> b1, b2;
  public:
  T x, y;
  Point(T x, T y) : x(x), y(y) { }
  friend ostream& operator<<(ostream& out, const Point<T>& p) { return out << "(" << p.x << "," << p.y << ")"; }
};

#define cx complex

int main() {
  cx<ld> c = {3, 5};
	Point<ld> p = {3, 5};
  cout << p << nl;
  cout << c << nl;
	return 0;
}
