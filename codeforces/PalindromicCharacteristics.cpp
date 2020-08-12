#include <bits/stdc++.h>
using namespace std;
const int p = 31;
const int mod = 1e9 + 9;
const int maxn = 5e3 + 10;
typedef long long ll;
ll p_pow[maxn], h[2][maxn];
int n;
void init(){
    memset(p_pow,0,sizeof(p_pow));
    p_pow[0] = 1;
    memset(h,0,sizeof(h));
    for (int i = 1; i < maxn; i++) p_pow[i] = (p_pow[i-1] * p) % mod;
}
void computeh(string &s, int tipo){
    for (int i = 0; i < n; i++){
        h[tipo][i+1] = (h[tipo][i] + (s[i] - 'a' + 1) *p_pow[i])%mod;
    }
}
ll sub_h(int lo, int hi, int tipo){
    ll ans = (h[tipo][hi + 1] + mod - h[tipo][lo]) % mod;
    ans = (ans * p_pow[n - lo - 1]) % mod;
    return ans;
}
ll dp[maxn][maxn];
int main(){
	init();
	string s;
	cin >> s;
	n = s.size();
	computeh(s, 0);
	reverse(s.begin(), s.end());
	computeh(s, 1);
	vector<ll> ans(n + 1, 0);
	memset(dp,0,sizeof(dp));
	ans[1] = n;
	for(int i = 0; i <= n; ++i) dp[i][i] = 1;
	for(int i = 0; i < s.size(); ++i){
		for(int len = 2; i + len - 1 < n; ++len){
			int hi = i + len - 1;
			ll sub1 = sub_h(i, hi, 0);
			ll sub2 = sub_h(n - 1 - hi, n - i - 1,1);
			if(sub1 == sub2){
				dp[i][hi] =  dp[i][(i + hi - 1)/2] + 1;
				for(ll k = dp[i][hi]; k >= 0; --k) ans[k]++;
			}
		}
	}
  for(int i = 1; i <= n; ++i) cout << ans[i] << " ";
	return 0;
}
// for k > 2 -> ans[k] = number of substrings that their halves are equal and each half is (k - 1) palindrommic
// for k = 1 -> number of palindromic strings
