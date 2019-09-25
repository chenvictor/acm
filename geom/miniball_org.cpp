#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
#define forxr(i,n) for(int i = (n)-1; i >= 0; --i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll,ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

const int D = 2;
typedef array<ld,2> ndpt;
typedef list<ndpt>::iterator It;
struct Miniball { list<ndpt> L; int m; vector<ndpt> v, a; vector<ndpt> c;
  ndpt q0; vector<ld> r2, z, f; It end; ndpt c_c; ld c_r2;
  Miniball() : m(0),v(D+1),a(D+1),c(D+1),
    r2(D+1), z(D+1), f(D+1), end(L.begin()), c_c(c[0]), c_r2(-1.L) {}
  void add(const ndpt &p) { L.push_back(p); }
  void move_to_front(It i) { m--; if (end==i) end++; L.splice(L.begin(),L,i); }
  void mtf_mb(It i) { end=L.begin(); if (m==D+1) return;
    for (It k=L.begin(),j;(j=k++)!=i;) { ld e = get_e(j);
      if (e > 0 && push(*j)) mtf_mb(j), move_to_front(j); } }
  void pivot_mb(It i) {
    It t=++L.begin(), pivot; mtf_mb(t); ld max_e, old_r2=-1;
    do { if((max_e=max_excess(t,i,pivot)) > 0) {
      if ((t=end)==pivot) ++t;
      old_r2=c_r2; push(*pivot); mtf_mb(end); move_to_front(pivot); }
    } while (max_e > 0 && c_r2 > old_r2); }
  ld max_excess(It j,It i,It& pivot) { ld max_e=0,e;
    for (; j!=i;++j) { if ((e=get_e(j)) > max_e) max_e=e,pivot=j; } return max_e; }
  ld get_e(It j) { ld e=-c_r2; for (int i=0;i<D;++i) e+=pow((*j)[i]-c_c[i], 2);
    return e; }
  bool push(const ndpt& p) { int i, j; if (!m) c[0]=q0=p, r2[0]=0; else {
      for (i=0;i<D;++i) v[m][i]=p[i]-q0[i];
      for (i=1;i<m;++i) { a[m][i]=0;
        for (j=0;j<D;++j) a[m][i]+=v[i][j]*v[m][j];
        a[m][i]*=(2/z[i]); }
      for (i=1;i<m;++i) for (j=0;j<D;++j) v[m][j]-=a[m][i]*v[i][j];
      z[m]=0; for (j=0;j<D;++j) z[m]+=2*pow(v[m][j], 2);
      if (z[m] < c_r2*EPS) return false;
      ld e=-r2[m-1]; for (i=0;i<D;++i) e+=pow(p[i]-c[m-1][i], 2);
      f[m]=e/z[m];
      for (i=0;i<D;++i) c[m][i]=c[m-1][i]+f[m]*v[m][i];
      r2[m]=r2[m-1]+e*f[m]/2;
    } c_c=c[m]; c_r2=r2[m]; m++; return true; }
  void build(){ pivot_mb(L.end()); } };

int main() {
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  Miniball ball;
  ball.add({2,3});
  ball.add({1,3});
  ball.add({2,4});
  ball.build();
  assert(ball.c_r2 == 0.5);
  assert(ball.c_c[0] == 1.5);
  assert(ball.c_c[1] == 3.5);

  return 0;
}

