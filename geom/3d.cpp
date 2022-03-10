struct p3d {
  ld x,y,z;
  p3d(ld s=0): p3d(s,s,s) {}
  p3d(ld a, ld b, ld c): x(a), y(b), z(c) {}
  ld sum() const { return x+y+z; }
  // I/O
  friend ostream& operator<<(ostream& os, const p3d& p) { return os << p.x << " " << p.y << " " << p.z; }
  friend istream& operator>>(istream& is, p3d& p) { return is >> p.x >> p.y >> p.z; }
};
#define ELWISE(O) p3d operator O(const p3d& a, const p3d& b) { return {a.x O b.x, a.y O b.y, a.z O b.z};}
ELWISE(+) ELWISE(-) ELWISE(*) ELWISE(/)
ld dp(const p3d& a, const p3d& b) { return (a*b).sum(); }
ld norm(const p3d& a) { return dp(a,a); }
ld abs(const p3d& a) { return sqrt(norm(a)); }
bool eq(const p3d& a, const p3d& b) { return abs(a-b) < EPS; }

