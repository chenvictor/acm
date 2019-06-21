template <int MOD=1000000007>
class ModInt { int val;
  public: ModInt() { val = 0; } ModInt(int v) { val = v; }
    ModInt& operator += (const ModInt& b) { if (val += b.val > MOD) val -= MOD; return *this; }
    ModInt& operator -= (const ModInt& b) { if (val -= b.val < 0) val += MOD; return *this; }
    ModInt& operator *= (const ModInt& b) { val = (val*b.val) % MOD; if (val < 0) val += MOD; return *this; }
    ModInt& operator /= (const ModInt& b) { val /= b.val; return *this; }
#define _op(op) ModInt& operator op (int b) { ModInt w(b); return *this op w; }
    _op(+=); _op(-=); _op(*=); _op(/=);
#define _op(op, btype, op2) ModInt operator op (btype b) const { ModInt ans = *this; return ans op2 b; }
    _op(+, const ModInt&, +=); _op(-, const ModInt&, -=); _op(*, const ModInt&, *=); _op(/, const ModInt&, /=);
    _op(+, int, +=); _op(-, int, -=); _op(*, int, *=); _op(/, int, /=);
#undef _op
    operator int() const { return val; }
};
