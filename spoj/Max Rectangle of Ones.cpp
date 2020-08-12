typedef long long ll;
const int maxn = 300;
ll best[maxn], M[maxn][maxn];
ll solve(int n, vector<int>&A){ 
// Largest Rectangle on Histogram
	ll ans = 0;
	stack<ll> s;
	for(int i = 0; i < n; ++i){
		ll num = A[i], id = i; 
		while(not s.empty() and A[s.top()] >= num) s.pop();
		id = (s.empty() ? 0 : s.top() + 1);
		s.push(i);
		best[i] = num* (i - id + 1);
	}
	while(not s.empty()) s.pop();
	for(int i = n - 1; i >= 0; --i){
		ll num = A[i], id = i; 
		while(not s.empty() and A[s.top()] >= num) s.pop();
		id = (s.empty() ? n - 1 : s.top() - 1);
		s.push(i);
		best[i] = best[i] + (num* (id - i + 1)) - num;
		ans = max(best[i], ans);
	}
	return ans;
}
ll recm(int n, int m){
	ll ans = 0;
	vector<int> A(m, 0);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j< m; ++j) A[j] = (M[i][j] == 0 ? 0 : A[j] + 1);
		ans = max(ans, solve(m, A));
	}
	return ans;
}
