#include <bits/stdc++.h>
using namespace std;
/*
  array A con N elementos
  queries:
  1. cambia elemento x a num
  2. suma de todos los pares bajo operacion (or xor and)
  ejemplo: 10 20 30 or
  (10 or 20) + (10 or 30) + (20 or 30)
  
*/
const int maxn = 1e5 + 40;
long long bit[30][maxn];

void update(int b, int x, long long val){
	for(; x < maxn; x+=x&-x) bit[b][x]+= val;
}
long long query(int b, int x){
	long long sum = 0;
	for(; x > 0; x-=x&-x) sum+= bit[b][x];
	return sum;
}
char s[39];
int main() {
	memset(bit,0,sizeof(bit));
	int n, q, t, x, num, l, r;
	
	scanf("%d%d", &n, &q);
	vector<long long> a(n + 1);
	for(int i = 1; i <= n; ++i){
		scanf("%lld", &a[i]);
		for(int b = 0; b < 28; ++b){ 
			int val = ((a[i] & (1 << b)));
			if(val) update(b, i, 1);
		}
	}
	while(q--){
		scanf("%d", &t);
		if(t == 1){
			scanf("%d%d", &num, &x);
			for(int b = 0; b < 28; ++b) if((a[x] & (1 << b))) update(b, x, -1);
			a[x] = num;
			for(int b = 0; b < 28; ++b) if((a[x] & (1 << b))) update(b, x, 1);
		}
		else{
			scanf("%s", &s[0]);
			scanf("%d%d", &l, &r);
			
			if(l == r){ 
				puts("0");
				continue;
			}
			long long ans = 0;
			for(int b = 0; b < 28; ++b){
				long long ones = query(b, r) - query(b, l - 1), ps = 0;
				long long zeros = (r - l + 1) - ones;
				long long len = (r - l + 1);
				
				if(s[0] == 'O'){
					ps = len*(len - 1LL)/2LL;
					ps-= zeros*(zeros - 1LL)/2LL;
				}
				else if(s[0] == 'A') ps = ones*(ones - 1LL)/2LL;
				else ps = ones*zeros;
				
				ans+= (1LL << b)*ps;
			}

			printf("%lld\n", ans);

		}
	}
	return 0;
}
