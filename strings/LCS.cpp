// O(n^2) LCS
string LCS(string a, string b) {
  vector<VI> len(a.size()+1, VI(b.size()+1, 0));
  // len[i][j] = lcs length using a[:i-1], b[:j-1]
  forx(i,a.size()) forx(j,b.size()) len[i+1][j+1] = max(len[i][j] + (a[i]==b[j]), max(len[i][j+1], len[i+1][j]));
  int i = a.size(), j = b.size(), idx = len[i][j];
  string ans(idx, '*');
  while(idx > 0) {
    if (len[i][j] == len[i-1][j]) {
      i--;
    } else if (len[i][j] == len[i][j-1]) {
      j--;
    } else {
      ans[--idx] = a[i-1];
      i--;
      j--;
    }
  }
  return ans;
}
