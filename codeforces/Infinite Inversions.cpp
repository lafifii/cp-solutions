#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
long long bit[maxn];
int a[maxn], b[maxn], p[maxn], n;
void sum(int x){
	for(; x <= n; x+= x&-x) bit[x]++;	
}
long long query(int x){
	long long s = 0;
	for(; x > 0; x-= x&-x) s+= bit[x];
	return s;
}
int main() {
	int q;
	n = 1;
	scanf("%d", &q);
	map<int,int> mp, ord;
	for(int i = 0; i < q; ++i){
		scanf("%d%d", &a[i], &b[i]);
		mp[a[i]], mp[b[i]];
	}
	
	for(auto&x: mp) x.second = n++;
	for(auto x: mp) ord[x.second] = x.first;
	n = mp.size();
	
	for(int i = 1; i <= n; ++i) p[i] = i;
	for(int i = 0; i < q; ++i){
		a[i] = mp[a[i]];
		b[i] = mp[b[i]];
		swap(p[a[i]], p[b[i]]);
	}
	
	long long ans = 0;
	for(int i = n; i > 0; --i){
		ans+= query(p[i]);
		sum(p[i]);
	}
	for(int i = 1; i <= n; ++i){
		int ini = i, fin = p[i];
		if(ini > fin) swap(ini,fin);
		ans+= (ord[fin] - ord[ini] - 1) - (fin - ini - 1);
	}
	printf("%lld", ans);
	
	return 0;
}