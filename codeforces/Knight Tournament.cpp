#include <bits/stdc++.h>
using namespace std;
//DSU
const int maxn = 3e5 + 20;

int p[maxn];
int c[maxn];

void make(int n){
	for(int i = 0; i < n; ++i){
		p[i] = i;
		c[i] = 0;
	}
}
int find(int u){
	if(u == p[u]) return u;
	return p[u] = find(p[u]);
}
void merge(int a, int b){
	a = find(a), b = find(b);
	if(a != b){ 
		p[a] = b;
	}
}
void comb(int l, int r, int cl){
	for(int j = find(l); j <= r; j = find(j + 1)){
		merge(j, j + 1);
		c[j] = cl + 1;
	}
}
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	make(n + 10);
	for(int i = 0; i < m; ++i){
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		l--, r--, x--;
		comb(l, x - 1, x);
		comb(x + 1, r, x);
	}
	for(int i = 0; i < n; ++i) printf("%d ", c[i]);
	
	return 0;
}