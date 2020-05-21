vector<int> g[N];
int sz[N], parent[N], done[N];

void dfs(int u, int p) {
  sz[u] = 1;
  for(int v : g[u]) {
    if(done[v] || v == p) continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}
 
int find_centroid(int u, int p, int total) {
  for(int v : g[u]) {
    if(done[v] || v == p) continue;
    if(sz[v] + sz[v] > total)
      return find_centroid(v, u, total);
  }
  return u;
}
 
int centroid(int u) {
  dfs(u, 0);
  int cnt = sz[u];
  int center = find_centroid(u, 0, cnt);
  done[center] = 1;
//do stuff on centroid's subtree.

	solve();

  for(int v : g[center]) {
//centroid's subtree completed, recurse into subtrees to solve them
    if(done[v]) continue;
    parent[centroid(v)] = center;
  }
  return center;
}
 