void fileio(const char* in, const char* out) {
  if (fopen(in, "r")) { assert(freopen(in, "r", stdin) && freopen(out, "w", stdout)); }
}

