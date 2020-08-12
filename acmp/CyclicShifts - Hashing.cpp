#include <bits/stdc++.h>
using namespace std;
const int nhash = 2, maxn = 2e5 + 20;
typedef long long ll;

int p[nhash] = {31,101}, n;
int mod[nhash] = {1000000009, 1000000007};
ll p_pow[nhash][maxn], h[nhash][maxn];

void init(){
    memset(p_pow,0,sizeof(p_pow));
    for(int j = 0; j < nhash; ++j){
    	p_pow[j][0] = 1;
    	for(int i = 1; i < maxn; ++i)
    		p_pow[j][i] = (p_pow[j][i-1] * p[j]) % mod[j];
    }
}
int get(char c){
	return c - 32;
}
void computeh(string &s){
    memset(h,0,sizeof(h));
    for(int j = 0; j < nhash; ++j){
    	for (int i = 0; i < n; i++){
        	h[j][i+1] = (h[j][i] + get(s[i])*p_pow[j][i])%mod[j];
    	}
    }
}
vector<ll> sub_h(int lo, int hi){
   vector<ll> ans(nhash, 0);
   for(int i = 0; i < nhash; ++i){
    	ans[i] = ((h[i][hi + 1] + mod[i] - h[i][lo]) + mod[i]) % mod[i];
    	ans[i] = (ans[i] * p_pow[i][n - lo - 1]) % mod[i];
    }
    return ans;
}
string s;
bool cmp(int i, int j){
	int lo = 1, hi = n/2, len = INT_MAX; // len
	while(lo <= hi){
		int mid = ((long long)hi + lo)/2;
		vector<ll> hash_i = sub_h(i, i + mid - 1);
		vector<ll> hash_j = sub_h(j, j + mid - 1);
		if(hash_i[0] == hash_j[0] and hash_i[1] == hash_j[1]){
			lo = mid + 1;
		}
		else{
			len = min(len, mid);
			hi = mid - 1;
		}
	}
	if(len == INT_MAX) return false; // iguales
	return s[i + len - 1] < s[j + len - 1];  
}
int main() {
	init();
	cin >> s;
	s = s + s;
	n = s.size();
	computeh(s);
	vector<int> pos;
	for(int i = 0; i < n/2; ++i) pos.push_back(i);
	sort(pos.begin(), pos.end(), cmp);
	string ans = "";
	for(int x: pos) ans+= s[x + n/2 - 1];
	cout << ans;
	return 0;
}
