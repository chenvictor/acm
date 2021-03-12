typedef ll Ans;
namespace Mo {
  static const int SZ = 460;
  function<void(int)> add;
  function<void(int)> sub;
  function<Ans(void)> get;
  vector<Ans> solve(const vector<pii>& Q) {
    const int n = Q.size(); VI order(n); forx(i,n) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b){
      int b1 = Q[a].ff / SZ, b2 = Q[b].ff / SZ;
      return b1 == b2 ? Q[a].ss < Q[b].ss : b1 < b2;
    });
    int l = 0, r = -1;
    vector<Ans> ans(n);
    for(int i : order) {
      const pii& q = Q[i];
      for (;r < q.ss; add(++r));
      for (;r > q.ss; sub(r--));
      for (;l < q.ff; sub(l++));
      for (;l > q.ff; add(--l));
      ans[i] = get();
    }
    return ans;
  }
}
