#include <bits/stdc++.h>
using namespace std;
// Segment Tree
const int maxn = 1e5 + 3;

int t[30][4*maxn];
char s[maxn];

int merge(int a, int b){
	return a + b;
}
void build(int v, int l, int r, int cr){
	if(l == r) t[cr][v] = (s[l] - 'a' == cr);
	else{
		int mid = (l + r)/2;
		build(2*v, l, mid, cr);
		build(2*v + 1, mid + 1, r, cr);
		t[cr][v] = merge(t[cr][2*v], t[cr][2*v + 1]);
	}
}

void update(int v, int l, int r, int pos, int val, int cr){
	if(l == r) t[cr][v] = val;	
	else{
		int mid = (l + r)/2;
		if(pos <= mid) update(2*v, l , mid, pos, val, cr);
		else update(2*v + 1, mid + 1, r, pos, val, cr);
		t[cr][v] = merge(t[cr][2*v], t[cr][2*v + 1]);
	}
}

int query(int v, int l, int r, int lo, int hi, int cr){
	if(lo > hi)	return 0;
	if(l == lo and r == hi) return t[cr][v];
	int mid = (l + r)/2;
	
	int iz = query(2*v, l,  mid, lo, min(hi, mid), cr);
	int dr = query(2*v + 1, mid + 1,  r, max(mid + 1, lo), hi, cr);
	
	return merge(iz, dr);
}

int main() {
	scanf("%s", s);
	int n = strlen(s);
	for(char i = 'a'; i <= 'z'; ++i) build(1, 0, n - 1, i - 'a');
	int q;
	scanf("%d", &q);
	
	for(int i = 0; i < q; ++i){
		int tt, l, r; char c;
		scanf("%d", &tt);
		if(tt == 1){
			scanf("%d %c", &l, &c);
			l--;
			update(1, 0, n - 1, l, 0, s[l] - 'a');
			s[l] = c;
			update(1, 0, n - 1, l, 1, s[l] - 'a');
		}
		else{
			scanf("%d%d", &l, &r);
			l--, r--;
			int cn = 0;
			for(char j = 'a'; j <= 'z'; ++j){
				cn+= (query(1, 0, n - 1, l, r, j - 'a') > 0);
			
			}
			printf("%d\n", cn);
		}
	}
	
	return 0;
}