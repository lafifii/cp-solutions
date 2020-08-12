#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 20;
int dis[2][maxn];
vector<int> lad[maxn];
bool es(int n){
	if(n <= 1) return 0;
	for(int i = 2; i*i <= n; ++i)
		if(n%i == 0) return 0;
	return 1;
}
int main() {
	int u,v,n,m,s,t;
	cin >> n >> m >> s >> t;
	s--,t--;
	for(int i = 0; i < m; ++i){
		cin >> u >> v;
		u--,v--;
		lad[u].push_back(v);
		lad[v].push_back(u);
	}
	memset(dis,-1,sizeof(dis));
	queue<int> Q;
	Q.push(s);
	Q.push(0);
	dis[0][s] = 0;
	while(!Q.empty()){
		int x = Q.front(); Q.pop();
		int d = Q.front(); Q.pop();
		for(int y: lad[x]){
			if(dis[(d + 1)%2][y] != -1) continue;
			dis[(d + 1)%2][y] = dis[d][x] + 1;
			Q.push(y);
			Q.push((d + 1)%2);
		}
	}
	if(dis[0][t] == 2) cout << dis[0][t];
	else if(dis[1][t] == -1) cout << -1;
	else{
		for(int i = 0; i <= maxn; ++i){
			if(es(dis[1][t] + 2*i)){
				cout << dis[1][t] + 2*i;
				return 0;
			}
		}
		cout << -1;
	}

	return 0;
}
