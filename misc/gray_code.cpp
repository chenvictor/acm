/**
 * Description: ordering of numbers so that only 1 bit changes at a time
 * https://en.wikipedia.org/wiki/Gray_code
 **/
template <class T>
T bin_to_gray(T v) {
  return v^(v>>1);
}
template <class T>
T gray_to_bin(T v) {
  for(int s=1; s<8*sizeof(T); s*=2)
    v ^= v >> s;
  return v;
}

