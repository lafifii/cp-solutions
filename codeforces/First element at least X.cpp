#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1;
int t[4*maxn], ar[maxn];

int merge(int a, int b){
	return max(a,b);
}
void build(int v, int l, int r){
	if(l == r){
		t[v] = ar[r];
	}
	else{
		int mid = (l+r)/2;
		build(2*v,l,mid);
		build(2*v+1,mid+1,r);
		t[v] = merge(t[2*v], t[2*v+1]);
	}
}

int query(int v, int l, int r, int x){
	if(t[v] < x) return -1;
	if(l == r) return l;
	int mid = (l + r)/2;
	if(t[2*v] >= x) return query(2*v,l,mid,x);
	return query(2*v+1,mid+1,r,x);
}
void update(int v, int l, int r, int pos, int val){
	if(l == r) t[v] = val;
	else{
		int mid = (l + r)/2;
		if(pos <= mid) update(2*v,l,mid,pos,val);
		else update(2*v+1,mid+1,r,pos,val);
		t[v] = merge(t[2*v], t[2*v+1]);
	}
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) scanf("%d", &ar[i]);
	build(1,0,n-1);
	for(int i = 0; i < m; ++i){
		int a, b, c;
		scanf("%d", &a);
		if(a == 1){
			scanf("%d%d", &b, &c);
			update(1,0,n-1,b,c);
		}
		else{
			scanf("%d", &b);
			printf("%d\n", query(1,0,n-1,b));
		}
	}
	return 0;
}