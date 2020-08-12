#include <bits/stdc++.h>
using namespace std;
const int p = 31;
const int mod = 1e9 + 9;
const int maxn = 1e7;
typedef long long ll;
ll p_pow[maxn], h[maxn];
void init(){
    memset(p_pow,0,sizeof(p_pow));
    p_pow[0] = 1;
    for (int i = 1; i < maxn; i++) p_pow[i] = (p_pow[i-1] * p) % mod;
}
void computeh(string &s){
    memset(h,0,sizeof(h));
    int n = s.size();
    for (int i = 0; i < n; i++){
        h[i+1] = (h[i] + (s[i] - 'a' + 1) *p_pow[i])%mod;
    }
}
ll sub_h(int lo, int hi, int n){
    ll ans = (h[hi + 1] + mod - h[lo]) % mod;
    ans = (ans * p_pow[n - lo - 1]) % mod;
    return ans;
}
ll compute_sh(string &s){
   ll ans = 0;
   for (int i = 0; i < s.size(); i++){
      ans = (ans + (s[i] - 'a' + 1) *p_pow[i])%mod;
   }
   return ans;
}
void solve(string &pat, string &s){
   computeh(s);
   int l = pat.size();
   int id = s.size() - pat.size();
   ll hash_pat = (compute_sh(pat)*p_pow[s.size() - 1])%mod;
   for(int i = 0; i + l - 1 < (int)s.size(); ++i){
	int hi = i + l - 1;
	ll hash_now = sub_h(i, hi, s.size());
	if(hash_now == hash_pat) cout << i << endl;
   }
   cout << endl;
}
int main() {
	init();
	int n;
	string s, t;
	while(cin >> n){
		cin >> s >> t;
		solve(s,t);
	}
	return 0;
}
