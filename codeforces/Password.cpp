#include <bits/stdc++.h>
using namespace std;
const int p = 31;
const int mod = 1e9 + 9;
const int maxn = 1e6 + 10;
typedef long long ll;
ll p_pow[maxn], h[maxn];
int n;
void init(){
    memset(h,0,sizeof(h));
    memset(p_pow,0,sizeof(p_pow));
    p_pow[0] = 1;
    for (int i = 1; i < maxn; i++) p_pow[i] = (p_pow[i-1] * p) % mod;
}
void computeh(string &s){
    for (int i = 0; i < n; i++)
        h[i+1] = (h[i] + (s[i] - 'a' + 1)*p_pow[i])%mod;
}
ll sub_h(int lo, int hi){
    ll ans = (h[hi + 1] + mod - h[lo]) % mod;
    ans = (ans * p_pow[n - lo - 1]) % mod;
    return ans;
}
vector<int> posibles;
bool pred(int mid){
	mid = posibles[mid];
	for(int i = 1; i + mid - 1 < n - 1; ++i){
		ll subh = sub_h(i, i + mid - 1);
		if(subh == sub_h(0, mid - 1)) return true;
	}
	return false;
}
int main() {
	init();
	string s; 
	cin >> s;
	n = s.size();
	computeh(s);
	int lo = 0, hi = n - 1;
	while(lo < n and hi >= 0){
		ll subpre = sub_h(0, lo);
		ll subsuf = sub_h(hi, n - 1);
		if(subpre == subsuf) posibles.push_back(lo + 1);
		++lo, --hi;
	}
	if(posibles.size() == 0){
		puts("Just a legend");
		return 0;
	}
	int ans = -1;
	lo = 0, hi = posibles.size() - 1;
	while(lo <= hi){
		int mid = (hi + lo)/2;
		if(pred(mid)){ 
			ans = max(ans, posibles[mid]);
			lo = mid + 1;
		}
		else hi = mid - 1;
	}
	if(ans == -1){
		puts("Just a legend");
		return 0;
	} 
	cout << s.substr(0, ans);
	return 0;
}
