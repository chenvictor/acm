template <int MOD>
struct modint {
  int v; modint(int val=0) : v(val) { if ((v %= MOD) < 0) v += MOD; }
  auto& operator += (const modint& b) { (v += b.v) %= MOD; return *this; }
  auto& operator *= (const modint& b) { v = int(ll(v)*b.v % MOD); return *this; }
  auto& operator -= (const modint& b) { return (*this) += MOD-b.v; }
  auto& operator /= (const modint& b) { return (*this) *= b.inv(); }
  auto operator + (const modint& b) const { return modint(*this) += b; }
  auto operator - (const modint& b) const { return modint(*this) -= b; }
  auto operator * (const modint& b) const { return modint(*this) *= b; }
  auto operator / (const modint& b) const { return modint(*this) /= b; }
  auto pow(ll e) const { modint res(1), b(v); for (; e>0; e/=2, b*=b) { if (e&1) res*=b; } return res; }
  auto inv() const { return pow(MOD-2); }
  friend ostream& operator<<(ostream& os, const modint& mi) { return os << mi.v; }
};

