#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll, ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

class SXArray {
  const int n; int gap;
  VI sa, pos, lcp;
  bool cmp(int i, int j) {
    if (pos[i] != pos[j]) return pos[i] < pos[j];
    i += gap, j += gap;
    return (i < n && j < n) ? pos[i] < pos[j] : i > j;
  }
  public:
    SXArray(string& s) : n(s.size()), gap(1), sa(n), pos(n), lcp(n) {
      forx(i,n) sa[i] = i, pos[i] = s[i];
      for (;; gap *= 2) {
        sort(sa.begin(), sa.end())
      }
    }
    //starting index (in s) of the ith lexographically smallest suffix
    int suf(int i) {
      r
    }
    //the sorted order of the suffix starting at index idx
    int pos(int idx) {
      return -1;
    }
};

int main() {
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  
  
  return 0;
}
