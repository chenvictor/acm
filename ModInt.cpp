class ModInt {
  int val; static const int MOD = -1; static_assert(MOD > 0, "Modulus not set!");
  static int modInverse(int a, int mod = MOD) { // simplified extended GCD, only solving for x
    int b = mod, x = 0, x_ = 1, q; while (a != 0) { q = b / a; swap(b, a); a %= b;
    swap(x, x_); x_ -= q * x; } assert(b == 1); return (x %= mod) < 0 ? (x + mod) : x; }
  public: ModInt() : val(0) { } ModInt(int v) : val(v) { if ((val %= MOD) < 0) val += MOD; }
    ModInt& operator += (const ModInt& b) { (val += b.val) %= MOD; return *this; }
    ModInt& operator -= (const ModInt& b) { return (*this) += MOD-b.val; }
    ModInt& operator *= (const ModInt& b) { val = ((ll)val*(ll)b.val) % MOD; return *this; }
    ModInt& operator /= (const ModInt& b) { return (*this) *= modInverse(b.val); }
#define _op(op, op2) ModInt operator op (const ModInt& b) const { ModInt ans = *this; return ans op2 b; }
    _op(+, +=); _op(-, -=); _op(*, *=); _op(/, /=);
#undef _op
    ModInt pow(ll e) const { ModInt res(1), b(*this); for (; e>0; e/=2, b*=b) { if (e&1) res*=b; } return res; }
    int toInt() const { return val; }
};
