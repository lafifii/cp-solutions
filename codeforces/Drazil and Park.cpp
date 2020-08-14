#include <bits/stdc++.h>
using namespace std;
// Segment Tree: Generalization of maximum subarray

const int maxn = 1e5 + 20;
struct node{ long long suf, pref, dis, val; };
node t[4*maxn];
long long d[maxn], h[maxn];

node NE = {0,0,0,0};

node merge(node a, node b){
	
	if(a.pref == 0 || a.suf == 0) return b;
	if(b.pref == 0 || b.suf == 0) return a;
	
	node ans;
	ans.val = max({a.val, b.val, a.suf + b.pref});
	ans.suf = max(b.suf , b.dis + a.suf);
	ans.pref = max(a.pref, b.pref + a.dis);
	ans.dis = a.dis + b.dis;
	return ans;
}

void build(int v, int l, int r){
	if(l == r){
		t[v].suf = 2*h[l] + d[l];
		t[v].pref = 2*h[l];
		t[v].dis = d[l];
		t[v].val = 0;
	}	
	else{
		int mid = (l + r)/2;
		build(2*v,l,mid);
		build(2*v+1,mid+1,r);
		t[v] = merge(t[2*v], t[2*v + 1]);
	}
}

node query(int v, int l, int r, int lo, int hi){
	if(lo > hi) return NE;
	if(l == lo and r == hi){ 
		return t[v];
	}
	int mid = (l + r)/2;
	node a = query(2*v, l, mid, lo, min(mid, hi));
	node b = query(2*v + 1, mid + 1, r, max(mid + 1, lo), hi);
	
	return merge(a, b);
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i){
		scanf("%lld", &d[i]);
	}
	
	for(int i = 0; i < n; ++i){
		scanf("%lld", &h[i]);
	}

	build(1, 0, n - 1);
	
	for(int i = 0; i < m; ++i){
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		node ans;
		if(x <= y){
			ans = merge( query(1,0,n-1,y+1, n - 1), query(1,0,n-1,0, x - 1));
		}
		else{
			ans = query(1,0,n-1,y+1,x-1);
		}
		printf("%lld\n", ans.val);
	}
	
	return 0;
}

