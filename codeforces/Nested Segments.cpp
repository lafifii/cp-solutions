#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 1;
int t[4*maxn], ar[maxn];

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
int main() {
	int n,x;
	scanf("%d", &n);
	memset(t,0,sizeof(t));
	memset(ar,-1,sizeof(ar));
	vector<int> ans(n+1, 0);
	for(int i = 0; i < 2*n; ++i){
		scanf("%d", &x);
		if(ar[x] == -1) ar[x] = i;
		else{
			ans[x] = query(1,0,2*n-1,ar[x],i);
			update(1,0,2*n-1,ar[x],1);
		}
	}
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}