void fileio(const char* i, const char* o) {
  if (fopen(i, "r")) {
    freopen(i, "r", stdin);
    freopen(o, "w", stdout);
  }
}

