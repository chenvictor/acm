/**
 * Various from http://paulbourke.net/geometry/pointlineplane/
 **/

/**
 * returns point on line (or segment) a-b closest to p
 * also works in 3d
 **/
template <bool seg=0>
pt pl_closest(const pt& a, const pt& b, const pt& p) {
  pt v=b-a; ld u=dp(p-a,v)/norm(v);
  if (seg) u=min(1.L,max(0.L,u));
  return a + u*v;
}

/**
 * Returns intersection point (or segment if coincident)
 * returns duplicate point if coincident at a single point.
 **/
vector<pt> seg_inter(pt a, pt b, pt c, pt d) {
  ld l=cp(b-a,d-c), x=cp(d-c,a-c), y=cp(b-a,a-c);
  if (!sgn(l)) { // parallel
    if (!sgn(x) && !sgn(y)) {
      // coincident
      if (cmp_lex(b,a)) swap(a,b);
      if (cmp_lex(d,c)) swap(c,d);
      if (cmp_lex(c,a)) swap(a,c), swap(b,d);
      if (cmp_lex(b,c)) return {};
      return {c, min(d,b,cmp_lex)};
    } else return {};
  }
  x /= l, y /= l;
  if (x<-EPS || 1+EPS<x) return {};
  if (y<-EPS || 1+EPS<y) return {};
  return {a + x*(b-a)};
}

