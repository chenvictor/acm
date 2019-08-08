void topoSort (Graph& graph, VI& ans)  {
  VB visited(graph.N(), false); stack<int> st;
  function<void(int u)> helper = [&](int u) { visited[u] = true; for (int v : graph.getAdjNode(u)) if (!visited[v]) helper(v); st.push(u); };
  forx (i, graph.N()) { if (!visited[i]) helper(i); } ans.resize(graph.N()); int i = 0; while (!st.empty()) { ans[i++] = st.top(); st.pop(); }
}
