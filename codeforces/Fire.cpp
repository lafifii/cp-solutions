#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 5;
int h, w;
int dx[4] = {0,0,1,-1};
int dy[4] = {-1,1,0,0};

void bfs(queue<pair<int,int> >&Q, vector<string>&M, map<pair<int,int> , int >& dis){
	while(!Q.empty()){
		pair<int,int> x = Q.front();
		Q.pop();
		int disx = dis[x];
		for(int i = 0; i < 4; ++i){
			int nx = x.second + dx[i], ny = x.first + dy[i];
			if(nx < 0 or ny < 0) continue;
			if(nx >= w or ny >= h) continue;
			if(dis.find({ny, nx}) == dis.end() and M[ny][nx] == '.'){
				int puede = 1;
				if(M[x.first][x.second] == '@'){
					for(int j = 0; j < 4; ++j){
						int nnx = nx + dx[j], nny = ny + dy[j];
						if(nnx < 0 or nny < 0) continue;
						if(nny >= w or nny >= h) continue;
						if(M[nny][nnx] != '*') continue;
						if(dis[{nny, nnx}] + 1 == disx + 1) puede = 0;
					}
				}
				if(!puede) continue;
				M[ny][nx] = M[x.first][x.second];
				dis[{ny, nx}] = disx + 1;
				Q.push({ny, nx});
			}
		}
	}
}
int main() {
	int t;
	cin >> t;
	while(t--){
		map<pair<int,int> , int > dis;
		cin >> w >> h;
		vector<string> M(h);
		queue<pair<int, int> > Q;
		for(int i = 0; i < h; ++i){ 
			cin >> M[i];
			for(int j = 0; j < w; ++j)
				if(M[i][j] == '@' or M[i][j] == '*'){ 
					Q.push({i, j});
					dis[{i, j}] = 0;
				}
		}
		bfs(Q, M, dis);
		int ans = INT_MAX;
		for(int i = 0; i < w; ++i){
			if(M[0][i] == '@') ans = min(ans, dis[{0,i}]);
			if(M[h - 1][i] == '@') ans = min(ans, dis[{h - 1,i}]);
		}
		for(int i = 0; i < h; ++i){
			if(M[i][0] == '@') ans = min(ans, dis[{i, 0}]);
			if(M[i][w - 1] == '@') ans = min(ans, dis[{i, w - 1}]);
		}
		if(ans == INT_MAX) cout << "IMPOSSIBLE\n";
		else cout << ans + 1 << endl;
	}

	return 0;
}
