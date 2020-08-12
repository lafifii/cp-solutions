#include <bits/stdc++.h>
using namespace std;
/*
	 queries [L,R]
	 find the minimum multiplication value of all possible interval between index I to J, 
	 and also for that multiplication value you need to find the longest interval.
*/
const int maxn = 1e5 + 5;
int ST[4][maxn][40], a[maxn], ones[maxn];
bool cmp(pair<int,int> a, pair<int,int> b){
	if(a.second - a.first == b.second - b.first) return a.first < b.first;
	return a.second - a.first > b.second - b.first;
}
void build(int n){
	memset(ST,0,sizeof(ST));
	for(int i = 0; i < n; i++){ 
		ST[0][i][0] = a[i];
		ST[1][i][0] = ones[i];
	}
	for(int t = 0; t < 2; ++t)
		for(int j = 1; (1 << j) <= n; ++j) 
			for(int i = 0; i + ( 1<< j) <= n; ++i){
				if(t == 0) ST[t][i][j] = min(ST[t][i][j - 1], ST[t][i + (1 << (j - 1) ) ][j - 1]);
				else ST[t][i][j] = max(ST[t][i][j - 1], ST[t][i + (1 << (j - 1) ) ][j - 1]);
			}
}
int rmq(int L, int R){ //[L, R]
	int ans = INT_MAX, T =  R - L + 1;
	int lg = 31 - (__builtin_clz(T));
	for(int j = lg; j >= 0; --j){
		if( (1<<j) <= T){
			ans = min(ans, ST[0][L][j]);
			L+= ( 1 << j );
			T-= ( 1 << j );
		}
	}
	return ans;
}
int query(int L, int R){ //[L, R]
	int ans = INT_MIN, T =  R - L + 1;
	int lg = 31 - (__builtin_clz(T));
	for(int j = lg; j >= 0; --j){
		if( (1<<j) <= T){
			ans = max(ans, ST[1][L][j]);
			L+= ( 1 << j );
			T-= ( 1 << j );
		}
	}
	return ans;
}
void solve(){
	int n, q,l,r,lo,hi,id;
	cin >> n >> q;
	memset(ones,0,sizeof(ones));
	for(int i = 0; i < n; ++i) cin >> a[i];
	vector<pair<int,int>> rgs;
	for(int i = 0; i < n; ++i){
		int c = 0, inicio = i;
		if(a[i] == 1){
			while(i < n and a[i] == 1) i++, c++;
			i--;
			rgs.push_back({inicio, i});
			while(inicio <= i){
				ones[inicio] = c;
				inicio++, c--;
			}
		}
	}
	build(n);
	while(q--){
		cin >> l >> r;
		l--, r--;
		int qq = rmq(l,r);
		if(qq == 0) cout << qq << " " << l + 1 << " " << r + 1 << endl;
		else if(qq > 1){
			lo = l, hi = r, id = r;
			while(lo <= hi){
				int mid = (lo + hi)/2;
				int menor = rmq(l, mid);
				if(menor > qq) lo = mid + 1;
				else{
					id = min(id, mid);
					hi = mid - 1;
				}
			}
			cout << qq << " " << id + 1 << " " << id + 1 << endl;
		}
		else{
			lo = l, hi = r;
			int ans = l, len = 1;
			// VVVVFFFF ultimo true
			while(lo <= hi){
				int mid = (lo + hi)/2;
				int mayor = mid + query(l, mid) - 1;
				if(mayor > r) hi = mid - 1;
				else{
					ans = max(ans, mid);
					lo = mid + 1;
				}
			}
			lo = l, hi = ans;
			int valor = query(l,ans), pt = ans;
			while(lo <= hi){
				int mid = (lo + hi)/2;
				int mayor = query(l,mid);
				if(mayor >= valor){
					pt = min(pt, mid);
					hi = mid - 1;
				}
				else lo = mid + 1;
			}
			pair<int,int> op1,op2,op3;
			if(pt + ones[pt] - 1 <= r) op1 = {pt, pt + ones[pt] - 1};
			else op1 = {-1,-1};
			
			int rp = -1;
			lo = 0, hi = rgs.size() - 1;
			while(lo <= hi){
				int mid = (lo + hi)/2; // [L, algo]
				if(rgs[mid].first >= l){
					rp = mid;
					hi = mid - 1;
				}
				else lo = mid + 1;
			}
			if(rp == -1) op2 = {-1,-1};
			else{ 
				if(rgs[rp].first == l) op2 = { l , min(r, rgs[rp].second) };
				else{
					rp--;
					if(rp >= 0) op2 = { l, min(rgs[rp].second, r) };
					else op2 = {-1,-1};
				}
			}
			rp = rgs.size();
			lo = 0, hi = rgs.size() - 1;
			while(lo <= hi){
				int mid = (lo + hi)/2; // [R, algo]
				if(rgs[mid].first > r){
					rp = mid;
					hi = mid - 1;
				}
				else lo = mid + 1;
			}
			rp--;
			
			if(rp <= -1) op3 = {-1,-1};
			else op3 = { max(l, rgs[rp].first), min(r, rgs[rp].second) };
			
			if(op3.first > op3.second) op3 = {-1,-1};
			if(op2.first > op2.second) op2 = {-1,-1};
			
			
			
			int dif1 = op1.second - op1.first;
			int dif2 = op2.second - op2.first;
			int dif3 = op3.second - op3.first;
			
			cout << qq << " ";
			vector<pair<int,int>> rps;
			if(op2.first >= 0) rps.push_back(op2);
			if(op3.first >= 0) rps.push_back(op3);
			if(op1.first >= 0) rps.push_back(op1);
			
			sort(rps.begin(), rps.end(), cmp);
			cout << rps[0].first + 1 << " " << rps[0].second + 1 << endl;
		}
	}
}
int main() {
	int t, tc = 1;
	cin >> t;
	while(t--){
		cout << "Case " << tc++ << ":\n";
		solve();
	}
	return 0;
}
