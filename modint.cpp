template <int MOD>
struct modint {
  int v; modint(int val=0) : v(val) { if ((v%= MOD) < 0) v += MOD; }
  modint& operator += (const modint& b) { (v += b.v) %= MOD; return *this; }
  modint& operator -= (const modint& b) { return (*this) += MOD-b.v; }
  modint& operator *= (const modint& b) { v = ((ll)v*(ll)b.v) % MOD; return *this; }
  modint& operator /= (const modint& b) { return (*this) *= b.pow(MOD-2); }
#define _op(op, op2) modint operator op (const modint& b) const { modint ans = *this; return ans op2 b; }
  _op(+, +=); _op(-, -=); _op(*, *=); _op(/, /=);
#undef _op
  modint pow(ll e) const { modint res(1), b(*this); for (; e>0; e/=2, b*=b) { if (e&1) res*=b; } return res; }
};
