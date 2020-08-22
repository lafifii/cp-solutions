#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1;
int t[4*maxn], ar[maxn];

int query(int v, int l, int r, int lo, int hi){
	if(lo > hi) return 0;
	if(l == lo and hi == r){
		return t[v];
	}
	int mid = (l + r)/2;
	return query(2*v,l,mid,lo, min(mid, hi)) + query(2*v+1,mid+1,hi,max(mid+1,lo),hi);
}
void update(int v, int l, int r, int pos){
	if(l == r) t[v]++;
	else{
		int mid = (l + r)/2;
		if(pos <= mid) update(2*v,l,mid,pos);
		else update(2*v+1,mid+1,r,pos);
		t[v] = t[2*v] + t[2*v+1];
	}
}
int main() {
	int n;
	scanf("%d", &n);
	memset(t,0,sizeof(t));
	for(int i =0; i < n; ++i){
		int x; scanf("%d", &x);
		int q = query(1,0,n,x+1,n);
		printf("%d ", q);
		update(1,0,n,x);
	}
	return 0;
}