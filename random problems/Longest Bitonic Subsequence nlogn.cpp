const int maxn = 1e5 + 5;
int A[maxn][2], parent[maxn][2], dp[maxn][2], best[maxn][2]; // best for every i
void lis(int n, int tipo) {
	int len = 1;
	dp[0][tipo] = -1, dp[1][tipo] = 0, parent[0][tipo] = -1, best[0][tipo] = 1;
	for (int i = 1; i < n; ++i) {
		int lo = 1, hi = len;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (A[dp[mid][tipo]][tipo] < A[i][tipo]) lo = mid+1;
			else hi = mid;
		}
		if (lo == len and A[dp[len][tipo]][tipo] < A[i][tipo]) len++, lo++;	
		dp[lo][tipo] = i; // guarda id final para cada tamaño
		parent[i][tipo] = dp[lo-1][tipo];
		best[i][tipo] = lo;
	}
}
vector<int> recover(int k, int tipo){
	int len = best[k][tipo];
	vector<int> ans;
	for(int i = 0; i < len; ++i){
		if(not (i == 0 and tipo == 0)) ans.push_back(A[k][tipo]);
		k = parent[k][tipo];
	}
	if(not tipo) reverse(ans.begin(), ans.end());
	return ans;
}
void bitonic(int n){
	lis(n, 0);
	lis(n, 1);
	int ans = 1, id = 0;
	for(int i = 0; i < n; ++i){
		if(ans < best[i][0] + best[n - i - 1][1] - 1)
			ans = best[i][0] + best[n - i - 1][1] - 1, id = i;
	}
	vector<int> l1 = recover(id, 0);
	vector<int> l2 = recover(n - id - 1, 1);
	l1.insert(l1.end(), l2.begin(), l2.end());
	cout << l1.size() << endl;
	for(int x: l1) cout << x << " ";
}
