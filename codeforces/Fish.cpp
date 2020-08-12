#include <bits/stdc++.h>
using namespace std;
const int maxn = 19;
double a[maxn][maxn], dp[1 << 19];
bool vis[1 << 19];
int n;
double f(int mask){
	if(mask == 0) return 1;
	if(vis[mask]) return dp[mask];
	double prob = 0;
	int total = n - __builtin_popcount(mask);
	total*= (total + 1);

	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(i == j) continue;
			if((mask & (1 << j)) == 0) continue; // muerto
			if((mask & (1 << i)) > 0) continue; 
			double pij = (2.0/total) * a[i][j] * f(mask - (1 << j));
			prob+= pij;
		}
	}
	vis[mask] = 1;
	return dp[mask] = prob;
}
int main() {
	cin >> n;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) cin >> a[i][j];
	
	memset(vis,0,sizeof(vis));
	int mask = (1 << n) - 1;
	for(int i = 0; i < n; ++i)
		printf("%.6f ", f(mask - (1 << i)) );
	return 0;
}
