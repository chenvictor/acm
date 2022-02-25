/**
 * Maintains set of convex combinations of points to the left and below
 * - add points
 * - query if point in set
 * O(log n)
 * tested on https://open.kattis.com/problems/hiringhelp
 **/
struct DynamicConvexSet : set<Pt,cmp_lex> {
  void clean(iterator it) {
    {
      if (it != end()) {
        auto nx = next(it);
        while(nx != end()) {
          auto mid = nx++;
          if (nx == end()) break;
          if (cp(*nx-*mid,*it-*mid) >= 0) {
            ifdebug cerr << "erasing " << *mid << nl;
            erase(mid);
          } else {
            break;
          }
        }
      }
    }
    {
      if (it != begin()) {
        auto nx = prev(it);
        while(nx != begin()) {
          auto mid = nx--;
          if (cp(*it-*mid,*nx-*mid) >= 0) {
            ifdebug cerr << "erasing " << *mid << nl;
            erase(mid);
          } else {
            break;
          }
        }
        while(it != begin() && nx->imag() <= it->imag()) {
          ifdebug cerr << "erasing " << *nx << nl;
          erase(nx--);
        }
      }
    }
  }
  bool add(Pt p) {
    if (query(p)) return 0;
    ifdebug cerr << "inserting " << p << nl;
    clean(insert(p).ff);
    return 1;
  }
  bool query(const Pt& q) {
    auto it = lower_bound(q);
    if (it == end()) return 0;
    if (it == begin()) {
      return q.imag() < it->imag()+EPS;
    }
    trace(*it);
    auto pr = prev(it);
    return cp(*it-q,*pr-q) > -EPS;
  }
};

