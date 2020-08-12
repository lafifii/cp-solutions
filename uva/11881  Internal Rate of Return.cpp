#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;
int n, cf[maxn];
double eps = 1e-6;
double pred(double v){
	double ans = cf[0], base = 1 + v;
	for(int i = 1; i <= n; ++i)
		ans+= (cf[i]/base), base*=(1 +  v);
	
	return ans;
}
int main(){
	
	while(cin >> n and n){
		for(int i = 0; i <= n; ++i)
			cin >> cf[i];
		
		double lo = -0.9999, hi = 100, ans = 100;
		for(int i = 0; i <= 100; ++i){
			double mid = (lo + hi)/2.0;
			double uwu = pred(mid);
			if(abs(uwu) <= eps){ 
				ans = mid;
				break;
			}
			if(uwu > eps) lo = mid;
			else hi = mid;
		}
		if(pred(ans) > eps) puts("No");
		else printf("%.2f\n", ans);;
		
	}
	return 0;
}
