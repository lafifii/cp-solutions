#include <bits/stdc++.h>
using namespace std;

// dfs 

const int maxn = 1e5 + 20;
int vis[maxn], cn[2];
vector<int> lad[maxn];

void dfs(int u, int c){
	if(vis[u] != -1) return;
	vis[u] = c;
	cn[c]++;
	
	for(int x: lad[u])
		dfs(x, !vis[u]);
}

void solve(){
	int q;
	scanf("%d", &q);
	for(int i = 0; i < maxn; ++i) lad[i].clear();
	for(int i = 0; i < q; ++i){
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;
		lad[a].emplace_back(b);
		lad[b].emplace_back(a);
	}
	
	memset(vis,-1,sizeof(vis));
	
	int ans = 0;
	for(int i = 0; i < maxn; ++i)
		if(vis[i] == -1 and lad[i].size() > 0){ 
			memset(cn,0,sizeof(cn));
			dfs(i, 0);
			ans+= max(cn[0], cn[1]);
		}
		
	printf("%d\n", ans);
}

int main() {
	int t, tc = 1;
	scanf("%d", &t);
	while(t--){
		printf("Case %d: ", tc++);
		solve();
	}
	
	return 0;
}