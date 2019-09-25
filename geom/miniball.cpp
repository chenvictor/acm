#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
#define forxr(i,n) for(int i = (n)-1; i >= 0; --i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll,ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL; TD vector<ld> VLD;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

/*  Returns the minimum enclosing ball 
 *  {center, radius**2}
 */
template <size_t D>
pair<array<ld,D>, ld> miniball(const vector<array<ld,D>>& points) { TD array<ld,D> ndpt; TD typename list<array<ld,D>>::iterator It;
  list<ndpt> L(points.begin(), points.end()); int m; array<ndpt, D+1> v, a, c; ld c_r2(-1.L); It end(L.begin()); ndpt q0, c_c;
  array<ld,D+1> r2, z, f; function<void(It)> mtf = [&](It i) { m--; if (end==i) end++; L.splice(L.begin(), L, i); };
  function<ld(It)> get_e = [&](It j) { ld e=-c_r2; for (int i=0;i<D;++i) e+=pow((*j).at(i)-c_c[i], 2); return e; };
  function<ld(It,It,It&)> max_excess = [&](It j,It i,It& pivot) { ld max_e=0,e; for (; j!=i;++j) { if ((e=get_e(j)) > max_e) max_e=e,pivot=j; } return max_e; };
  function<bool(const ndpt&)> push = [&](const ndpt& p) {
    int i, j; if (!m) c[0]=q0=p, r2[0]=0; else {
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
    } c_c=c[m]; c_r2=r2[m]; m++; return true; };
  function<void(It)> mtf_mb = [&](It i) {
    end=L.begin(); if (m==D+1) return;
    for (It k=L.begin(), j;(j=k++)!=i;) {
      ld e = get_e(j);
      if (e > 0 && push(*j)) mtf_mb(j), mtf(j);
    }
  };
  function<void(It)> pivot_mb = [&](It i) {
    It t = ++L.begin(), pivot; mtf_mb(t); ld max_e, old_r2 = -1;
    do { if((max_e=max_excess(t,i,pivot)) > 0) {
      if ((t=end)==pivot) ++t;
      old_r2=c_r2; push(*pivot); mtf_mb(end); mtf(pivot); }
    } while (max_e > 0 && c_r2 > old_r2);
  };
  pivot_mb(L.end());
  return {c_c, c_r2};
}

int main() {
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  vector<array<ld,2>> points;
  points.push_back({2,3});
  points.push_back({1,3});
  points.push_back({2,4});
  
  auto ans = miniball(points);
  array<ld,2> center = ans.ff;
  assert(center[0] == 1.5);
  assert(center[1] == 3.5);
  assert(ans.ss == 0.5);

  return 0;
}

