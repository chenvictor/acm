// Finds the diameter of a tree graph
// @param g     the graph
// @param i     the node to use as the root
int tree_diameter(Graph& g, int i = 0) {
  // ff is the diameter so far (which could be the branch)
  // ss is the longest branch
  function<pii(int,int)> helper = [&](int u, int p) {
    if (g.isLeaf(u,p)) return make_pair(0,0);
    int diam = 0; // biggest diameter so far
    int best = 0; // biggest branch so far
    for (int v : g.getAdjNode(u)) {
      if (v == p) continue;
      pii temp = helper(v, u);
      diam = max(diam, temp.ff);
      diam = max(diam, best + temp.ss + 1);
      best = max(best, temp.ss + 1);
    }
    return make_pair(diam, best);
  };
  return helper(i, -1).ff;
}
