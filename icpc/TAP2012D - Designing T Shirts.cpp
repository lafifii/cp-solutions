#include <bits/stdc++.h>
using namespace std;
/*
	https://www.spoj.com/problems/TAP2012D/
  Maximum Amount of Common Prefixes of maximum Lenght that two sets of strings share.
*/
const int maxn = 2e6 + 20, alp = 27; // suma de caracteres, alp
int t[maxn][alp], vis[2][maxn], nodos = 1, maximo[maxn];
pair<int,int> V[maxn];
int getid(char c){
	return c - 'A';
}
void add(string s, int g){
	int act = 0;
	for(char c: s){
		int id = getid(c);
		vis[g][act]++;
		if(t[act][id] == 0) t[act][id] = nodos++;
		act = t[act][id];
	}
	vis[g][act]++;
}
void init(){
	memset(t,0,sizeof(t));
	memset(vis,0,sizeof(vis));
	for(int i = 0; i < maxn; ++i) V[i] = {0,0};
}
int dfs(int u, int lvl = 1){
	int mayor = 0;
	for(int i = 0; i < alp; ++i){
		if(t[u][i]) mayor += max(maximo[t[u][i]] ,dfs(t[u][i], lvl + 1) );
	}
	V[u] = make_pair(maximo[u] - mayor, lvl);
	return mayor;
}
int main() {
	int n;
	string s;
	while(cin >> n){
		if(n == -1) break;
		init(); int ans = 0;
		for(int i = 0; i < n; ++i){
			cin >> s;
			add(s, 0);
		}
		for(int i = 0; i < n; ++i){
			cin >> s;
			add(s, 1);
		}
		for(int i = 0; i < nodos; ++i) maximo[i] = min(vis[0][i], vis[1][i]);
		for(int i = 0; i < alp; ++i){
			if(t[0][i]) dfs(t[0][i]);
		}
		for(int i = 0; i < nodos; ++i) ans+= (V[i].first*V[i].second);
		cout << ans << endl;
	}
	return 0;
}
