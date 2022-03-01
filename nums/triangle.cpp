/**
 * sum of numbers in range [from, to), both nonnegative
 **/
ll triangle(ll from, ll to, ll acc=0) {
  if (from <= 1) return acc+to*(to-1)/2;
  return triangle(0, to-from+1, from*(to-from));
}

