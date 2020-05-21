

vector<int> adj[N];
stack<int> s;
bool instack[N];
vector<vector<int>> sccs;
int disc[N], low[N], a[N];
int ttime = 0;

// code for Tarjan's strongly connected components algorithm
// taken from http://training.noi.ph/topics/graph_scc
void get_scc(ll i)
{
    vector<ll> scc;
    ll j;
    do
    {
        j = s.top();
        s.pop();
        instack[j] = false;
        scc.push_back(j);
    } while (j != i);
    sccs.push_back(scc);
}
void dfs(ll i)
{
    disc[i] = ttime;
    low[i] = ttime++;
    s.push(i);
    instack[i] = true;
    for (auto &j : adj[i])
    {
        if (disc[j] == -1)
        {
            dfs(j);
            low[i] = min(low[i], low[j]);
        }
        else if (instack[j])
            low[i] = min(low[i], disc[j]);
    }
    if (low[i] == disc[i])
        get_scc(i);
}
 
