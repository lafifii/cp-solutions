#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
long long lazy[4*maxn], t[4*maxn];
void push(int v){
	lazy[2*v]+= lazy[v];
	t[2*v]+= lazy[v];
	lazy[2*v+1]+= lazy[v];
	t[2*v+1]+= lazy[v];
	lazy[v] = 0;
}
void update(int v, int l, int r, int lo, int hi, int val){
	if(lo > hi) return;
	if(l == lo and hi == r){
		lazy[v] += val;
		t[v]+=val;
	}
	else{
		push(v);
		int mid = (l+r)/2;
		update(2*v,l,mid,lo,min(mid,hi),val);
		update(2*v+1,mid+1,r,max(mid+1,lo),hi,val);
	}
}
long long query(int v, int l, int r, int pos){
	if(l == r) return t[v];
	int mid = (l+r)/2;
	push(v);
	if(pos<=mid) return query(2*v,l,mid,pos);
	return query(2*v+1,mid+1,r,pos);
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i){
		int b,c,d,e;
		scanf("%d", &b);
		if(b == 2){
			scanf("%d", &c);
			printf("%lld\n", query(1,0,n-1,c));
		}
		else{
			scanf("%d%d%d", &c, &d, &e);
			update(1,0,n-1,c,d-1,e);
		}
	}
	return 0;
}