template <size_t N, typename V>
struct RollingHash {
  static int toi(char c) { return c-'a'+1; }
  V pw[N], px[N]; int j=1;
  RollingHash() {
    pw[0] = 1; rep(i,1,N) pw[i] = pw[i-1]*31;
  }
  void append(char c) {
    px[j] = px[j-1] + toi(c)*pw[j-1];
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

