// Returns the # inversions in the vector
// The vector is sorted upon completion
ll mergeSortCountInversions(VI& nums) {
  ll ans = 0;
  function<void(int, int)> helper = [&](int l, int r) {
    //if the range [l, r) contains >= 2 elements
    if (l < r-1) {
      int mid = l + (r-l)/2; // midpoint while avoiding overflow
      helper(l, mid); helper(mid, r);
      VI temp;
      for (int i1 = l, i2 = mid, n1 = mid, n2 = r; i1 < mid || i2 < mid;) {
        int v1 = (i1 < n1) ? nums[i1] : INF;
        int v2 = (i2 < n2) ? nums[i2] : INF;
        if (v1 <= v2) {
          temp.push_back(v1);
          ++i1;
        } else {
          temp.push_back(v2);
          ++i2;
          //add # of values remaining in left side
          ans += (n1 - i1);
        }
      }
      copy(temp.begin(), temp.end(), nums.begin() + l);
    }
  };
  helper(0, nums.size());
  return ans;
}
