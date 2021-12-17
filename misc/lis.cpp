namespace lis {
  template <class T> void add(vector<T>& lis, T nx) {
    /* lower_bound => strictly increasing
     * upper_bound => non-decreasing */
    auto pos = lower_bound(all(lis), nx);
    if (pos == lis.end()) lis.push_back(nx);
    else *pos = nx;
  }
}

