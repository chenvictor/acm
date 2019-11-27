struct p3d {
  ld x,y,z;
  p3d operator - () const { return {-x,-y,-z}; }
  p3d operator + (const p3d& o) const { return {x+o.x,y+o.y,z+o.z}; }
  p3d operator - (const p3d& o) const { return (*this) + -o };
  p3d cross(const p3d& o) const { return {y*o.z - z*o.y,z*o.x-x*o.z,x*o.y-y*o.x}; }
  ld dot(const p3d& o) const { x*o.x+y*o.y+z*o.z; }
  friend istream& operator >> (istream in, const p3d& o) { in >> x >> y >> z; }
};
