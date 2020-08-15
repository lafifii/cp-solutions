#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int t[4*maxn];
int a[maxn];
int merge(int a, int b){
	return a + b;
}
void build(int v, int l, int r){
	if(l == r)
		t[v] = a[l];
	else{
		int mid = (l + r)/2;
		build(2*v,l,mid);
		build(2*v+1,mid+1,r);
		t[v] = merge(t[2*v], t[2*v+1]);
	}
}
void update(int v, int l, int r, int pos){
	if(l == r) t[v] = !t[v]; 	
	else{
		int mid = (l + r)/2;
		if(pos <= mid) update(2*v,l,mid,pos);
		else update(2*v+1,mid+1,r,pos);
		t[v] = merge(t[2*v], t[2*v+1]);
	}
}
int kth(int v, int l, int r, int k){
	if(k > t[v]) return -1;
	if(l == r) return l;
	int mid = (l + r)/2;
	if(k <= t[2*v]) return kth(2*v,l,mid,k);
	return kth(2*v+1,mid+1,r,k-t[2*v]);
}

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
	build(1,0,n-1);
	for(int i = 0; i < q; ++i){
		int id, x;
		scanf("%d%d", &id, &x);
		if(id == 1) update(1,0,n-1,x);
		else{
			id = kth(1,0,n-1,x + 1);
			printf("%d\n", id);
		}
	}
	return 0;
}