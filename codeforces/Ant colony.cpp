#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 3;
const int inf = 1e9 + 7;

struct node{ int mn, cn, gcd; };
node t[4*maxn];
int a[maxn];

node merge(node a, node b){
	int cn = 0;
	if(a.mn == b.mn)  cn = a.cn + b.cn;
	else cn = a.mn < b.mn ? a.cn : b.cn;
	return { min(a.mn, b.mn) , cn , __gcd(a.gcd, b.gcd) };
}

void build(int v, int l, int r){
	if(l == r){
		t[v].mn = a[l];
		t[v].gcd = a[l];
		t[v].cn = 1;
	}
	else{
		int mid = (l + r)/2;
		build(2*v, l, mid);
		build(2*v + 1, mid + 1, r);
		t[v] = merge(t[2*v], t[2*v + 1]);
	}
}

node query(int v, int l, int r, int lo, int hi){
	if(lo > hi)	return {inf,0,0};
	if(l == lo and r == hi) return t[v];
	int mid = (l + r)/2;
	
	node iz = query(2*v, l,  mid, lo, min(hi, mid));
	node dr = query(2*v + 1, mid + 1,  r, max(mid + 1, lo), hi);
	
	return merge(iz, dr);
}

int main() {
	int n, q;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
	build(1, 0, n - 1);
	scanf("%d", &q);
	for(int i = 0; i < q; ++i){
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		node v = query(1, 0, n - 1, l, r);
		int ans = r - l + 1;
		if(v.gcd == v.mn) ans-=v.cn;
		printf("%d\n", ans);
	}
	return 0;
}