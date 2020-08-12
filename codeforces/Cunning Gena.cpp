#include <bits/stdc++.h>
using namespace std;
/*
  bitmask dp (pos, mask)
  donde pos es el ultimo valor que tomas
*/
typedef pair< pair<int,int> , int >  amigo; // (valor, mask) , monitors
vector<amigo> A;
int n;
long long b;
bool cmp(amigo a, amigo b){
	return a.second < b.second;
}
long long dp[1 << 20];
long long ans[200];
int main() {
	int m;
	cin >> n >> m >> b;
	for(int i = 0; i < (1<<20); ++i) dp[i] = LLONG_MAX;	
	for(int i = 0; i < n; ++i){
		int x,k,p, mask = 0, num;
		cin >> x >> k >> p;
		for(int j = 0; j < p; ++j){
			cin >> num;
			num--;
			mask|= (1 << num);
		}
		A.push_back({ {x, mask} , k});
	}
	sort(A.begin(), A.end(), cmp);
	long long real = LLONG_MAX;
	for(int pos = 0; pos < n; ++pos){
		for(int mask = 0; mask < (1<<m); ++mask){
			if(mask == 0){
				dp[mask] = 0;
				continue;
			}
			int comun = mask&A[pos].first.second;
			long long ans = dp[mask - comun];
			if(ans == LLONG_MAX) continue;
			dp[mask] = min(dp[mask], ans + A[pos].first.first);
		}	
		if(dp[(1<<m) - 1] != LLONG_MAX) ans[pos] =  dp[(1<<m) - 1] + A[pos].second*b;
		else ans[pos] = LLONG_MAX;
		real = min(ans[pos], real);
	}
	cout << (real == LLONG_MAX ? -1 : real);
	return 0;
}
