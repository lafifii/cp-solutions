const int maxn = 1e4 + 5;
int valores[10] = {0,2,5,5,4,5,6,3,7,6};
int dp[maxn];
vector<int> A;
int f(int k){
	if(k < 0) return INT_MIN;
	if(k == 0) return 0;
	if(dp[k] != -1) return dp[k];
	int best = INT_MIN;
	for(int num: A){
		int now = f(k - valores[num]);
		if(now != INT_MIN) now++;
		best = max(now, best);
	}
	return dp[k] = best;
}
void rec(int k){
	if(k <= 0) return;
	int ans = f(k), digit = 0;
	for(int num : A){
		if(f(k - valores[num]) + 1 == ans){
			digit = max(num, digit);
		}
	}
	cout << digit;
	rec(k - valores[digit]);
}
int main() {
	int n, k, num;
	cin >> k >> n;
	memset(dp,-1,sizeof(dp));
	for(int i = 0; i < n; ++i){ 
		cin >> num;
		A.push_back(num);
	}
	rec(k);
	return 0;
}
