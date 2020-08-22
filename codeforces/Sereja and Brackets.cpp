#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 20;
char s[maxn];
struct node{ int op, cl, ans; };
node t[4*maxn];
node merge(node a, node b){
	node c;
	int mn = min(a.op, b.cl);
	c.ans = a.ans + b.ans + mn;
	c.op = a.op + b.op - mn;
	c.cl = a.cl + b.cl - mn;
	return c;
}
void build(int v, int l, int r){
	if(l == r){
		t[v].op = s[l] == '(';
		t[v].cl = s[l] == ')';
		t[v].ans = 0;
	} 
	else{
		int mid = (l + r)/2;
		build(v*2,l,mid);
		build(v*2+1,mid+1,r);
		t[v] = merge(t[v*2],t[v*2+1]);
	}
}
node query(int v, int l, int r, int lo, int hi){
	if(lo > hi) return {0,0,0};
	if(lo == l and hi == r) return t[v];
	int mid = (l + r)/2;
	return merge(query(2*v,l,mid,lo,min(mid,hi)), query(2*v+1,mid+1,r,max(mid+1,lo),hi));
}
int main() {
	int n, q, l, r;
	scanf("%s", s);
	scanf("%d", &q);
	n = strlen(s);
	build(1,0,n-1);
	for(int i = 0; i < q; ++i){
		scanf("%d%d", &l, &r); l--, r--;
		printf("%d\n", query(1,0,n-1,l,r).ans*2);
	}
	
	return 0;
}