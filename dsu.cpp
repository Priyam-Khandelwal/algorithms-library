int par[N];
int sz[N];
int find(int x) { 
	return x == par[x] ? x : par[x] = find(par[x]); 
} 
//path compression(logn)
void merge(int a, int b) {
	a = find(a);
	b = find(b);
	if(a == b) return;
	sz[a] += sz[b];
	par[b] = a;
}