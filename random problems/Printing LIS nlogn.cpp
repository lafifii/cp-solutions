const int maxn = 1e5 + 5;
int A[maxn], parent[maxn], dp[maxn];
int len = 1; // answer
void lis(int n) {
	dp[0] = -1, dp[1] = 0, parent[0] = -1;
	for (int i = 1; i < n; ++i) {
		int lo = 1, hi = len;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (A[dp[mid]] < A[i]) lo = mid+1;
			else hi = mid;
		}
		if (lo == len and A[dp[len]] < A[i]) len++, lo++;	
		dp[lo] = i; // guarda id final para cada tamaño
		parent[i] = dp[lo-1];
	}
}
void recover(){
	int k = dp[len];
	vector<int> ans(len);
	for(int i = len - 1; i >= 0; --i){
		ans[i] = A[k];
		k = parent[k];
	}
	for(int i = 0; i < len; ++i) cout << ans[i] << ' ';
	cout << endl;
}
