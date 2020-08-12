#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 20;

// DSU 

int p[maxn];
int a[maxn];
int cl[maxn];


void make(int n){
	for(int i = 0; i < n; ++i){
		p[i] = i;
		cl[i] = a[i];
	}
}

int find(int u){
	if(u == p[u]) return u;
	return p[u] = find(p[u]);
}

void merge(int a, int b, int c){
	a = find(a), b = find(b);
	if(a != b){
		p[b] = a;
		cl[b] = cl[a] = c;
	}
}

void solve(){
	int n, q;
	scanf("%d%d", &n, &q);
	map<int, int> mp;
	map<int, vector<int> > mp2;
	for(int i = 0; i < n; ++i){ 
		scanf("%d", &a[i]);
		mp[a[i]] = i;
		mp2[a[i]].emplace_back(i);
	}
	make(n);
	for(auto x: mp2){
		for(int i = 0; i < (int) x.second.size() - 1; ++i){
			merge(x.second[i], x.second[i + 1], x.first);
		}	
	}
	
	for(int i = 0; i < q; ++i){
		int t,x,y;
		scanf("%d", &t);
		if(t == 1){
			scanf("%d%d", &x, &y);
			if(x == y) continue;
			if(mp.find(x) != mp.end()){
				int id_x = mp[x];
				if(mp.find(y) != mp.end()){
					int id_y = mp[y];
					merge(id_y, id_x, y);
				}
				else{
					cl[find(id_x)] = y;
					mp[y] = id_x;
				}
				mp.erase(x);
			}
		}
		else{
			scanf("%d", &x);
			x--;
			printf("%d\n", cl[find(x)]);
		}
	}
	
	
}

int main() {
	int t, tc = 1;
	scanf("%d", &t);
	while(t--){
		printf("Case %d:\n", tc++);
		solve();
	}
	return 0;
}