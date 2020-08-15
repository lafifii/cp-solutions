#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 20;
long long t[4*maxn], lazy[4*maxn];
int a[maxn];

void build(int v, int l, int r){
	if(l == r) t[v] = a[l];
	else{
		int mid = (l + r)/2;
		build(2*v, l, mid);
		build(2*v + 1, mid + 1, r);
		t[v] = min(t[2*v], t[2*v+1]);
	}
}

void push(int v){
	t[2*v]+= lazy[v];
	lazy[2*v]+= lazy[v];
	t[2*v + 1]+= lazy[v];
	lazy[2*v + 1]+= lazy[v];
	lazy[v] = 0;
}

void upd(int v, int l, int r, int lo, int hi, int val){
	if(lo > hi) return;
	if(lo == l and r == hi){
		t[v]+=val;
		lazy[v]+=val;
	}
	else{
		push(v);
		int mid = (l + r)/2;
		upd(2*v, l, mid, lo, min(mid, hi), val);
		upd(2*v+1, mid + 1, r, max(mid + 1, lo), hi, val);
		t[v] = min(t[2*v], t[2*v+1]);
	}
}

long long query(int v, int l, int r, int lo, int hi){
	if(lo > hi) return LLONG_MAX;
	if(lo == l and r == hi) return t[v];
	push(v);
	int mid = (l + r)/2;
	long long a = query(2*v,l,mid,lo, min(mid, hi));
	long long b = query(2*v + 1,mid+1,r,max(lo,mid+1), hi);
	return min(a, b);
}

vector<int> split(string &s){
	int num = 0, sign = 1;
	vector<int> v;
	for(int i = 0; i < s.size(); ++i){
		if(s[i] == ' '){ 
			v.emplace_back(num*sign);
			num = 0;
			sign = 1;
		}
		else if(s[i] == '-') sign = -1;
		else num = num*10 + (s[i] - '0');
	}
	v.emplace_back(num*sign);
	return v;
}

int main() {
	int n,q;
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> a[i];
	build(1,0,n-1);
	cin >> q;
	string s; getline(cin, s);
	for(int i = 0; i < q; ++i){
		getline(cin, s);
		vector<int> v = split(s);
		if(v.size() == 2){
			if(v[0] <= v[1]) cout << query(1,0,n-1,v[0],v[1]) << endl;
			else cout << min(query(1,0,n-1,v[0],n-1),query(1,0,n-1,0,v[1])) << endl;
		}
		else{
			if(v[0] <= v[1]) upd(1,0,n-1,v[0],v[1],v[2]);
			else{
				upd(1,0,n-1,v[0],n-1,v[2]);
				upd(1,0,n-1,0,v[1],v[2]);
			}
		}
		
	}
	
	return 0;
}
