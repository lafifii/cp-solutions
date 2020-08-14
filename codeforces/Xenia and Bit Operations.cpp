#include <bits/stdc++.h>
using namespace std;
// Segment Tree
const int maxn = (1 << 17) + 10;

int t[4*maxn];
int a[maxn];
int merge(int a, int b, int p){
	return p ? (a|b) : (a^b);
}
void build(int v, int l, int r, int p){
	if(l == r) t[v] = a[l];
	else{
		int mid = (l + r)/2;
		build(2*v, l, mid, !p);
		build(2*v + 1, mid + 1, r, !p);
		t[v] = merge(t[2*v], t[2*v + 1], p);
	}
}

void update(int v, int l, int r, int pos, int val, int p){
	if(l == r) t[v] = a[l] = val;	
	else{
		int mid = (l + r)/2;
		if(pos <= mid) update(2*v, l , mid, pos, val, !p);
		else update(2*v + 1, mid + 1, r, pos, val, !p);
		t[v] = merge(t[2*v], t[2*v + 1], p);
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	bool fst = n%2;
	n = (1 << n);
	for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
	build(1, 0, n - 1, fst);
	for(int i = 0; i < m; ++i){
		int p, x;
		scanf("%d%d", &p, &x);
		p--;
		update(1, 0, n - 1, p, x, fst);
		printf("%d\n", t[1]);
	}
	return 0;
}