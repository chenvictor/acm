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
class LinkedList {
  struct Node {
    T data;
    Node* next, prev;
    Node(const T& data, Node* next=nullptr, Node* prev=nullptr) : data(data), next(next), prev(prev) {}
  };
  ll n;
  Iterator* head;
  public:
    class Iterator {
      protected:
      Node* node;
      public:
      Iterator(Node* ptr) : node(ptr) {}
      T operator * () {
        return node->data;
      }
      Iterator operator++() {
        Iterator temp = *this;
        node = node->next;
        return temp;
      }
      bool operator == (const Iterator& it) {
        return node == it.node;
      }
      Iterator prev() {
        return Iterator(node->prev);
      }
      Iterator next() {
        return Iterator(node->next);
      }
    }
    LinkedList() : n(0), head(Node(T())) {}
    ~LinkedList() {
      for (auto it = begin(); it != end();)
    }
    ll size() {
      return n;
    }
    Iterator begin() {
      return head.next();
    }
    Iterator end() {
      return head;
    }
    // Add item to end of list
    void push_back(const T& data) {
      Node* item = 
      n++;
    }
    void push_front(const T& data) {
      n++;
    }
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  // Emily <3  
  
  return 0;
}

