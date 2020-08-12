#include <bits/stdc++.h>
using namespace std;
const int maxn = 60;
int dp[maxn][maxn][maxn][maxn], sum[maxn][maxn], n, m;
vector<string> M(maxn);
int suma(int x1, int y1, int x2, int y2){
	
	int val1 = (y1 - 1 >= 0 ? sum[y1 - 1][x2] : 0);
	int val2 = (x1 - 1 >= 0 ? sum[y2][x1 - 1] : 0);
	int val3 = (x1 - 1 >= 0 and y1 - 1 >= 0 ? sum[y1 - 1][x1 - 1] : 0);
	return ( sum[y2][x2] - val1 - val2 + val3) == 0 ;
}
void precal(){
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			int val1 = (i - 1 >= 0 ? sum[i - 1][j] : 0);
			int val2 = (j - 1 >= 0 ? sum[i][j - 1] : 0);
			int val3 = (i - 1 >= 0 and j - 1 >= 0 ? sum[i - 1][j - 1] : 0);
			sum[i][j] = ( M[i][j] == '1' ) + val1 + val2 - val3;
		}
	}
}
int f(int x1, int y1, int x2, int y2){
	if(x1 > x2 or y1 > y2) return 0;
	if(dp[x1][y1][x2][y2]!=-1) return dp[x1][y1][x2][y2];

	int ans = suma(x1,y1,x2,y2);

	int o1 = f(x1 + 1, y1    , x2    , y2    );
	int o2 = f(x1    , y1 + 1, x2    , y2    );
	int o3 = f(x1    , y1    , x2 - 1, y2    );
	int o4 = f(x1    , y1    , x2    , y2 - 1);
	
	int o12 = f(x1 + 1, y1 + 1, x2    , y2);
	int o13 = f(x1 + 1, y1 , x2 - 1, y2);
	int o14 = f(x1 + 1, y1 , x2 , y2 - 1);
	
	int o23 = f(x1 , y1 + 1, x2 - 1, y2);
	int o24 = f(x1 , y1 + 1, x2    , y2 - 1);
	
	int o34 = f(x1 , y1 , x2 - 1, y2 - 1);
	
	int o123 = f(x1+1 , y1+1, x2 - 1, y2);
	int o124 = f(x1+1 , y1+1, x2, y2 - 1);
	int o134 = f(x1+1 , y1 , x2 - 1, y2 - 1);
	
	int o234 = f(x1 , y1+1, x2-1, y2-1);
	
	int o1234 = f(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
	

	ans = ans + (o1 + o2 + o3 + o4) - (o12 + o13 + o14 + o23 + o24 + o34) + (o123 + o124 + o134 + o234) - o1234;
	
	
	return dp[x1][y1][x2][y2] = ans;
}
int main() {
	int q, x1, y1, x2, y2;
	cin >> n >> m >> q;
	for(int i = 0; i < n; ++i) cin >> M[i];
	precal();
	memset(dp,-1,sizeof(dp));
	while(q--){
		cin >> y1 >> x1 >> y2 >> x2;
		x1--,y1--,x2--,y2--;
		cout << f(x1,y1,x2,y2) << endl;
	}
	return 0;
}
// contar rectangulos llenos de zeros en el rango (x1,y1) a (x2,y2)
