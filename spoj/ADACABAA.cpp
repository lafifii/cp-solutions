#include <bits/stdc++.h>
using namespace std;
const int maxn = 200005;
unordered_map<int,int> bit[maxn];
int n;
/*
  
  eliminar elmento para los que su (a,b,c,d) sea menor a 
  algun otro
  
*/

void update(int y, int x, int val){
	for(; y <= n; y+= y&-y)
		for(int j = x; j <= n; j+= j&-j){
			if(bit[y].count(j)) bit[y][j] = min(bit[y][j], val);
			else bit[y][j] = val;
		}
}
int query(int y, int x){
	int ans = 1e9;
	for(; y > 0; y-= y&-y)
		for(int j = x; j > 0; j-= j&-j) if(bit[y].count(j)) ans = min(ans, bit[y][j]);
		
	return ans;
}
struct el{
	int x, y, z, w;
	bool operator<(const el &r)const{return x <r.x;}
};

el a[maxn];

int main() {
	int ans = 0;
	scanf("%d", &n);
	
	for(int i = 0; i < n; ++i){ 
		scanf("%d%d%d%d", &a[i].x, &a[i].y, &a[i].z, &a[i].w);
	}
	sort(a , a + n);
	for(int i = 0; i < n; ++i){ 
		int q = query(a[i].y, a[i].z);
		if(q > a[i].w) ans++;
		update(a[i].y, a[i].z, a[i].w);
	}
	printf("%d", ans);
	return 0;
}
