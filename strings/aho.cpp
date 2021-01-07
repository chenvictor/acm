// https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/AhoCorasick.h
// 1. Aho::insert() strings
// 2. Aho::build()
// findAll type operations NsqrtN ONLY IF STRINGS DISTINCT
namespace Aho {
  const int ALPHA = 26;
  int toi(char c) { return c - 'a'; }
  struct Node {
    int back, next[ALPHA], s = -1, end = -1, cnt = 0;
    // back is suffix link
    // next is node next node given char
    // end is longest match ending at current position
    // cnt is number of matching ending at current position
    Node(int v) { fill(next, next+ALPHA, v); }
  };
  int sz = 0; vector<Node> N = {-1}; vi backp;
  // backp[i] is the longest suffix of string i, -1 if none
  // returns terminal node of added string
  int insert(const string& s) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int& m = N[n].next[toi(c)];
      if (m == -1) { n = m = N.size(); N.emplace_back(-1); }
      else n = m;
    }
    if (N[n].end == -1) N[n].s = sz;
    backp.push_back(N[n].end);
    N[n].end = sz++;
    N[n].cnt++;
    return n;
  }
  void build() {
    N[0].back = N.size();
    N.emplace_back(0);
    for (queue<int> q({0}); q.size(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      rep(i,0,ALPHA) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1) {
          ed = y;
        } else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].s])
            = N[y].end;
          N[ed].cnt += N[y].cnt;
          q.push(ed);
        }
      }
    }
    N[0].back = 0; N.pop_back();
  }
  // nicer interface
  const struct Iter {
    int id; Iter(int i=0): id(i) {}
    Iter go(char c) { return N[id].next[toi(c)]; }
    Node& operator()() { return N[id]; }
  } root;
  // returns longest match ending at each pos
  vi find(string word) {
    Iter i = root;
    vi res; // ll count = 0;
    for(char c : word) {
      i = i.go(c);
      res.push_back(i().end);
      // count += N[n].cnt;
    }
    return res;
  }
  // returns all matches starting at each pos, shortest first
  vector<vi> findAll(vector<string>& pat, string word) {
    vi r = find(word);
    vector<vi> res(word.size());
    rep(i,0,word.size()) {
      int ind = r[i];
      while (ind != -1) {
        res[i - pat[ind].size() + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }
};
