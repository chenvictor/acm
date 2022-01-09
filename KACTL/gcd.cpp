/**
 * Solve for x,y s.t. ax+by = (a,b) = g
 * !! VALUES MAY BE NEGATIVE !!
 * if g = 1,
 *   ax = 1 (mod b)
 *   by = 1 (mod a)
 * Source: KACTL
 **/
template <class T>
T gcd(T a, T b, T &x, T &y) {
  if (!b) return x=1, y=0, a;
  T d = gcd(b, a % b, y, x);
  return y -= a/b * x, d;
}

