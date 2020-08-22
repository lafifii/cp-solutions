#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 20;
int a[21][maxn], t[21][4*maxn], lazy[21][4*maxn];

void build(int v, int l, int r){
	if(l == r){
		for(int i = 0; i < 21; ++i){ 
			t[i][v] = a[i][l];
		}
	}
	else{
		int mid = (l+r)/2;
		build(2*v,l,mid);
		build(2*v+1,mid+1,r);
		for(int i = 0; i < 21; ++i)
			t[i][v] = t[i][2*v] + t[i][2*v+1];
	}
}
void push(int id, int v, int l, int r){
	if(lazy[id][v] > 0){
		t[id][v] = (r-l+1) - t[id][v];
		
        if(l<r)
        {          
            lazy[id][2*v]^=1;
            lazy[id][2*v+1]^=1;
            
            
        }
        lazy[id][v] = 0;
	}
}
int query(int v, int l, int r, int lo, int hi, int id){
	push(id,v,l,r);
    if(lo > hi) return 0;
	if(lo == l and hi == r){
		return t[id][v];
	}
	int mid = (l+r)/2, sum = 0;
	int ans = query(2*v,l,mid,lo,min(hi,mid),id) + query(2*v+1,mid+1,r,max(mid+1,lo),hi,id);
	return ans;
}
void upd(int v, int l, int r, int lo, int hi, int id){
	push(id,v,l,r);
    if(lo > hi) return;
	if(lo == l and r == hi){ 
		lazy[id][v] ^= 1;
        push(id,v,l,r);
	}
	else{
		int mid = (l + r)/2;
		upd(2*v, l, mid, lo, min(mid, hi), id);
		upd(2*v+1, mid + 1, r, max(mid + 1, lo), hi, id);
		t[id][v] = t[id][2*v] + t[id][2*v+1];
	}
}
int main() {
	int n, num, q;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){ 
		scanf("%d", &num);
		for(int j = 0; j < 21; ++j){ 
			a[j][i] = (((1<<j)&num) > 0);
		}
	}
	scanf("%d", &q);
	build(1,0,n-1);
	for(int i = 0; i < q; ++i){
		int t, l, r;
		scanf("%d", &t);
		if(t == 1){
			scanf("%d%d", &l, &r);
			long long ans = 0;
			l--,r--;
			for(int j = 0; j < 21; ++j) ans+= (query(1,0,n-1,l,r,j)*(1LL<<j));
			
			printf("%lld\n", ans);
		}
		else{
			scanf("%d%d%d", &l, &r, &num);
			l--,r--;
			for(int j = 0; j < 21; ++j) if(((1<<j)&num) > 0) upd(1,0,n-1,l,r,j);
		}
	}
		
	return 0;
}