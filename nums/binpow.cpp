template <class T>
T binpow(T base, ll exp, T I=1) {
  while(exp > 0) {
    if (exp&1) I = I*base;
    base = base*base;
    exp /= 2;
  }
  return I;
}

