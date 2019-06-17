template <int MOD=1000000007>
class ModInt {
  int val; public: ModInt() { val = 0; } ModInt(int v) { val = v; }
    ModInt& operator += (const ModInt& b) { if (val += b.val > MOD) val -= MOD; return *this; }
    ModInt& operator -= (const ModInt& b) { if (val -= b.val < 0) val += MOD; return *this; }
    ModInt& operator *= (const ModInt& b) { val = (val*b.val) % MOD; if (val < 0) val += MOD; return *this; }
    ModInt& operator /= (const ModInt& b) {
      assert(__gcd(val, b.val) == 1); //must be coprime for division
      val /= b.val; return *this; }

    ModInt& operator += (int b) { ModInt w(b); return operator+=(w); }
    ModInt& operator -= (int b) { ModInt w(b); return operator-=(w); }
    ModInt& operator *= (int b) { ModInt w(b); return operator*=(w); }
    ModInt& operator /= (int b) { ModInt w(b); return operator/=(w); }
    ModInt operator + (const ModInt& b) const { ModInt ans = *this; return ans += b; }
    ModInt operator - (const ModInt& b) const { ModInt ans = *this; return ans -= b; }
    ModInt operator * (const ModInt& b) const { ModInt ans = *this; return ans *= b; }
    ModInt operator / (const ModInt& b) const { ModInt ans = *this; return ans /= b; }
    ModInt operator + (int b) const { ModInt ans = *this; return ans += b; }
    ModInt operator - (int b) const { ModInt ans = *this; return ans -= b; }
    ModInt operator * (int b) const { ModInt ans = *this; return ans *= b; }
    ModInt operator / (int b) const { ModInt ans = *this; return ans /= b; }
    operator int() const { return val; }
};
