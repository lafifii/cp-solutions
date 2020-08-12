// Minium N such that N! has x trailing zeros
#include <bits/stdc++.h>
using namespace std;
int zeros(long long n){ // cuentra trailing zeros en N!
	long long ans = 0;
	while(n > 0){
		n/=5;
		ans+=n;
	}
	return ans;
}
int main() {
	long long t, q,tc = 1;
	cin >> t;
	while(t--){
		cin >> q;
		long long lo = 0, hi = 1e10;
		while(lo < hi){
			long long mid = (lo + hi)/2;
			if(zeros(mid) < q) lo = mid + 1; // primer true
			else hi = mid;
		}
		cout << "Case " << tc++ << ": ";
		if(zeros(lo) == q) cout << lo << endl;
		else puts("impossible");
 	}
	return 0;
}
