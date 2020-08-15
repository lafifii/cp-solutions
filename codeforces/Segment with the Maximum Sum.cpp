#include <bits/stdc++.h>
using namespace std;
struct node{long long pref, suf, sum, maxsum; };
const int maxn = 1e5 + 10;
node t[4*maxn];
int a[maxn];
node merge(node a, node b){
	node c;
	c.sum = a.sum + b.sum;
	c.pref = max(a.pref, a.sum + b.pref);
	c.suf = max(b.suf, b.sum + a.suf);
	c.maxsum = max({c.pref, c.suf, a.maxsum, b.maxsum, a.suf + b.pref});
	return c;
}
void build(int v, int l, int r){
	if(l == r)
		t[v].sum = t[v].pref = t[v].suf = t[v].maxsum = a[l];
	else{
		int mid = (l + r)/2;
		build(2*v,l,mid);
		build(2*v+1,mid+1,r);
		t[v] = merge(t[2*v], t[2*v+1]);
	}
}
void update(int v, int l, int r, int pos, int val){
	if(l == r) t[v].sum = t[v].pref = t[v].suf = t[v].maxsum = val; 	
	else{
		int mid = (l + r)/2;
		if(pos <= mid) update(2*v,l,mid,pos,val);
		else update(2*v+1,mid+1,r,pos,val);
		t[v] = merge(t[2*v], t[2*v+1]);
	}
}
int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
	build(1,0,n-1);
	printf("%lld\n", t[1].maxsum > 0 ? t[1].maxsum : 0);
	for(int i = 0; i < q; ++i){
		int id, x;
		scanf("%d%d", &id, &x);
		update(1,0,n-1,id,x);
		printf("%lld\n", t[1].maxsum > 0 ? t[1].maxsum : 0);
	}
	return 0;
}