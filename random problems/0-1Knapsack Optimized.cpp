// dp[w] = max value for exact weigth
const int maxn = 2e4 + 300, maxw = 500;
int val[maxn], w[maxn], dp[maxw], n;
int knapsack(int v){
	memset(dp,0,sizeof(dp));
	for (int i = 0; i < n; ++i){
        	for (int j = v; j >= w[i]; --j) 
        	{
 	           	if (dp[j - w[i]] > 0 || j == w[i])
         		       	dp[j] = max(dp[j], dp[j - w[i]] + val[i]);
        	}
	}
	return dp[v];
}
