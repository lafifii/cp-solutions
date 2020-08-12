const int maxn = 1e3 + 5;
bool dp[maxn][maxn];
string a;
int n;
string f(){
  int best = 1, inicio = 0;
	dp[0][0] = 1;
	for(int i = 1; i < n; ++i){ 
		dp[i][i] = 1;
		if(a[i] == a[i - 1]) dp[i - 1][i] = 1, best = 2, inicio = i - 1;
	}
	
	for(int len = 3; len <= n; ++len){
		for(int i = 0; i < n - len + 1; ++i){
			int j = i + len - 1;
			if(dp[i + 1][j - 1] and a[i] == a[j]){
				dp[i][j] = 1;
				if(len > best){
					best = len;
					inicio = i;
				}
			}
		}
	}
  return a.substr(inicio, best);
}
