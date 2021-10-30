template <size_t N, typename V>
struct RollingHash {
  static int toi(char c) { return c-'a'+1; }
  V pw[N], px[N]; int j=1;
  RollingHash() {
    pw[0] = 1; rep(i,1,N) pw[i] = pw[i-1]*5;
  }
  void append(char c) {
    px[j] = px[j-1] + pw[j-1]*toi(c);
    ++j;
  }
  template <typename iter>
  void append(iter a, iter b) {
    while(a!=b) append(*a++);
  }
  V operator()(int l, int r) const {
    return (px[r] - px[l])*pw[N-l-1];
  }
};

template<int M, typename B>
struct HVal {
  // Source: kactl Hashing-codeforces, TODO make nicer?
  int x; B b; HVal(int v=0) : x(v), b(v) {}
  HVal(int v, B y) : x(v), b(y) {}
  HVal operator+ (HVal o) const {int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
  HVal operator- (HVal o) const {int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
  HVal operator* (HVal o) const {return {(int)(1LL*x*o.x % M), b*o.b}; }
  bool operator==(HVal o) const {return x == o.x && b == o.b; }
};
using HashValue = HVal<1000000007, HVal<1000000009, unsigned>>;

