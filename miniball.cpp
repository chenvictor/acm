class Miniball { 
	typedef vector<ld> ndpt; // n dimensional point
	typedef list<ndpt>::iterator It;
	list<ndpt> L; int m, D;
	vector<vector<ld> > v, a;
	vector<ndpt> c; ndpt q0;
	vector<ld> r2, z, f;
	It end;	ndpt c_c; ld c_r2;
	// Private methods
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
    for (; j!=i;++j) if ((e=get_e(j)) > max_e) max_e=e,pivot=j; return max_e; }
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
	public:
		Miniball(int d) : D(d), m(0),v(D+1,vector<ld>(D)),a(D+1,vector<ld>(D)),c(D+1,ndpt(D,0)),
			q0(D), r2(D+1), z(D+1), f(D+1), end(L.begin()), c_c(c[0]), c_r2(-1.L) {}
		void add(ndpt &p) { L.push_back(p); }
		void build(){ pivot_mb(L.end()); }
		ndpt getCenter() { return c_c; }
		ld getRadius2() { return c_r2; }
};
typedef vector<ld> ndpt;
pair<npdt, ld> miniball_center(int D, vector<ndpt>& points) {
  int m = 0;
  vector<ndpt> v(D+1, npdt(D)), a(D+1, ndpt(D)), c(D+1, ndpt(D,0));
  ndpt q0(D), r2(D+1), z(D+1), f(D+1), c_c(c[0]);
  auto end = L.begin();
  ld c_r2(-1.L);
  function
  return make_pair(c_c, c_r2);
}
