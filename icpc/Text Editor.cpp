#include <bits/stdc++.h>
using namespace std;
const int p = 101;
const int mod = 1e9 + 9;
const int maxn = 1e7;
typedef long long ll;
int k, n;
map<char,int> mp;
ll p_pow[maxn], h[maxn];
void init(){
    memset(p_pow,0,sizeof(p_pow));
    p_pow[0] = 1;
    for (int i = 1; i < maxn; i++) p_pow[i] = (p_pow[i-1] * p) % mod;
}
int get(char c){
	return mp[c];
}
void computeh(string &s){
    memset(h,0,sizeof(h));
    for (int i = 0; i < n; i++){
        h[i+1] = (h[i] + get(s[i])*p_pow[i])%mod;
    }
}
ll sub_h(int lo, int hi){
    ll ans = (h[hi + 1] + mod - h[lo]) % mod;
    ans = (ans * p_pow[n - lo - 1]) % mod;
    return ans;
}
ll compute_sh(string &s){
   ll ans = 0;
   for (int i = 0; i < s.size(); i++){
      ans = (ans + get(s[i]) *p_pow[i])%mod;
   }
   return ans;
}
bool pred(string &s){
	int c = 0;
	ll subh = (compute_sh(s)*p_pow[n - 1])%mod;
	for(int i = 0; i + (int)s.size() - 1 < n; ++i){
		ll subnow = sub_h(i, i + s.size() - 1);
		c+=(subnow == subh);
	}
	return c >= k;
}
int main() {
	init();
	int ans = -1, id = 1;
	string s, t;
	getline(cin, s);
	getline(cin, t);
	cin >> k;
	for(char c: s) if(mp.count(c) == 0) mp[c] = id++;
	for(char c: t) if(mp.count(c) == 0) mp[c] = id++;
	cin >> s >> t >> k;
	n = s.size();
	computeh(s);
	int lo = 1, hi = t.size();
	while(lo <= hi){
		int mid = (lo + hi)/2;
		string sub = t.substr(0, mid);
		if(pred(sub)){
			ans = max(ans, mid);
			lo = mid + 1;
		}
		else hi = mid - 1;
	}
	if(ans == -1) puts("IMPOSSIBLE");
	else cout << t.substr(0, ans);
	return 0;
}
