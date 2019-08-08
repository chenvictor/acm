// Rooted node depths
// LCA with binary jumping
// Initialize with a Graph, or add_node to add leaves
class TreeLCA {
  VI dep; vector<VI> bin; inline int anc(int node, int k) { return (k < bin[node].size()) ? bin[node][k] : -1; }
  public: TreeLCA(Graph& g, int root = 0) : dep(g.N(), -1), bin(g.N()) { assert(root < g.N()); dep[root] = 0; queue<pii> wk({{root, -1}});
      while (!wk.empty()) { pii elem = wk.front(); wk.pop(); for (int node : g.getAdjNode(elem.ff))
          if (elem.ss != node) { add_node(node, elem.ff); wk.push({node, elem.ff}); } } }
    TreeLCA(int root = 0) : dep(root+1, -1), bin(root+1) { dep[root] = 0; }
    // Add 'node' as a child of 'par'
    void add_node(int node, int par) { if (node >= dep.size()) { dep.resize(node+1, -1); bin.resize(node+1); } dep[node] = dep[par]+1; assert(bin[node].empty());
      bin[node].push_back(par); for (int k = 0; anc(par, k) != -1; ++k) bin[node].push_back(par = anc(par, k)); }
    int lca(int n1, int n2) { if (depth(n1) < depth(n2)) { swap(n1, n2); } int d2 = depth(n2); int diff = depth(n1) - d2;
      for (int i = 0; diff > 0; ++i, diff >>= 1) { if (diff & 1) n1 = anc(n1, i); } if (n1 == n2) return n1;
      for (int jump_k = 32 - __builtin_clz(d2); jump_k >= 0; --jump_k) if (anc(n1, jump_k) != anc(n2, jump_k)) { n1 = anc(n1, jump_k); n2 = anc(n2, jump_k); }
      return anc(n1, 0); }
    int depth(int node) { return dep[node]; }
};
