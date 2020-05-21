    vector<int> adj[N]; 
    vector<vector<int>> ans;
    vector<bool> visited;
    vector<int> tin, low;
    int timer;
    void IS_BRIDGE(int v,int to){
        ans.push_back({v,to});
    }
    void dfs(int v, int p = -1) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v])
                    IS_BRIDGE(v, to);
            }
        }
    }

    void find_bridges(int n) {
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
    }