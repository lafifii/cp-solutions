#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
bitset<maxn> pr; 
void sieve(){
	pr.set();
	pr[0] = pr[1] = 0;
	for(int i = 2; i*i < maxn; ++i){
		if(pr[i])
			for(int j = i*i; j < maxn; j+=i) 
				pr[j] = 0;
	}
}
// veces de P en N!
int veces(long long n , int p){
	int cnt = 0;
	for(int k = p; k <= n; k*= p)
		cnt+= (n/k);
	
	return cnt;
}
const int mod = 1e9 + 7;
int main() {
	sieve();
	int n; cin >> n;
	long long ans = 1;
	for(int i = 2; i <= n; ++i){
		if(!pr[i]) continue;
		ans = ans*( veces(n, i) + 1);
		ans%= mod;
	}
	cout << ans;
	return 0;
}
