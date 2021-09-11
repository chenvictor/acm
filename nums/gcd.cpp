// solves: ax + by = gcd(a,b)
// return: { gcd, x, y };
// source: https://en.wikibooks.org/wiki/Algorithm_Implementation/Mathematics/Extended_Euclidean_algorithm#Iterative_algorithm_3
template <typename T>
tuple<T,T,T> egcd(T a, T b) {
  T gcd = b, x = 0, y = 1, x_ = 1, y_ = 0;
  while (a) {
    b = gcd / a;
    swap(gcd, a); a %= gcd;
    swap(y, y_); y_ -= b * y;
    swap(x, x_); x_ -= b * x;
  }
  return {gcd, x, y};
}

