#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define TD typedef
#define forx(i,n) for(int i = 0; i < (n); ++i)
#define forxr(i,n) for(int i = (n)-1; i >= 0; --i)
TD long long ll; TD long double ld; TD pair<int,int> pii; TD pair<ll,ll> pll; TD vector<int> VI; TD vector<bool> VB; TD vector<ll> VL;
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3fll; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

// T is the type to order by
// Keys are int type
template <class T, class Compare = greater<T>>
class PQ {
  Compare cmp;
  VI c; //heap of keys
  inline int& elem(int i) { return c.at(i-1); }
  vector<pair<int, T>> key_map;
  inline int& index(int i) { return key_map[i].ff; }
  inline T& pri(int i) { return key_map[i].ss; }
  //swaps the ith and jth elements in the heap if they should be
  //return true if swap occurred
  inline bool swp(int i, int j) {
    int &x = elem(i);
    int &y = elem(j);
    if (cmp(pri(x), pri(y))) return false;
    swap(x, y);
    index(x) = i, index(y) = j;
    return true;
  }
  
  struct {
    vector<pair<int,T>>& key_map;
    Compare& cmp;
    bool operator()(int i, int j) const {
      return cmp(key_map[j].ss, key_map[i].ss);
    }
  } inv_cmp =  {key_map, cmp};

  void h_up(int i) {
    for (int p = i>>1; i > 1 && swp(p, i); i = p, p>>=1);
  }
  void h_dn(int i) {
    int child = i << 1;
    while (child <= c.size()) {
      if (child < c.size() && cmp(pri(elem(child|1)), pri(elem(child)))) {
        child |= 1;
      }
      if (!swp(i, child)) break;
      i = child, child<<=1;
    }
  }
  public:
    pair<int, T> top() const { int i = c.at(0); return {i,pri(i)}; }
    bool empty() const { return c.empty(); }
    size_t size() const { return c.size(); }
    // pushes the value into the queue, or updates its priority
    void push(int key, const T& priority) {
      if (key_map.size() <= key) key_map.resize(key+1);
      bool go_down = cmp(priority, pri(key));
      int& i = index(key);
      pri(key) = priority;
      if (i > 0) {
        go_down ? h_dn(i) : h_up(i);
      } else {
        c.push_back(key);
        h_up(i = c.size());
      }
    }
    void pop() {
      assert(swp(c.size(), 1));
      c.pop_back();
      h_dn(1);
    }
    void debug() {
      cerr << "size: " << c.size() << nl;
      for(int i : c) {
        cerr << "(" << i << "," << pri(i) << ")" << nl;
      }
      check();
    }
    void check() {
      assert(is_heap(c.begin(), c.end(), inv_cmp));
    }
};

int main() {
  atexit([](){ cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl; });
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3
  vector<pii> testVals;
  testVals.push_back({0, 4});
  testVals.push_back({1, 6});
  testVals.push_back({2, -4});
  testVals.push_back({3, 100});
  testVals.push_back({4, 50});
  testVals.push_back({5, -2});
  random_device dev;
  mt19937 rng(dev());
  forx(i, 10) {
    shuffle(testVals.begin(), testVals.end(), rng);
    PQ<int> pq;
    for (auto val : testVals) {
      pq.push(val.ff, val.ss);
      pq.check();
    }
    while (pq.size()) {
      pq.pop();
      pq.check();
    }
  }
  
  return 0;
}

