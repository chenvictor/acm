template <size_t N, typename V, int P, char F>
// p is prime > #chars,     F is first char
struct RollingHash {
  static int toi(char c) { return c-F+1; }
  V pw[N], px[N]; int j=1;
  RollingHash() {
    pw[0] = 1; rep(i,1,N) pw[i] = pw[i-1]*P;
  }
  void clear() { j=1; }
  void append(char c) {
    px[j] = px[j-1] + pw[j-1]*toi(c); ++j;
  }
  V operator()(const string& s) const {
    V v=0; const int m = sz(s);
    rep(i,0,m) v = v+pw[i]*toi(s[i]);
    return v*pw[N-1];
  }
  V operator()(int l, int r) const {
    return (px[r] - px[l])*pw[N-l-1];
  }
};
template<int M=int(1e9+9), typename B=unsigned>
struct HVal {
  // Source: kactl Hashing-codeforces
  int x; B b; HVal(int v=0) : x(v), b(v) {}
  HVal(int v, B y) : x(v), b(y) {}
  HVal operator+ (HVal o) const {int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
  HVal operator- (HVal o) const {int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
  HVal operator* (HVal o) const {return {(int)(1LL*x*o.x % M), b*o.b}; }
  bool operator==(HVal o) const {return x == o.x && b == o.b; }
  bool operator< (HVal o) const {return x == o.x ? b < o.b : x < o.x; }
};
using HashValue = HVal<int(1e9+7), HVal<>>;

