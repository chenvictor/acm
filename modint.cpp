struct mi {
  int val; static const int MOD = -1; static_assert(MOD > 0, "Modulus not set!");
  mi(int v=0) : val(v) { if ((val %= MOD) < 0) val += MOD; }
  mi& operator += (const mi& b) { (val += b.val) %= MOD; return *this; }
  mi& operator -= (const mi& b) { return (*this) += MOD-b.val; }
  mi& operator *= (const mi& b) { val = ((ll)val*(ll)b.val) % MOD; return *this; }
  mi& operator /= (const mi& b) { return (*this) *= b.pow(MOD-2); }
#define _op(op, op2) mi operator op (const mi& b) const { mi ans = *this; return ans op2 b; }
  _op(+, +=); _op(-, -=); _op(*, *=); _op(/, /=);
#undef _op
  mi pow(ll e) const { mi res(1), b(*this); for (; e>0; e/=2, b*=b) { if (e&1) res*=b; } return res; }
  int toInt() const { return val; }
};
