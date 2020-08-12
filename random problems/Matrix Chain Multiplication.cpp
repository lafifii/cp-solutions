const int maxn = 100;
int A[maxn], dp[maxn][maxn];
int mchain(int n) 
{ 
    for (int i = 1; i < n; i++)  dp[i][i] = 0; 
    for (int len = 2; len < n; ++len) 
    { 
        for (int i = 1; i < n - len + 1; ++i) 
        { 
            int j = i + len - 1; 
            dp[i][j] = INT_MAX; 
            for (int k = i; k <= j - 1; ++k) 
            { 
                int cost = dp[i][k] + dp[k + 1][j] + A[i - 1] * A[k] * A[j]; 
                dp[i][j] = min(cost, dp[i][j]);
            } 
        } 
    }   
    return dp[1][n - 1]; 
} //O(n^3)
