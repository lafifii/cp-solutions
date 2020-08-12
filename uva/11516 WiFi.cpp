#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 20;
int a[maxn], n;
bool pred(double maxi, int m){
	int g = 0;
	for(int i = 0; i < n; ++i){
		double faro = a[i] + maxi;
		int entro = 0;
		while(i < n and abs(a[i] - faro) <= maxi) entro = 1, i++;
		if(entro) i--;
		g++;
	}
	return g <= m;
}
int main(){
	int t,m;
	cin >> t;
	while(t--){
		cin >> m >> n;
		for(int i = 0; i < n; ++i) cin >> a[i];
		sort(a, a + n);
		double lo = 0, hi = 1e9, ans = 1e9;
		for(int i = 0; i <= 100; ++i){
			double mid = (lo + hi)/2.0;
			if(pred(mid, m)) ans = min(ans, mid), hi = mid;
			else lo = mid;
		}
		printf("%.1f\n", ans);
	}
	return 0;
}
