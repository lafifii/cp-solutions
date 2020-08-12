#include <bits/stdc++.h>
using namespace std;
const int maxn = 600;
/*
  Minimo valor con el que tienes que empezar en (1,1) para que en tu path hasta 
  el (n,m) nunca mueras (energia < 0).
  
  Solucion: Binary search para fijar el valor con el que empiezas y teniendo ese valor
  mid vemos si en algun momento tu path no sera menor a 0, esto esta limitado por
  el minimo entre a[i][j] y la suma maxima que puedes formar hasta cierto momento
  regresando del (n, m) hasta (i,j), bottom up
*/
int n, m, dp[maxn][maxn], a[maxn][maxn];
bool vis[maxn][maxn];
int f(int i, int j){
	if(i == n - 1 and j == m -1) return 0;
	if(vis[i][j]) return dp[i][j];
	int derecha = (j + 1 <= m - 1 ? a[i][j] + f(i, j + 1) : INT_MIN);
	int abajo = (i + 1 <= n - 1 ? a[i][j] + f(i + 1, j) : INT_MIN);
	vis[i][j] = 1;
	return dp[i][j] = min(a[i][j], max(derecha, abajo));
}
bool pred(int mid){
	a[0][0] = mid;
	memset(vis,0,sizeof(vis));
	return f(0,0) > 0;
}
int main() {
	int t;
	cin >> t;
	while(t--){
		cin >> n >> m;
		
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j) cin >> a[i][j];
		
		int lo = 0, hi = 1e9, ans = 1e9;
		while(lo <= hi){
			long long mid = (lo + hi)/2;
			if(pred(mid)) ans = mid, hi = mid - 1;
			else lo = mid + 1;
		}
		cout << ans << endl;
	}
	return 0;
}
