int n;
vector<int> dgs;
typedef long long ll;
ll dp[10][300][2];
// position, unique sum for pos, is limited
ll f(int pos, int sum, bool oki){
	if(pos == n) return sum;
	if(dp[pos][sum][oki] != -1) return dp[pos][sum][oki];
	ll ans = 0;
	int limite = (oki ? 9 : dgs[pos]);
	for(int num = 0; num <= limite; ++num){
		bool oki2 = oki;
		if(not oki and num != limite) oki2 = 1;
		ans+= f(pos + 1, sum + num, oki2);
	}
	return dp[pos][sum][oki] = ans;
}
void convert(int num){
	dgs.clear();
	while(num){
		dgs.push_back(num%10);
		num/=10;
	}
	reverse(dgs.begin(), dgs.end());
	n = dgs.size();
}
// solution is solve(b) - solve(a - 1) = O(digits*max_sum*bool)
