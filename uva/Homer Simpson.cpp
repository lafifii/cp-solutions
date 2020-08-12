/*
 Taking tipe A takes N minutes and B takes M
 You need to take maximum of any type in T minutes
 and minimize the minutes in wich you do not take anything
*/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000 + 5;
int n, m, t;
int dp[maxn];

int main() {
	while(cin >> n >> m >> t){
		memset(dp,-1,sizeof(dp));
		for(int i = t; i >= 0; --i){
			int tomo_m = 0, tomo_n = 0;
			if(i == t) dp[i] = 0;
			else{
				if(i + n <= t) tomo_n = 1 + dp[i + n];
				if(i + m <= t) tomo_m = 1 + dp[i + m];
				tomo_n = max(tomo_n, tomo_m);
				if(tomo_n <= 0) continue;
				dp[i] = tomo_n;
			}
		}
		if(dp[0] >= 0) cout << dp[0] << endl;
		else{
			for(int i = 0; i <= t; ++i){
				if(dp[i] >= 0){
					cout << dp[i] << ' ' << i << endl;
					break;
				}
			}
		}
	}
	return 0;
}
