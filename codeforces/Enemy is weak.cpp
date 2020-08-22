#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int t[2][4*maxn];
void update(int v, int l, int r, int pos, int id, int val){
	if(l == r) t[id][v]+=val;
	else{
		int mid = (l+r)/2;
		if(pos <= mid) update(2*v,l,mid,pos,id,val);
		else update(2*v+1,mid+1,r,pos,id,val);
		t[id][v] = t[id][2*v] + t[id][2*v+1]; 
	}
}
int query(int v, int l, int r, int lo, int hi, int id){
	if(lo > hi) return 0;
	if(lo == l and hi == r) return t[id][v];
	int mid = (l+r)/2;
	return query(2*v,l,mid,lo,min(hi,mid),id) + query(2*v+1,mid+1,r,max(lo,mid+1),hi,id);
}
int main() {
	int n;
	scanf("%d", &n);
	vector<int> v(n);
	map<int,int> mp;
	for(int i = 0; i < n; ++i){
		scanf("%d", &v[i]);
		mp[v[i]];
	}
	int id = 0;
	for(auto &x: mp) x.second = id++;
	for(int i = 0; i < n; ++i){ 
		v[i] = mp[v[i]];
		if(i < n - 1) update(1,0,n-1,v[i],0,1);
	}
	long long ans = 0;
	update(1,0,n-1,v[n-1],1,1);
	for(int i = n-2; i > 0; --i){
		long long q_r = query(1,0,n-1,0,v[i]-1,1);
		long long q_i = query(1,0,n-1,v[i]+1,n-1,0);
		ans+= (q_r*q_i);
		update(1,0,n-1,v[i],1,1);
		update(1,0,n-1,v[i],0,-1);
	}
	printf("%I64d\n", ans);
	return 0;
}