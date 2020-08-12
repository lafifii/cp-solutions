#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 20;

int p[maxn];
int sz[maxn];
char s[maxn];
bool ok[maxn];

// DSU

void make(int n){
	for(int i = 0; i < n; ++i){
		p[i] = i;
		sz[i] = 1;
	}
}

int find(int u){
	if(u == p[u]) return u;
	return p[u] = find(p[u]);
}

void merge(int b, int a){
	a = find(a), b = find(b);
	if(a != b){
		p[a] = b;
		sz[b]+= sz[a];
	}
}
struct query{ int t, i; };

void solve(){
	
	int n, q;
	scanf("%s", s);
	n = strlen(s);
	
	scanf("%d", &q);
	
	vector<query> qs;
	memset(ok,1,sizeof(ok));
	
	for(int i = 0; i < q; ++i){
		int tt, ii;
		scanf("%d%d", &tt, &ii);
		if(tt == 2 and ok[ii]){ 
			ok[ii] = 0;
			qs.push_back({tt, ii});
		}
		else qs.push_back({tt, ii});
	}
	
	
	q = qs.size();
	make(n);
	
	for(int i = 0; i < n; ++i){
		char prev = s[i];

		if(ok[i]){
			int ini = i;
			while(i < n and ok[i] and s[i] == prev) i++;
			i--;
			for(int j = ini; j < i; ++j){
				merge(j , j + 1);
			}
		}
	}
	
	vector<int> ans;
	
	for(int i = q - 1; i >= 0; --i){
		char letra = s[qs[i].i];
		if(qs[i].t == 1){
			ans.emplace_back(sz[find(qs[i].i)]);
		}
		else{
			int id = qs[i].i;
			ok[id] = 1;
			
			bool entro = 0;
			if(id - 1 >= 0 and s[id - 1] == s[id] and ok[id - 1]){
				entro = 1;
				merge(id, id - 1);
			}
			
			if(id + 1 < n and s[id + 1] == s[id] and ok[id + 1]){
				entro = 1;
				merge(id, id + 1);
			}
		}
	}
	
	for(int i = (int) ans.size() - 1; i >= 0; --i) printf("%d\n", ans[i]);
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