/**
 * Closest pair of 2D points in O(nlogn)
 **/
template<class T=double>
struct closest_pair {
  using pt=pair<T,T>;
  using V=vector<pt>;
  using It=typename V::iterator;
  static tuple<T,pt,pt> res(const pt& a, const pt& b) {
    T dx = a.ff-b.ff, dy = a.ss-b.ss;
    return make_tuple(dx*dx+dy*dy,a,b);
  }
  static tuple<T,pt,pt> rec(It px, It py, int n) {
    if (n <= 3) {
      auto ans = res(px[0], px[1]);
      rep(j,2,n) rep(i,0,j) ans = min(ans, res(px[i], px[j]));
      return ans;
    }
    auto [s,e] = equal_range(px,px+n,px[n/2]);
    if (e-s == n) {
      // all same
      auto ans = res(px[0], px[1]);
      rep(j,2,n) ans = min(ans, res(py[j-1], py[j]));
      return ans;
    }
    auto mid = s-px > n-(e-px) ? s : e;
    int h = int(mid-px);
    V ny(n);
    It q = ny.begin(), r = q+h;
    rep(i,0,n) *(py[i] < *mid ? q : r)++ = py[i];
    auto sub = min(rec(px,ny.begin(),h), rec(mid,q,n-h));
    int m = 0;
    rep(i,0,n) {
      if (abs(py[i].ff-mid->ff) <= get<0>(sub)) ny[m++] = py[i];
    }
    rep(j,1,m) {
      rep(i,max(0,j-7),j) {
        sub = min(sub, res(ny[i], ny[j]));
      }
    }
    return sub;
  }
  static tuple<T,pt,pt> solve(const V& p) {
    V px=p, py=p;
    sort(all(px));
    sort(all(py), [](const pt& a, const pt& b) { return a.ss < b.ss; });
    return rec(px.begin(), py.begin(), sz(p));
  }
};


