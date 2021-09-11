template <size_t N>
struct SIEVE {
  // See https://codeforces.com/blog/entry/54090
  vi prime;
  int f[N];
  // if prime (or <= 1)
  //   f[i] = 0
  // otherwise
  //   f[i] = min prime factor
  constexpr SIEVE () {
    for (int i=2; i<N; ++i) {
      if (!f[i]) {
        prime.push_back(i);
      }
      for (int p : prime) {
        if (i*p >= N) break;
        f[i*p] = p;
        if (i%p == 0) break;
      }
    }
  }
};

