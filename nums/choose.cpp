template <int N, typename T=int>
struct Choose {
  T f[N];
  constexpr Choose() {
    f[0] = 1; rep(i,1,N) f[i] = f[i-1]*i;
  }
  T operator()(int n, int k) {
    return f[n] / f[k] / f[n-k];
  }
};

template <int N, typename mi>
struct ChooseMod {
  // with inverse precomputation
  mi f[N], inv[N];
  constexpr ChooseMod() {
    f[0] = inv[0] = 1;
    rep(i,1,N) inv[i] = (f[i] = f[i-1]*i).inv();
  }
  mi operator()(int n, int k) {
    return f[n] * inv[k] * inv[n-k];
  }
};

