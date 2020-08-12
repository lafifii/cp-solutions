#include <bits/stdc++.h>
using namespace std;
const int maxn = 600;
int a[maxn][maxn], n , m;
bool pred(int w, int c1, int r1, int r){
	if(c1 + w  > m or r1 + w > n) return false;
	return a[r1 + w - 1][c1 + w - 1] <= r;
}
int main(){
	int l,r,r1,c1,lo,hi,len,q;
	while(cin >> n >> m and n and m){
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j) cin >> a[i][j];
		
		cin >> q;
		while(q--){
			cin >> l >> r;
			len = 0;
			for(int i = 0; i < n; ++i){
				r1 = i, c1 = m;
				lo = 0, hi = m - 1;
				while(lo <= hi){
					int mid = (lo + hi)/2;
					if(a[i][mid] >= l){
						c1 = min(c1, mid);
						hi = mid - 1;
					}
					else lo = mid + 1;
				}
				if(c1 != m){
					// esquina derecha (r1, c1), buscar (r2, c2)
					lo = 1, hi = n;
					while(lo <= hi){
						int mid = (lo + hi)/2;
						if(pred(mid, c1, r1, r)){
							len = max(len , mid);
							lo = mid + 1;
						}
						else hi = mid - 1;
					}
				}	
			}
			cout << len << endl;
		}
		puts("-");
	}
	return 0;
}
