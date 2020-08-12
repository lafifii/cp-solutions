#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
vector<int> lad[maxn];
double dp[maxn], eps = 1e-9;
int in[maxn];
/*
  maxima probabilidad de quedarte atascado en un nodo i
  viajando desde un nodo u
*/
int main() {
	memset(dp,0,sizeof(dp));
	memset(in,0,sizeof(in));
	int n, m, u, v, ini;
	cin >> n >> m >> ini;
	ini--;
	
	for(int i = 0; i < m; ++i){
		cin >> u >> v;
		u--, v--;
		lad[u].push_back(v);
		in[v]++;
	}
	
	dp[ini] = 1;
	queue<int> q;
	for(int i = 0; i < n; ++i) if(in[i] == 0) q.push(i);
	
	while(q.size() > 0){
		int x = q.front(); q.pop();
		for(int y: lad[x]){
			dp[y] += (dp[x]/lad[x].size());
			in[y]--;
			if(in[y] == 0) q.push(y);
		}
	}
	double mx = 0;
	// ways i es probabilidad de llelgar a ese nodo
	for(int i = 0; i < n; ++i) if(lad[i].size() == 0) mx = max(mx, dp[i]);
	for(int i = 0; i < n; ++i){
		if(lad[i].size() == 0 and fabs(mx - dp[i]) <= eps) cout << i + 1 << " ";
	}
	return 0;
}
