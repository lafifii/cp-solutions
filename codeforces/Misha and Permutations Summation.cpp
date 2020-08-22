#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 20;
int a[2][maxn], t[2][4*maxn];
void build(int v, int l, int r){
	if(l == r) t[0][v] = t[1][v] = 1;
	else{
		int mid = (l+r)/2;
		build(2*v,l,mid);
		build(2*v+1,mid+1,r);
		t[0][v] = t[0][2*v] + t[0][2*v+1];
		t[1][v] = t[1][2*v] + t[1][2*v+1];
	}
}
void update(int v, int l, int r, int pos, int num, int id){
	if(l == r) t[id][v] = num;
	else{
		int mid = (l+r)/2;
		if(pos<=mid)update(2*v,l,mid,pos,num,id);
		else update(2*v+1,mid+1,r,pos,num,id);
		t[id][v] = t[id][2*v] + t[id][2*v+1];
	}
}
int query(int v, int l, int r, int lo, int hi, int id){
	if(lo > hi) return 0;
	if(lo == l and hi == r) return t[id][v];
	int mid = (l+r)/2;
	return query(2*v,l,mid,lo,min(mid,hi),id) + query(2*v+1,mid+1,r,max(mid+1,lo),hi,id);
}

int findk(int v, int l, int r, int k, int id){
	if(l == r) return l;
	int mid = (l + r)/2;
	if(t[id][2*v] > k) return findk(2*v,l,mid,k,id);
	return findk(2*v+1,mid+1,r,k-t[id][2*v],id);
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%d", &a[0][i]);
	for(int i = 0; i < n; ++i) scanf("%d", &a[1][i]);
	
	vector<int> sum(n,0);
	build(1,0,n-1);
	
	for(int i = 0; i < n; ++i){
		int qa = query(1,0,n-1,0,a[0][i]-1,0);
		int qb = query(1,0,n-1,0,a[1][i]-1,1);
		update(1,0,n-1,a[0][i],0,0);
		update(1,0,n-1,a[1][i],0,1);
		sum[i] = qa + qb;
	}
	
	sum[n-1] = 0;
	for(int i = n - 2; i >=  0; --i){
		if(i>0) sum[i - 1]+= (sum[i]/(n - i));
		sum[i]%=(n - i);
	}
	
	build(1,0,n-1);
	for(int i = 0; i < n; ++i){
		int k = findk(1,0,n-1,sum[i], 0);
		printf("%d ", k);
		update(1,0,n-1,k,0,0);
	}
	
	return 0;
}