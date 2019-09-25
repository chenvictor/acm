#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll,ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

// Max area quadrilateral OR area of triangle (d=0)
// source: https://en.wikipedia.org/wiki/Heron's_formula
// source: https://en.wikipedia.org/wiki/Bretschneider's_formula
ld maxAreaQuad(ld a, ld b, ld c, ld d=0) {
  ld s = (a+b+c+d)/2; return sqrt((s-a)*(s-b)*(s-c)*(s-d));
}

class MT {
  ld mat[3][3];
  MT() : mat {{1,0,0},{0,1,0},{0,0,1}} { }
  MT& scale(ld k) {
    forx(i,3) { forx(j,3) { mat[i][j] *= k; } }
    return *this;
  }
  MT& translate(ld dx, ld dy) {
  
  }
};
struct pt {
  ld x, y;
  pt(ld x, ld y) : x(x), y(y) { }
  ld cross(const pt& o) const { return x*o.y - y*o.x; }
  ld dot(const pt& o) const { return x*o.x + y*o.y; }
  pt& operator +=(const pt& o) { x += o.x; y += o.y; return *this; }
  pt& operator -=(const pt& o) { x -= o.x; y -= o.y; return *this; }
  pt& operator *=(ld c) { x *= c; y *= c; return *this; }
  pt operator -() const { pt ret = *this; return ret *= -1; }
  pt operator +(const pt& o) const { pt ret = *this; return ret += o; }
  pt operator -(const pt& o) const { pt ret = *this; return ret -= o; }
  pt operator *(ld c) const { pt ret = *this; return ret *= o; }
  friend ostream& operator<<(ostream& out, const pt& p) {
    return out << "<" << p.x << "," << p.y << ">";
  }
  ld L1() const {
    return abs(x)+abs(y);
  }
  ld L2() const {
    return sqrt(x*x + y*y);
  }
  ld LINF() const {
    return max(x,y);
  }
};

int main() {
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  
  pt p = {1.5, -2};
  cout << p << nl;
  p *= -1;
  cout << p << nl;
  cout << -p << nl;
  return 0;
}
