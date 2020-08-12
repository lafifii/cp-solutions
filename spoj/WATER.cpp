#include <bits/stdc++.h>
using namespace std;
const int maxn = 300;
int a[maxn][maxn], dis[maxn][maxn];
bool vis[maxn][maxn];

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,-1,1};
/* 
  maximo volumen que se recolectara en el techo de una torre luego de llover
  techo es n*m y cada Aij es la altura de ese bloque
*/
int main() {
	int t;
	cin >> t;
	while(t--){
		int n, m, ans = 0;
		cin >> n >> m;
		set< pair<int, pair<int,int> > > st;
		memset(vis,0,sizeof(vis));
		for(int i = 0; i < n; ++i){ 
			for(int j = 0; j < m; ++j){ 
				cin >> a[i][j];
				if(i == 0 or i == n - 1 or j == 0 or j == m - 1){
					st.insert({a[i][j], {i,j} });
					dis[i][j] = a[i][j];
					vis[i][j] = 1;
				}
				else dis[i][j] = 1e9;
			}
		}
		
		while(st.size() > 0){
			auto x = *st.begin();
			st.erase(st.begin());
			for(int i = 0; i < 4; ++i){
				int ii = x.second.first + dy[i];
				int jj = x.second.second + dx[i];
				
				if(ii < 0 or ii >= n) continue;
				if(jj < 0 or jj >= m) continue;
				if(vis[ii][jj]) continue;
				
				vis[ii][jj] = 1;
				if(dis[ii][jj] > dis[x.second.first][x.second.second]){
					if(a[ii][jj] > dis[x.second.first][x.second.second]) dis[ii][jj] = a[ii][jj];
					else dis[ii][jj] = dis[x.second.first][x.second.second];
					st.insert({ dis[ii][jj] , { ii, jj }});
				}
			}
		}
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j)
				ans+= max(0, dis[i][j] - a[i][j]);
		}
		cout << ans << endl;
	}
	return 0;
}
