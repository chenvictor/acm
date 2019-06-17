#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
//const char nl = '\n';
const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second
#define nl endl
#define assertEquals(actual, exp) if ((actual) != (exp)) { cerr << "Line " << __LINE__ << " assertion failed!" << nl; \
  cerr << "Expected: " << (exp) << nl << "Actual:   " << (actual) << nl; exit(-1); }

#define DEBUG 1
#if     DEBUG
#define trace(var)  {cerr << "Line " << __LINE__ << ": " << #var << "=" << (var) << nl;}
#else
#define trace(var)	{}
#endif

class Rand {
  public:
    static void seed(int s) { srand(s); }
    static ll range(ll low, ll hi) {
      return (rand() % (hi-low)) + low;
    }
};

class BigInt { typedef unsigned int uint; typedef unsigned long long ull; static const int I_SIZE = 8*sizeof(uint); char sgn; vector<uint> mag;
  uint& operator[] (int i) { if (i >= size()) mag.resize(i+1, 0); return mag[i]; } uint operator[] (int i) const { return (i < mag.size()) ? mag[i] : 0; }
  char cmpMag(const BigInt& b) const { ll diff = size() - b.size(); for (int i = size()-1; i >= 0 && !diff; --i) diff = (ll)(*this)[i] - b[i];; return getSign(diff); }
  char cmp(const BigInt& b) const { if (!sgn) return -b.sgn;; if (!b.sgn || sgn ^ b.sgn) return sgn;; return sgn * cmpMag(b); }
  char cmp(int b) const { if (!sgn) return -b; else if (!b || sgn ^ getSign(b) || size() > 1) return sgn;; return getSign((ll)(*this)[0] - abs((ll)b)) * sgn; }
  void addMag(const BigInt& b) { ull x = 0;  for (int i=0; i < max(b.size(), size()) || x; ++i, x >>= I_SIZE) (*this)[i] = (x += (ull)(*this)[i] + b[i]); }
  void subMag(const BigInt& b) { bool carry = false; ll x = 0; for (int i=0; i < max(b.size(), size()) || x; ++i, x >>= I_SIZE) {
    x += (ll)(*this)[i] - b[i] - carry; if ((carry = x < 0)) x += UINT_MAX; (*this)[i] = x; } } int size() const { return mag.size(); }
  void tc() { while (mag.size() && !mag.back()) mag.pop_back();; if (mag.empty()) { sgn = 0; } } void set(int s, vector<uint>& d) { sgn = s; mag.swap(d); }
  template <typename T> static char getSign(T x) { return (x < 0) ? -1 : x > 0; } public: BigInt() : sgn(0), mag(0) {}
  BigInt(string s, int radix=10) { fromString(s,radix); } BigInt(int x) : sgn(getSign(x)), mag(1, abs((ll)x)) { }
  char sign() const { return sgn; } void clear() { mag.clear(); sgn = 0; } void swap(BigInt& b) { std::swap(sgn, b.sgn); mag.swap(b.mag); }
  BigInt negate() const { BigInt ans = *this; ans.sgn *= -1; return ans; } BigInt absolute() const { return ((*this < 0) ? negate() : *this); }
  BigInt operator - () const { return negate(); } BigInt operator + () const { BigInt ans = (*this); return ans; }
  int popcount() const { int tot = 0; for (int v : mag) { tot += __builtin_popcount(v); } return tot; }
  int bitcount() const { return sgn ? (mag.size() * I_SIZE - __builtin_clz(mag.back())) : -1; }
  int ctz(bool pop1 = false) const { if (pop1) return I_SIZE * (mag.size() - 1) + __builtin_ctz(mag.back());; if (!sgn) return -1;
    for (int ans = 0, i = mag.size()-1; ; --i, ans += I_SIZE) if (mag[i]) return ans += __builtin_ctz(mag[i]); }
  BigInt lastnbits(int n) { BigInt ans = *this; const int full = ((n-1) / I_SIZE)+1, semi = n % I_SIZE;
    if (full > 0) { ans.mag.resize(full); ans.mag.back() &= ((1 << semi) - 1); } else { ans.clear(); } ans.tc(); return ans; }
#define _(op, T) bool operator op (T b) const { return cmp(b) op 0; }
  _(==,int); _(!=,int); _(>,int); _(>=,int); _(<,int); _(<=,int); _(==,BigInt); _(!=,BigInt); _(>,BigInt); _(>=,BigInt); _(<,BigInt); _(<=,BigInt);
#undef _
  // String conversions
  inline static int fromChar(char c) { return (c<'a')?(c<'A'?c-'0':c-'A'):c-'a'; }
  void fromString(string s, int radix=10) { BigInt bigRadix(radix); clear(); for (int i = (s[0]=='-'); i < s.length(); ((*this) *= bigRadix) += fromChar(s[i]), ++i);;
    sgn = s[0]=='-' ? -1 : 1; tc(); }
  int toInt() const { if (sgn > 0) { if (*this > INT_MAX) { throw runtime_error("Above integer limits!"); } return (*this)[0]; }
    else if (sgn < 0) { if (*this < INT_MIN) { throw runtime_error("Below integer limits!"); } return -((ll)(*this)[0]); }; return 0; }
  char toChar(int radix=10, bool upper=false) const { assert(*this < radix); return toInt() + ((*this < 10) ? '0' : (upper ? 'A' : 'a')-10); }
  string toString(int radix=10, bool upper=false) const { try { if (radix == 10) { return to_string(toInt()); }} catch (runtime_error e) { }
    BigInt bigRadix(radix), abs = absolute(); string ans; do { auto p = abs.divide(bigRadix); ans += (p.ss.toChar(radix, upper)); abs.swap(p.ff); }
    while (abs.sgn); if (sgn < 0) ans += '-';; reverse(ans.begin(), ans.end()); return ans; }
  // IOStream operators
  friend istream& operator>>(istream& in, BigInt& x) { string s; in >> s; x.fromString(s); return in; }
  friend ostream& operator<<(ostream& out, const BigInt& x) { return out << x.toString(); }
  // Bitwise operators
  BigInt& operator>>=(int shift) { if (shift < 0) return operator<<=(-shift); const int full = shift / I_SIZE, semi = shift % I_SIZE; const int temp = mag.size();
    for(int i = full; i < temp; ++i) (*this)[i-full] = ((ull)(*this)[i] | ((ull)(*this)[i+1] << I_SIZE)) >> semi;; mag.resize(mag.size()-full); tc(); return *this; }
  BigInt& operator<<=(int shift) { if (shift < 0) return operator>>=(-shift); const int full = shift / I_SIZE, semi = shift % I_SIZE;
    if (sgn) { ull val = (ull)mag.back() << semi; for (int i = mag.size()-1; i > 0; --i) { (*this)[full+i] = ((val <<= I_SIZE) |= ((ull)(*this)[i-1] << semi)) >> I_SIZE;
    } (*this)[full] = val; fill(mag.begin(), mag.begin()+full, 0); } tc(); return *this; }
  BigInt& operator&=(const BigInt& b) { forx (i, size()) (*this)[i] &= b[i];; tc(); return *this; }
  BigInt& operator|=(const BigInt& b) { forx (i, max(size(),b.size())) (*this)[i] |= b[i];; return *this; }
  BigInt& operator^=(const BigInt& b) { forx (i, max(size(),b.size())) (*this)[i] ^= b[i];; tc(); return *this; }
#define _op(op, op2, T) BigInt operator op (T b) const { BigInt ans=*this; return ans op2 b; }
  _op(&, &=, const BigInt&); _op(|, |=, const BigInt&); _op(^,^=,const BigInt&); _op(>>,>>=,int); _op(<<,<<=,int); _op(&,&=,int); _op(|,|=,int); _op(^,^=,int);
#undef _op
  operator bool() const { return sgn; }
  BigInt& operator +=(const BigInt& b) { if (b.sgn) { if (sgn) { if (sgn == b.sgn) { addMag(b); } else { switch(cmpMag(b)) { case 0: clear(); break;
    case 1: subMag(b); break; case -1: BigInt temp = b; swap(temp); subMag(temp); } } } else { (*this) = b; } } return *this; }
  BigInt& operator -=(const BigInt& b) { if (b.sgn) { if (sgn) { if (sgn == b.sgn) { switch(cmpMag(b)) { case 0: clear(); break; case 1: subMag(b); break;
    case -1: BigInt temp = -b; swap(temp); subMag(temp); } } else { addMag(b); } } else { (*this) = -b; } } return *this; } 
  BigInt& operator *=(const BigInt& b) { if (!sgn || !b.sgn) { clear(); return *this; } if (b.popcount() == 1) { sgn *= b.sgn; return *this <<= b.ctz(true); }
    BigInt a; swap(a); sgn = a.sgn * b.sgn; ull x = 0, t=0; bool carry = false; forx(i, a.size()) { for(int j = 0; j < b.size() || x; ++j) { x += (*this)[i+j];
    carry = __builtin_add_overflow(x, (ull)a[i]*b[j], &t); x = t; (*this)[i+j] = x; x >>= 32; x += ((ull)carry) << I_SIZE; } } return *this; }
  pair<BigInt,BigInt> divide(const BigInt& b) { try { int x = toInt(), y = b.toInt(); return make_pair(BigInt(x / y), BigInt(x % y)); } catch (runtime_error e) {
    if (b.popcount() == 1) { int cnt = b.ctz(true); BigInt temp = *this; BigInt R = temp.lastnbits(cnt); temp.sgn *= b.sgn; return make_pair(temp >> cnt, R); }
    BigInt lo, hi = (absolute()+1), mid, res; int cmp = 1; while(lo < hi-1 && cmp) { mid = (lo+hi) >> 1; switch (cmp = cmpMag(res = b*mid)) { case 1: lo.swap(mid);break;
    case -1: hi.swap(mid); break; case 0: lo.swap(mid); } } if (cmp == -1) res -= b; lo.sgn *= b.sgn * (res.sgn *= sgn * b.sgn); return make_pair(lo, *this - res); } }
  BigInt& operator /=(const BigInt& b) { return *this = divide(b).ff; } BigInt& operator %=(const BigInt& b) { return *this = divide(b).ss; }
#define _op(op, op2) BigInt operator op (const BigInt& b) const { BigInt copy = *this; return copy op2 b; }
  _op(+, +=); _op(-, -=); _op(*, *=); _op(/, /=); _op(%, %=);
#undef _op
#define _op(op) BigInt& operator op (int b) { BigInt temp(b); return (*this) op temp; }
  _op(+=); _op(-=); _op(*=); _op(/=); _op(%=);
#undef _op
#define _op(op, op2) BigInt operator op (int b) const { BigInt ans = *this; return ans op2 b; }
  _op(+, +=); _op(-, -=); _op(*, *=); _op(/, /=); _op(%, %=);
#undef _op
  BigInt& operator++() { return (*this) += 1; } BigInt& operator--() { return (*this) -= 1; } BigInt operator++(int) { BigInt copy = *this; *this += 1; return copy; }
  BigInt operator--(int) { BigInt copy = *this; *this -= 1; return copy; } };

/* ~~~~~~~~~~~~ TESTS ~~~~~~~~~~ */

inline void _shiftRight(int val, int shift) {
  BigInt bigVal(val); assertEquals(bigVal >> shift, val >> shift); }
inline void _shiftLeft(int val, int shift) { BigInt bigVal(val); assertEquals(bigVal << shift, val << shift); }
inline void _bitAnd(int a, int b) { BigInt bigA(a), bigB(b); assertEquals(bigA & bigB, a&b); }
inline void _bitOr(int a, int b) { BigInt bigA(a), bigB(b); assertEquals(bigA | bigB, a|b); }
inline void _bitXor(int a, int b) { BigInt bigA(a), bigB(b); assertEquals(bigA ^ bigB, a^b); }
void testBits() { cerr << "Testing Bitwise Operators" << nl; int x, y; forx(i,999999) { x = Rand::range(0, SHRT_MAX); y = Rand::range(0, 16);
    _shiftLeft(x,y); _shiftRight(x,y); x = Rand::range(0, INT_MAX); y = Rand::range(0, 32); _shiftRight(x,y); y = Rand::range(0, INT_MAX); _bitAnd(x,y);
    _bitOr(x,y); _bitXor(x,y); if (i % 100000 == 0) cerr << "."; } cerr << nl << "Done." << nl; }
inline void _cmp(int a, int b) { BigInt bigA(a), bigB(b); assertEquals(bigA < bigB, a < b); assertEquals(bigA > bigB, a > b); assertEquals(bigA <= bigB, a <= b);
  assertEquals(bigA >= bigB, a >= b); assertEquals(bigA == bigB, a == b); assertEquals(bigA != bigB, a != b); assertEquals(bigA < b, a < b);
  assertEquals(bigA > b, a > b); assertEquals(bigA <= b, a <= b); assertEquals(bigA >= b, a >= b); assertEquals(bigA == b, a == b); assertEquals(bigA != b, a != b); }
void testCmp() { cerr << "Testing Comparison Operators" << nl; int x, y; forx(i,999999) { x = Rand::range(INT_MIN,INT_MAX); y = Rand::range(INT_MIN, INT_MAX);
  _cmp(x,y); if (i % 100000 == 0) cerr << "."; } cerr << nl << "Done." << nl;
}
inline void _pm(int a, int b) { BigInt bigA(a), bigB(b); assertEquals(bigA + bigB, a + b); assertEquals(bigA - bigB, a - b); assertEquals(bigB - bigA, b - a); }
void testMathpm() { cerr << "Testing +/- operators" << nl; Rand::seed(55); int x, y; forx(i, 999999) {
    x = Rand::range(-INT_MAX>>1, INT_MAX>>1); y = Rand::range(-INT_MAX>>1, INT_MAX>>1); _pm(x,y); if (i % 100000 == 0) cerr << "."; } cerr << nl << "Done." << nl; }

void testMultDivPow2() {
  cerr << "Testing pow2 multiplication and division" << nl;
  int x; BigInt temp;
  forx(i,999999) {
    temp = x = Rand::range(-SHRT_MAX, SHRT_MAX);
    for (int i = 1; i <= 64; i*=2) {
      assertEquals(temp * i, x * i);
      assertEquals(temp / i, x / i);
      assertEquals(temp % i, x % i);
    }
    for (int i = -1; i >= -64; i*=2) {
      assertEquals(temp * i, x * i);
      assertEquals(temp / i, x / i);
      assertEquals(temp % i, x % i);
    }
    if (i % 100000 == 0) cerr << ".";
  } cerr << nl << "Done." << nl;
}

void testTemplate() {
  forx(i,999999) {

    if (i % 100000 == 0) cerr << ".";
  } cerr << nl << "Done." << nl;
}

void testString() {
  cerr << "Testing string operations" << nl;
  string s;
  ll val;
  forx(i,999999) {
    s=to_string(val = Rand::range(INT_MIN, INT_MAX));
    BigInt temp(s, 10);
    assertEquals(temp.toString(), s);
    if (i % 100000 == 0) cerr << ".";
  } cerr << nl << "Done." << nl;
}

void testMultDiv() {
  cerr << "Testing multiplication and division" << nl;
  int x, y; BigInt a, b;
  forx(i,999999) {
    a = x = Rand::range(SHRT_MIN, SHRT_MAX);
    b = y = Rand::range(SHRT_MIN, SHRT_MAX);
    if (y == 0) {
      ++y; ++b;
    }
    assertEquals(a*b, x*y);
    assertEquals(a/b, x/y);
    assertEquals(a%b, x%y);
    if (i % 100000 == 0) cerr << ".";
  } cerr << nl << "Done." << nl;
}

static unsigned long long clo;
#define checkpoint() { cerr << (ld) (clock()-clo) / CLOCKS_PER_SEC << nl; clo = clock(); }

int main() {
  // Emily <3
  cerr << boolalpha;
  testMathpm();
  checkpoint();
  testBits();
  checkpoint();
  testCmp();
  checkpoint();
  testMultDivPow2();
  checkpoint();
  testString();
  checkpoint();
  testMultDiv();
  checkpoint();

  return 0;
}
