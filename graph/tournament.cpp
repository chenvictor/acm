// Calculates the hamiltonian path within a Tournament graph, O(n^2)
// (Complete undirected graph, but directed) 
class Tournament {
  vector<VB> mat;
  public:
    // n = number of nodes
    Tournament(int n) : mat(n, VB(n)) { }
    // adds edge from u to v
    void add_edge(int u, int v) { mat[u][v] = true; }
    // calculate ham path
    VI path() const {
      VI ans;
      forx(i, mat.size()) {
        ans.push_back(i);
        for(int idx = i-1; idx >= 0; idx--)
          if (!mat[ans[idx]][ans[idx+1]])
            swap(ans[idx], ans[idx+1]);
      }
      return ans;
    }
};
