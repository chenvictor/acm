bool miller_rabin(int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  int d = n-1, r = 0;
  if (d%2) return false;
  while (d % 2 == 0) { ++r; d /= 2; }
  for (int a : {2, 7, 61}) {
    ll x = modpow(a, d, n);
    if (x == 1 || x == n-1) continue;
    for (int i = 1; i < r && x != n-1; ++i) {
      x = x*x % n;
    }
    if (x != n-1) return false;
  }
  return true;
}

