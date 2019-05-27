#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

//change to class after
struct BigInt {
    bool n; //is this number negative?
    VI data;  //unsigned data, each entry is a 'base' long segment
    int& operator[] (int i) { return data[i]; }
    int operator[] (int i) const { return (i < data.size()) ? data[i] : 0; }
  public:
  static const int base = 1e9;
    BigInt() : n(false), data(1,0) {}
    BigInt(int x) : n(x < 0) {
      for (int t = abs(x); t; t /= base) {
        data.push_back(t % base);
      }
    }
    void clear() { data.clear(); }
    int size() const { return data.size(); }
    friend istream& operator>>(istream& in, BigInt& x) {
      //cin big integer
      x.clear();
      return in;
    }
    friend ostream& operator<<(ostream& out, const BigInt& x) {
      if (x.size() == 0) return out << 0;
      if (x < 0) out << '-';
      out << x[x.size()-1];
      for (int i = x.size()-2; i >= 0; --i) {
        for (int j=BigInt::base/10;j; j/=10) out << x[i]/j%10;
      }
      return out;
    }
    int cmp(const BigInt& b) const {
      if (n && !b.n) return -1;
      if (!n && b.n) return 1;
      ll d = size() - b.size();
      for (int i = size()-1; i >= 0 && d == 0; --i) {
        d = (*this)[i] - b[i];
      }
      return (n ? -d : d);
    }
    int cmp(int b) const {
      if (n && b>0) return -1;
      if (!n && b<0) return 1;
      ll diff = (size() > 1 ? 1 : (*this)[0] - abs(b));
      return (n ? -diff : diff);
    }
#define _(op, T) bool operator op (T b) const { return cmp(b) op 0; }
    _(==,int); _(!=,int); _(>,int); _(>=,int); _(<,int); _(<=,int);
    _(==,BigInt); _(!=,BigInt); _(>,BigInt); _(>=,BigInt); _(<,BigInt); _(<=,BigInt);
#undef _
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3  
  BigInt t0;
  BigInt t1(200);
  cout << t0 << nl;
  assert(t0 >= 0);
  assert(t1 > t0);
  return 0;
}

