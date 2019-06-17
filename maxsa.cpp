#include <bits/stdc++.h>
using namespace std;
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

template <typename T>
ll maxSA(vector<T>& nums, bool canEmpty=true) { static ll dummy; if (nums.empty()) return 0ll;
  function<ll(ll&, ll&, int, int)> helper = [&](ll& lsum, ll& rsum, int l, int r) {
    if (l == r-1) return (ll) nums[l];; int m = (l+r)/2; lsum = rsum = 0ll; ll lt = 0, rt = 0;
    forx(i,r-l) { lsum = max(lsum, lt += nums[l+i]); rsum = max(rsum, rt += nums[r-i-1]); }
    ll lbest = 0, rbest = 0; ll ans = max(helper(dummy, lbest, m, r), helper(rbest, dummy, l, m));
    return max(ans, lbest + rbest); };
  if (!canEmpty) { T pick = *(max_element(nums.begin(), nums.end())); if (pick < 0) return pick; }
  ll ans = helper(dummy, dummy, 0, nums.size()); return canEmpty ? max(0ll, ans) : ans;
}

template <typename T>
ll maxSAdp(vector<T>& nums, bool canEmpty=true) {
  if (nums.empty()) return 0;
  ll ans;
  forx(i,nums.size()) {
    if (i == 0)
      ans = nums[0];
    else
      ans = max(ans+nums[i], (ll)nums[i]);
  }
  return canEmpty ? max(0ll, ans) : ans;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3  
  VI arr = {-2, -3, 4, -1, -2, 1, 5, -3};
  cout << maxSAdp(arr);
  return 0;
}
