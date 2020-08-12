#include <bits/stdc++.h>
using namespace std;
int n, a[30][30];
const int mod = 1e9 + 7;
// man i, woman j
long long dp[(1 << 22)][22];
long long f(int mask, int i){ // womans tomadas
	if(i == n) return mask == 0;
	if(dp[mask][i] != -1) return dp[mask][i];
	long long c = 0;
	for(int j = 0; j < n; ++j){
		if( (mask & (1<<j)) == 0) continue;
		if(a[i][j]){
			c+= f(mask - (1<<j), i + 1);
			c%=mod;
		}
	}
	return dp[mask][i] = c%mod;
}
int main() {
	memset(dp,-1,sizeof(dp));
	cin >> n;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) cin >> a[i][j];

	cout << f((1<<n) - 1, 0);
	return 0;
}
