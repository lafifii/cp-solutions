#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 4;
int dp[maxn][maxn];
int a[maxn][maxn];
int ST[11][maxn][11][maxn];
int logs[maxn];
// hallar subcuadrado lleno de unos mas grande en el rango (x1,y1) (x2,y2)
void build(int n, int m){
	logs[0] = 1;
	for(int i = 2; i < maxn; ++i) logs[i] = logs[i/2] + 1;
	
	for (int ir = 0; ir < n; ir++) {
		for(int ic=0;ic<m;ic++)
	    	ST[ 0 ][ ir ][ 0 ][ ic ] = dp[ir][ic];
	      
	  	for(int jc=1;jc<=10;jc++) {
	  		for(int ic=0; ic+(1<<(jc)) <= m; ic++) {
	     		ST[0 ][ir ][jc ][ic ] = max(ST[0 ][ir ][jc-1 ][ic ],ST[0 ][ir ][ jc-1 ][ ic+ (1<<(jc-1)) ]);
	    	}
		}
	}       

	for (int jr = 1; jr <= 10; jr++) {
		for (int ir = 0; ir+(1<<(jr)) <= n; ir++) {
			for (int jc = 0; jc <= 10; jc++) {
				for (int ic = 0; ic < m; ic++) {
					ST[jr][ir][jc][ic] = max(ST[jr-1][ir][jc][ic],ST[jr-1][ir+(1<<(jr-1)) ][jc ][ic ])  ;
				}
			}
		}
	}
}
int query(int x1, int y1, int x2, int y2) {
	
	int lenx=x2-x1+1;
	int kx = logs[lenx];
	
    int leny=y2-y1+1;
    int ky = logs[leny];

    int max_R1 = max ( ST[kx ][x1 ][ky ][y1 ] , ST[kx ][x1 ][ky ][ y2+1- (1<<ky) ] );
  	int max_R2 = max ( ST[kx ][x2+1-(1<<kx) ][ky ][y1 ], ST[kx ][x2+1- (1<<kx) ][ky ][y2+1- (1<<ky) ] );
  	return max ( max_R1, max_R2 );
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) cin >> a[i][j];
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(!i or !j) dp[i][j] = a[i][j];
			else dp[i][j] = (a[i][j] ? a[i][j] + min({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]}) : 0);
		}
	}
	build(n,m);
	int t;
	cin >> t;
	while(t--) {
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1--; y1--; x2--; y2--;

		int lo = 0, hi = min(x2-x1+1, y2-y1+1), ans = 0;
		while (lo <= hi) {
			int mid = (lo+hi)/2;
			int qq = query(x1 + mid - 1, y1 + mid - 1, x2 , y2);
			if ( qq >= mid) ans = max(ans, mid), lo = mid + 1;
			else hi = mid - 1;
		}
		cout << ans << endl;
	}
	return 0;
}

