#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1;
int t[4*maxn], ar[maxn];

int query(int v, int l, int r, int sum){
	if(t[v] < sum) return 0;
	if(l == r) return l;
	int mid = (l + r)/2;
	if(t[2*v] >= sum) return query(2*v,l,mid,sum);
	return query(2*v+1,mid+1,r,sum-t[2*v]);
}
void update(int v, int l, int r, int pos, int delta){
	if(l == r) t[v]+=delta;
	else{
		int mid = (l + r)/2;
		if(pos <= mid) update(2*v,l,mid,pos,delta);
		else update(2*v+1,mid+1,r,pos,delta);
		t[v] = t[2*v] + t[2*v+1];
	}
}
int main() {
	int n;
	scanf("%d", &n);
	memset(t,0,sizeof(t));
	for(int i = 1; i <= n; ++i) update(1,0,n,i,1);
	vector<int> v(n), ans(n);
	for(int i = 0; i < n; ++i) scanf("%d", &v[i]);
	int id = n;
	for(int i = n - 1; i >= 0; --i){
		ans[i] = query(1,0,n,id-v[i]);
		update(1,0,n,ans[i],-1);
		id--;
	}
	for(int x: ans) printf("%d ", x);
	
	return 0;
}