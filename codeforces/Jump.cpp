#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e4 + 10;
int A[maxn], dis[3*maxn][3], tt, s, t;
int main() {
	int n; cin >> n;
	queue<int> Q;
	memset(dis,-1,sizeof(dis));
	for(int i = 0; i < n; ++i){ 
		cin >> A[i];
		Q.push(A[i]);
		dis[A[i] + maxn][1] = 1;
		Q.push(1);
	}
	dis[maxn][0] = 0;
	while(not Q.empty()){
		int x = Q.front(); Q.pop();
		int par = Q.front(); Q.pop();
		for(int i = 0; i < n; ++i){
			int num = x - A[i];
			if(!par) num = A[i] + x;
			if(num <= -3e4 or num >= 3e4 or dis[num + maxn][(par + 1)%2] != -1) continue;
			dis[num + maxn][(par + 1)%2] = dis[x + maxn][par] + 1;
			Q.push(num);
			Q.push((par + 1)%2);
		}
	}
	cin >> tt;
	while(tt--){
		cin >> s >> t;
		int v1, v2;
		if(dis[(s - t)/2 + maxn][0] == -1 or (s - t)%2) v1 = INT_MAX;
		else v1 = dis[(s - t)/2 + maxn][0];
		if(dis[(s + t)/2 + maxn][1] == -1 or (s + t)%2) v2 = INT_MAX;
		else v2 = dis[(s + t)/2 + maxn][1];
		int ans = (min(v1,v2) == INT_MAX ? -1 : min(v1,v2));
		cout << ans << endl;
	}
	return 0;
}
