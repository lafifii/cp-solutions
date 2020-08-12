const int maxn = 1e3 + 5;
int n,m, dp[maxn][maxn];
string a, b;
int f(int i, int j){
	if(i == n or j == m) return 0;
	if(dp[i][j] != -1) return dp[i][j];
	if(a[i] == b[j]) dp[i][j] = 1 + f(i + 1, j + 1);
	else dp[i][j] = max(f(i + 1,j) , f(i, j + 1) );
	return dp[i][j];
}
vector<string> recover(int i, int j){
	if(i == n or j == m){ 
		vector<string> v(1);
		return v;
	}
	if(a[i] == b[j]){
		vector<string> uno = recover(i + 1, j + 1);
		for(string &s : uno) s+= a[i];
		return uno;
	}
	if(dp[i + 1][j] > dp[i][j + 1]) return recover(i + 1, j);
	if(dp[i][j + 1] > dp[i + 1][j]) return recover(i, j + 1);
	vector<string> dos = recover(i + 1, j);
	vector<string> tres = recover(i, j + 1);
	dos.insert(dos.end(), tres.begin(), tres.end());
	return dos;
}
