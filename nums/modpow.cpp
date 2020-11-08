ll modpow(ll b, int e, int mod) {
  ll res = 1; for (; e; e>>=1, b=b*b%mod) { if (e&1) res = res*b % mod; } return res;
}

