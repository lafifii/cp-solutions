#include <bits/stdc++.h>
using namespace std;

// DSU

const int maxn = 1e5 + 20;
int p[30];
void make(){
	for(int i = 0; i < 30; ++i){
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
		if(a > b) swap(a, b);
		p[b] = a;
	}
}
char a[maxn];
char b[maxn];
char c[maxn];
int main() {

	scanf("%s", a);
	scanf("%s", b);
	scanf("%s", c);
	make();
	int n = strlen(a);
	for(int i = 0; i < n; ++i){ 
		merge(a[i] - 'a', b[i] - 'a');
	}

	n = strlen(c);
	for(int i = 0; i < n; ++i) printf("%c", find(c[i] - 'a') + 'a');
	
	return 0;
}