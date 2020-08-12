#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 10;
const int mod = 1000000007;

long long bit[maxn], fact[maxn], a[maxn];
int n;
void update(int x, int val){
	for(; x <= n; x+= x&-x) bit[x]+= val;
}
long long query(int x){
	long long sum = 0;
	for(; x > 0; x-=x&-x) sum+= bit[x];
	return sum;
}
int main() {
	int t;
	scanf("%d", &t);
	
	fact[0] = fact[1] = 1;
	for(int i = 2; i < maxn; ++i) fact[i] = (fact[i - 1]*i)%mod;
	
	while(t--){
		scanf("%d", &n);
		memset(bit,0,sizeof(bit));
		for(int i = 1; i <= n; ++i){ 
			scanf("%lld", &a[i]);
			update(i, 1);
		}
		long long ans = 1;
		for(int i = 1, cn = n - 1; i <= n; ++i, cn--){
			int q = query(a[i] - 1);
			ans = (ans + (q*fact[cn])%mod)%mod; // (n - 1)! x #menores
			update(a[i], -1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
