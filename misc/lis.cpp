namespace lis {
  void add(vi& lis, int nx) {
    // upper_bound for non-decreasing
    // lower_bound for strictly increasing ?? not sure
    auto pos = upper_bound(all(lis), nx);
    if (pos == lis.end()) {
      lis.push_back(nx);
    } else {
      *pos = nx;
    }
  }
}

