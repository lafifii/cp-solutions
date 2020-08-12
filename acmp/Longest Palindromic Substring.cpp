#include <bits/stdc++.h>
using namespace std;
const int nhash = 2, maxn = 2e6 + 20;
typedef long long ll;

int p[nhash] = {31,101}, n;
int mod[nhash] = {1000000009, 1000000007};
int best, start;
ll p_pow[nhash][maxn], h[2][nhash][maxn];

void init(){
    memset(p_pow,0,sizeof(p_pow));
    memset(h,0,sizeof(h));
    for(int j = 0; j < nhash; ++j){
    	p_pow[j][0] = 1;
    	for(int i = 1; i < maxn; ++i)
    		p_pow[j][i] = (p_pow[j][i-1] * p[j]) % mod[j];
    }
}
int get(char c){
	return c - 'a' + 1;
}
void computeh(string &s, int id){
    for(int j = 0; j < nhash; ++j){
    	for (int i = 0; i < n; i++){
        	h[id][j][i+1] = (h[id][j][i] + get(s[i])*p_pow[j][i])%mod[j];
    	}
    }
}
vector<ll> sub_h(int lo, int hi, int id){
   vector<ll> ans(nhash, 0);
   for(int i = 0; i < nhash; ++i){
    	ans[i] = ((h[id][i][hi + 1] + mod[i] - h[id][i][lo]) + mod[i]) % mod[i];
    	ans[i] = (ans[i] * p_pow[i][n - lo - 1]) % mod[i];
    }
    return ans;
}
bool solve(int len){
	bool ok = 0;
	for(int i = 0; i + len - 1 < n; ++i){
		vector<ll> subf = sub_h(i, i + len - 1, 0);
		vector<ll> subr = sub_h(n - i - len, n - i - 1, 1);
		if(subf[0] == subr[0] and subf[1] == subr[1]){
			ok = 1;
			if(len > best) best = len, start = i;
		}
	}
	return ok;
}
void bs(int parity){
	int lo = 1, hi = n;
	if(lo%2 != parity) lo++;
	if(hi%2 != parity) hi--;
	while(lo <= hi){
		int mid = (lo + hi)/2;
		if(mid%2 != parity) mid++;
		if(mid > hi) break;
		bool exists = solve(mid);
		if(exists) lo = mid + 2;
		else hi = mid - 2;
	}
	
}
int main() {
	init();
	best = 1, start = 0;
	string s;
	cin >> s;
	n = s.size();
	computeh(s, 0);
	reverse(s.begin(), s.end());
	computeh(s, 1);
	
	for(int i = 0; i < 2; ++i) bs(i);
	
	reverse(s.begin(), s.end());
	cout << s.substr(start, best);
	return 0;
}
