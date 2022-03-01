/**
 * eps=1 for integer
 **/
template <class T>
T binary_search(function<bool(T)> f, T l, T r, T eps) {
  while(abs(r-l) > eps) {
    T mid = (l+r)/2;
    (f(mid) ? l : r) = mid;
  }
  return l;
}

