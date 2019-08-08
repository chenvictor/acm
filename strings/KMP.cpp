#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll, ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

class KMP {
  VI fail;
  string p;
  public:
    KMP (string target) : fail(target.size()+1), p(target) {
      for(int i=0, j=-1; ; ++i, ++j) {
        fail[i] = j; if (i == p.size()) break;
        while (j >= 0 && p[i] != p[j]) j = fail[j];
      }
    }
    VI match(string source) {
      VI ans;
      for (int i=0,j=0; ; ++i, ++j) {
        if (j == p.size()) ans.push_back(i-j), j = fail[j];
        if (i == source.size()) break;
        while (j >= 0 && source[i] != p[j]) j = fail[j];
      } return ans;
    }
};

int main() {
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  KMP test("abac");
  for (int a : test.match("abacababacac")) {
    cout << a << nl;
  }
  
  return 0;
}

