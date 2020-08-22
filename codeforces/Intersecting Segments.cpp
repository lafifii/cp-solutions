#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int t[4*maxn], ar[maxn], ans[maxn], xs[maxn];

int query(int v, int l, int r, int lo, int hi){
	if(lo > hi) return 0;
	if(lo == l and hi == r) return t[v];
	int mid = (l + r)/2;
	return query(2*v,l,mid,lo,min(mid,hi)) + query(2*v+1,mid+1,r,max(mid+1,lo),hi);
}
void update(int v, int l, int r, int pos, int val){
	if(l == r) t[v] = val;
	else{
		int mid = (l + r)/2;
		if(pos <= mid) update(2*v,l,mid,pos,val);
		else update(2*v+1,mid+1,r,pos,val);
		t[v] = t[2*v] + t[2*v+1];
	}
}
void solve(int n){
	memset(ar,-1,sizeof(ar));
	for(int i = 0; i < 2*n; ++i){		
		int x = xs[i];
		if(ar[x] == -1){ 
			ar[x] = i;
			update(1,0,2*n-1,i,1);
		}
		else{
			update(1,0,2*n-1,ar[x],0);
			ans[x] += query(1,0,2*n-1,ar[x],i);
		}
	}
	
}
int main() {
	int n,x;
	scanf("%d", &n);
	for(int i = 0; i < 2*n; ++i) scanf("%d", &xs[i]);
	solve(n);
	reverse(xs, xs + 2*n);
	solve(n);
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}