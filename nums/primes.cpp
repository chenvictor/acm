template <size_t N, bool Compact=false>
struct Primes : vi {
  /**
   * O(n) sieve: https://codeforces.com/blog/entry/54090
   * f[p] = 0
   * f[c] = min prime factor (or 1 if compact)
   **/
  conditional_t<Compact,bitset<N>,array<int,N>> f;
  Primes () {
    f[0]=f[1]=-1;
    vi::reserve(2*N/(31-__builtin_clz(N))); // optional
    rep(i,2,N) {
      if (!f[i]) vi::push_back(i);
      for (int p : SELF) {
        if (i*p >= N) break;
        f[i*p] = p;
        if (i%p == 0) break;
      }
    }
  }
  bool operator()(int v) { return !f[v]; }
};

