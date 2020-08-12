#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 20;
int p[maxn];
int cl[maxn];

// DSU 

void make(int n){
	for(int i = 0; i < n; ++i){
		p[i] = i;
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
struct query{ int l, r, c; };
int main() {
	
	int n, q;
	scanf("%d%d", &n, &q);
	make(n + 10);
	vector<query> qs(q);
	for(int i = 0; i < q; ++i){
		scanf("%d%d%d", &qs[i].l, &qs[i].r, &qs[i].c);
		qs[i].l--, qs[i].r--;
	}
	
	for(int i = q - 1; i >= 0; --i){
		int j = qs[i].l;
		for(j = find(j) ; j <= qs[i].r; j = find(j + 1) ){
			cl[j] = qs[i].c;
			merge(j, j + 1);
		}
	}

	for(int i = 0; i < n; ++i) printf("%d\n", cl[i]);
	
	return 0;
}