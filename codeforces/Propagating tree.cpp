#include <bits/stdc++.h>
using namespace std;
/* arbol que propaga valor con update
    1 x val : suma val a x y resta val a sus hijos
    2 x : pide valor del nodo
*/
const int maxn = 2e5 + 60;
vector<int> lad[maxn];
int a[maxn], bit[2][maxn], in[maxn], out[maxn], n, cnt = 0;
bool vis[maxn], dep[maxn];

int query(int nv, int x){
	int ans = 0;
	for(; x > 0; x-=x&-x) ans+= bit[nv][x];
	return ans;
}
void update(int nv, int x, int val){
	for(; x <= n; x+=x&-x) bit[nv][x]+= val;
}
void dfs(int x, int d){
	if(vis[x]) return;
	vis[x] = 1;
	in[x] = ++cnt;
	dep[x] = d;
	for(int y: lad[x]) dfs(y, !d);
	out[x] = cnt;
}
int main() {
	int m, tip, u, v;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 0; i < n - 1; ++i){
		scanf("%d%d", &u, &v);
		lad[u].push_back(v);
		lad[v].push_back(u);
	}
	memset(vis,0,sizeof(vis));
	memset(bit,0,sizeof(bit));
	dfs(1, 0);
	for(int i = 0; i < m; ++i){
		scanf("%d", &tip);
		if(tip == 1){
			scanf("%d%d", &u, &v);
			update(dep[u], in[u], v);
			update(dep[u], out[u] + 1, -v);
			update(!dep[u], in[u], -v);
			update(!dep[u], out[u] + 1, v);
		}
		else{
			scanf("%d", &u);
			printf("%d\n", a[u] + query(dep[u], in[u]));
		}
	}
	
	return 0;
}
