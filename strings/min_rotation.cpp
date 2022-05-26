/**
 * Author: Stjepan Glavina
 * Description: Finds the lexicographically smallest rotation of a string (or vector)
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp ?
 * Time: O(N)
 * Usage:
    rotate(v.begin(), v.begin()+minRotation(v), v.end());
 **/
template <class C>
int min_rotation(const C& s) {
  int a=0, sz=sz(s);
  #define SI(x) s[(x+i)%sz]
  rep(b,0,sz) rep(i,0,sz) {
    if (a+i==b || SI(a) < SI(b)) { b+=max(0,i-1); break; }
    if (SI(a) > SI(b)) { a=b; break; }
  }
  return a;
}

