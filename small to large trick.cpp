vector<int> g[N];
int cnt[N], col[N], sz[N];
bool big[N];
long long sum, maxx, ans[N];
void getsz(int v, int p){
    sz[v] = 1;
    for(auto u : g[v])
        if(u != p){
            getsz(u, v);
            sz[v] += sz[u];
        }
}
void add(int v, int p, int x){
	// cout << v << ' ' << col[v] << '\n';
    cnt[ col[v] ] += x;
    if(cnt[col[v]] > maxx) {
    	maxx = cnt[col[v]];
    	sum = col[v];
    }
    else if (maxx == cnt[col[v]]) {
    	sum += col[v];
    }
    for(auto u: g[v])
        if(u != p && !big[u])
            add(u, v, x);
}
void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1), big[bigChild] = 1;  // bigChild marked as big and not cleared from cnt
    add(v, p, 1);
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    
    ans[v] = sum;
    if(bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0) {
        add(v, p, -1);
        sum = 0;
        maxx = 0;
    }
}