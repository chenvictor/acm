// partitions the 'sizes' into as even groups as possible
// returns one of the partition sums, which will be the minimal value >= sum/2
// if recover != nullptr, the indices of the sizes giving the returned partition sum will be placed within the vector
int optimalPartition(VI& sizes, VI* recover = nullptr) {
  int sum = 0;
  for(int i:sizes) sum += i;
  VI dp(sum+1, -1); //dp[i] is the index of the size used to reach sum 'i'
  forx(i,sizes.size()) {
    register int sz = sizes[i];
    for(int j = dp.size()-1; j >= 0; --j) {
      if (dp[j] != -1) {
        if (dp[j+sz] == -1) {
          dp[j+sz] = i;
        }
      }
    }
    if (dp[sz] == -1) dp[sz] = i;
  }
  for(int i = (sum-1)/2+1; i < dp.size(); ++i) {
    if (dp[i] != -1) {
      if (recover) {
        VI& ans = *recover;
        register int cursz = i;
        register int curidx = dp[i];
        while (cursz > 0) {
          ans.push_back(curidx);
          cursz -= sizes[curidx];
          curidx = dp[cursz];
        } 
      }
      return i;
    }
  }
  throw "Something went wrong!";
}
