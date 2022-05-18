/**
 * O(C*sqrt(C) / 32) where C = sum of weights
 **/
template <size_t MAX>
bitset<MAX> sqrt_knapsack(const vi& ws, int sum) {
  bitset<MAX> ans;
  ans[0] = 1;
  vi cnt(sum+1);
  for (int w : ws) ++cnt[w];
  for(int i=1; i<=sum; ++i) {
    if (cnt[i] == 0) continue;
    ans |= ans << i;
    if (cnt[i]%2==0) {
      ans |= ans << i;
    }
    cnt[2*i] += (cnt[i]-1)/2;
  }
  return ans;
}

