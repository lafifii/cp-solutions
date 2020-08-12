#include <bits/stdc++.h>
using namespace std;
const int nhash = 2, maxn = 2e6 + 20;
typedef long long ll;

int p[nhash] = {31,101};
int mod[nhash] = {1000000009, 1000000007};
ll p_pow[nhash][maxn], h[5][nhash][maxn];

void init(){
    memset(h,0,sizeof(h));
    memset(p_pow,0,sizeof(p_pow));
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
	int n = s.size();
	for(int j = 0; j < nhash; ++j){
    	for (int i = 0; i < n; i++){
        	h[id][j][i+1] = (h[id][j][i] + get(s[i])*p_pow[j][i])%mod[j];
    	}
    }
}
vector<string> A(5);
int orden[3] = {0,1,2};

vector<ll> sub_h(int lo, int hi, int id){
	vector<ll> ans(nhash, 0);
	int n = A[id].size();
	for(int i = 0; i < nhash; ++i){
    	ans[i] = ((h[id][i][hi + 1] + mod[i] - h[id][i][lo]) + mod[i]) % mod[i];
    	ans[i] = (ans[i] * p_pow[i][n - lo - 1]) % mod[i];
	}
    return ans;
}
vector<ll> hash_s(string &s){
	vector<ll> ans(nhash, 0);
	for(int j = 0; j < nhash; ++j){
		for(int i = 0; i < s.size(); ++i)
			ans[j] = (ans[j] + (get(s[i])*p_pow[j][i])%mod[j])%mod[j];
	}
	return ans;
}
string check(int i, int j){
	// matchear pref i con suf j o substring
	int leni = A[i].size();
	int lenj = A[j].size();
	vector<ll> sub_j, sub_i;
	if(lenj <= leni){ // substring
		sub_j = sub_h(0, lenj - 1, j);
		
		if(lenj < leni)
			for(int ii = 0; ii < nhash; ++ii) 
				sub_j[ii] = (sub_j[ii]*p_pow[ii][leni - lenj])%mod[ii];
		
		for(int lo = 0; lo + lenj - 1 < leni; ++lo){
			sub_i = sub_h(lo, lo + lenj - 1, i);
			if(sub_i[0] == sub_j[0] and sub_i[1] == sub_j[1]){
				return A[i];
			}
		}
	}
	sub_j.clear();
	sub_i.clear();
	int id_best = 0;
	for(int ii = 1; ii <= lenj and leni - ii >= 0; ++ii){
		int lo_j = 0, hi_j = ii - 1;
		int lo_i = leni - ii, hi_i = leni - 1;
		sub_j = sub_h(lo_j, hi_j, j);
		sub_i = sub_h(lo_i, hi_i, i);

		for(int jj = 0; jj < nhash; ++jj){
			if(lenj < leni) sub_j[jj] = (sub_j[jj]*p_pow[jj][abs(lenj - leni)])%mod[jj];
			else sub_i[jj] = (sub_i[jj]*p_pow[jj][abs(lenj - leni)])%mod[jj];
		}
		
		if(sub_i[0] == sub_j[0] and sub_i[1] == sub_j[1]){
			id_best = ii;
		}
	}
	return A[i] + A[j].substr(id_best);
}
int main() {
	ll best = LLONG_MAX;
	init();
	for(int i = 0; i < 3; ++i){ 
		cin >> A[i];
		computeh(A[i], i);
	}
	do{
		A[3] = check(orden[0], orden[1]);
		ll best_len = A[3].size();
		computeh(A[3], 3);
		best_len = check(3, orden[2]).size();
		best = min(best, best_len);
	}while(next_permutation(orden, orden + 3));

	cout << best << endl;
	return 0;
}
