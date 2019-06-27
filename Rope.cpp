#include <bits/stdc++.h>
using namespace std; inline void fileio(const char* in, const char* out) { freopen(in, "r", stdin); freopen(out, "w", stdout); } 
#define CM ,
#define TD(a,b) typedef a b
#define forx(i,n) for(int i = 0; i < (n); ++i)
TD(long long,ll); TD(long double,ld); TD(pair<int CM int>,pii); TD(pair<ll CM ll>,pll); TD(vector<int>,VI); TD(vector<bool>,VB); TD(vector<ll>, VL);
const char nl = '\n'; const int INF = 0x3f3f3f3f; const ll LINF = 0x3f3f3f3f3f3f3f3f; const ld EPS = 1e-9, PI = acos(-1);
#define ff first
#define ss second

template <typename T>
class Rope {
    struct Node {
      Node *l, *r, *parent;
      T data;
      int size;
      Node(T d = T(), Node* p = 0) : l(0), r(0), parent(p), data(d), size(1) { }
    };
    // The root, leftmost, and rightmost nodes respectively
    Node rNode = {0, 0, 0, T(), 0};
    Node *root, *left, *right;
    static int _size(Node* n) { return n ? n->size : 0; }
    Node*& find(int idx) {
      Node* n = root;
      while (_size(n->l) != i) { if (i >= _size(n->l)) i -= _size(n = n->r); else n = n->l; }
      return n;
    }
  public:
    Rope() : root(0), left(0), right(0) {  }
    Rope(int n, T fill = T()) : root(0) {
      if (n) { root = left = right = new Node(fill); int l,r;
        queue<pair<Node*,int>> to_init({make_pair(root, n)});
        while (!to_init.empty()) {
          Node* cur = to_init.front().ff; cur->size = to_init.front().ss; to_init.pop();
          l = (cur->size-1)/2; r = (cur->size-1)-l;
          if (l) {
            to_init.emplace(cur->l = new Node(fill, cur), l);
            if (left == cur) left = cur->l;
          }
          if (r) {
            to_init.emplace(cur->r = new Node(fill, cur), r);
            if (right == cur) right = cur->r;
          }
        }
      }
    }
    ~Rope() { clear(); }
    T& operator[](int i) { return find(i).data; };
    T& at(int i) { assert(0 <= i && i < size()); return operator[](i); }
    // Insert an element at index 'i'
    T& insert(int i, T val = T()) {
      Node* n = find()
    }
    void clear() {
      for (queue<Node*> wk({root}); !wk.empty(); delete wk.front(), wk.pop()) {
        if (wk.front()->l) { wk.push(wk.front()->l); }
        if (wk.front()->r) { wk.push(wk.front()->r); }
      }
    }
    int size() const { return _size(root); }
    // Iterator
    class Iterator {
      Node* node;
      public:
        Iterator(Node* node) : node(node) { }
    };
    Iterator begin() const {
      return Iterator(left);
    }
    Iterator end() const {
      return Iterator
    }
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3  
  
  Rope<int> test(5);
  test[2] = 3;
  test[3] = 4;
  cout << test[2] + test[3] << nl;
  test[2] = 5;
  cout << test[2];

  cerr << "Time: " << (ld)clock() / CLOCKS_PER_SEC << nl;
  return 0;
}

