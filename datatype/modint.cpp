template <int M> struct modint {
  int v; modint(int val=0) : v(val) { if ((v %= M) < 0) v += M; }
  modint& operator += (const modint& b) { return (v += b.v) %= M, SELF; }
  modint& operator *= (const modint& b) { return v = int(ll(v)*b.v % M), SELF; }
  modint& operator -= (const modint& b) { return SELF += M-b.v; }
  modint& operator /= (const modint& b) { return SELF *= b.inv(); }
  modint operator + (const modint& b) const { return modint SELF += b; }
  modint operator - (const modint& b) const { return modint SELF -= b; }
  modint operator * (const modint& b) const { return modint SELF *= b; }
  modint operator / (const modint& b) const { return modint SELF /= b; }
  modint pow(ll e) const { modint res(1), b(v); for (; e>0; e/=2, b*=b) { if (e&1) res*=b; } return res; }
  modint inv() const { return pow(M-2); }
  friend ostream& operator<<(ostream& os, const modint& mi) { return os << mi.v; }
};

