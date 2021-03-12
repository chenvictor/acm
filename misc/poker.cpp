#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,e) for(int i = s; i < (e); ++i)
using ll = long long; using ld = long double;
using pii = pair<int,int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vl = vector<ll>;
const char nl = '\n';
const ll LINF = 0x3f3f3f3f3f3f3f3fll; const int INF = (int)LINF;
const ld EPS = 1e-9, PI = acos(-1.0L);
#define ff first
#define ss second
#define all(c) begin(c),end(c)
#define sz(c) int(c.size())

///////////////
// BOOK CODE //
///////////////

const string SUIT = "DCHS", CARD = "23456789TJQKA";
// true if A2345 is a straight
#define LOW_ACE 1
struct Poker {
  // add_card()x5 and eval()
  // result in val
  int s,f,j,c[5],cnt[13]; ll val;
  Poker(): s(1), f(15) { j=0; fill(all(cnt), 0); }
  void add_card(char v, char suit) {
    f &= (1 << SUIT.find(suit));
    cnt[c[j++] = CARD.find(v)] += 16;
  }
  void eval() {
    if (!(j = f)) { fill(all(c),0); rep(i,0,13)
      if (cnt[i]) s &= (cnt[i] == 16), c[j++] = i | cnt[i]; }
    sort(all(c));
#if LOW_ACE
    if (c[4] == 28 && c[3] == 19) {
      j = 1, c[4] = 19;
    } else
#endif
    j = c[4]-c[0] == 4;
    s &= j; s = 2*s + 3*!!f;
    ll cls = max(8*!c[2], 1<<s); cls<<=40;
    // full house, 3/4kind don't break ties
    if (c[0] >= 48) c[1] = c[2] = 0;
    rep(i,0,5) cls |= ((c[i] & 0xf) | ((c[i] & 0xf0l) << 16)) << 4*i;
    val = cls;
  }
};

///////////////
// REAL CODE //
///////////////

void deal(const string& s) {
  Poker b;
  int o = 0;
  rep(i,0,5) {
    b.add_card(s[o], s[o+1]);
    o+=3;
  }
  b.eval();
  Poker w;
  rep(i,0,5) {
    w.add_card(s[o], s[o+1]);
    o+=3;
  }
  w.eval();
  if (w.val > b.val) {
    cout << "White wins.\n";
  } else if (w.val < b.val) {
    cout << "Black wins.\n";
  } else {
    cout << "Tie.\n";
  }
}

int main() { // Emily <3
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(12);
  string s;
  while(getline(cin,s)) {
    if (sz(s) == 0) break;
    deal(s);
  }
  return 0;
}

