/**
 * solves Ax = b
 * O(nm min(n,m))
 * Usage: GEPP(A).solve(b);
 **/
template <class T>
struct GEPP {
  static T nz(T v) {
    return abs(v) < EPS ? 0 : v;
  }
  matrix<T> M;
  GEPP(const matrix<T>& A): M(A.n,A.m+1) {
    rep(i,0,A.n) rep(j,0,A.m) M(i,j) = A(i,j);
  }
  pair<int,valarray<T>> solve(valarray<T>& b) {
    assert(M.n == sz(b));
    rep(i,0,M.n) M(i,M.m-1) = b[i];
    rep(i,0,min(M.n,M.m)) {
      // pivot
      pair<T,int> p;
      rep(k,i,M.n) p = max(p, {abs(M(k,i)),k});
      if(p.ss != i) swap(M[i],M[p.ss]);
      // reduce
      const T ai = M(i,i);
      if (!nz(ai)) continue;
      rep(k,0,M.n) {
        if (k==i) continue;
        T s = M(k,i);
        if (!nz(s)) continue;
        s /= ai;
        M[k] -= s*M[i];
        M(k,i) = 0;
      }
    }
    valarray<T> ans(NAN,M.m-1);
    int arb=M.m-1;
    for (auto row : M) {
      int cnt=0,k;
      rep(j,0,M.m-1) {
        if (nz(row[j])) {
          k=j; cnt++;
        }
      }
      const T v = nz(row[M.m-1]);
      if (v && !cnt) return {-1,ans};
      if (cnt == 1) {
        ans[k] = nz(v / row[k]);
        --arb;
      }
    }
    return {arb,ans};
  }
};

