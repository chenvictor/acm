class ModInt {
  int val; static const int MOD = -1; static_assert(MOD > 0, "Modulus not set!");
  int modInverse(int a) { // simplified extended GCD, only solving for x
    int b = MOD, x = 0, x_ = 1, q; while (a != 0) { q = b / a; swap(b, a); a %= b;
    swap(x, x_); x_ -= q * x; } assert(b == 1); return (x %= MOD) < 0 ? (x + MOD) : x; }
  public: ModInt() : val(0) { } ModInt(int v) : val(v) { if ((val %= MOD) < 0) val += MOD; }
    ModInt& operator += (const ModInt& b) { if ((val += b.val) >= MOD) val -= MOD; return *this; }
    ModInt& operator -= (const ModInt& b) { if ((val -= b.val) < 0) val += MOD; return *this; }
    ModInt& operator *= (const ModInt& b) { val = ((ll)val*(ll)b.val) % MOD; return *this; }
    ModInt& operator /= (const ModInt& b) {
      return (*this) *= modInverse(b.val);
      //if (((val *= modInverse(b.val)) %= MOD) < 0) val += MOD; return *this;
    }
#define _op(op, btype, op2) ModInt operator op (btype b) const { ModInt ans = *this; return ans op2 b; }
    _op(+, const ModInt&, +=); _op(-, const ModInt&, -=); _op(*, const ModInt&, *=); _op(/, const ModInt&, /=);
    _op(+, int, +=); _op(-, int, -=); _op(*, int, *=); _op(/, int, /=);
#undef _op
    operator int() const { assert(0 <= val && val < MOD); return val; }
};
