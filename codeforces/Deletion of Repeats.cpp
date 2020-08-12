#include<bits/stdc++.h>
using namespace std;
const int nhash = 2, maxn = 2e6 + 20;
typedef unsigned long long ll;

int p[nhash] = {31,101}, n;
int mod[nhash] = {1000000009, 1000000007};
ll p_pow[nhash][maxn], h[nhash][maxn];
ll A[maxn];

void init(){
    memset(p_pow,0,sizeof(p_pow));
    for(int j = 0; j < nhash; ++j){
    	p_pow[j][0] = 1;
    	for(int i = 1; i < maxn; ++i)
    		p_pow[j][i] = (p_pow[j][i-1] * p[j]) % mod[j];
    }
}
void computeh(){
    memset(h,0,sizeof(h));
    for(int j = 0; j < nhash; ++j){
    	for (int i = 0; i < n; i++){
        	h[j][i+1] = (h[j][i] + (A[i]*p_pow[j][i])%mod[j])%mod[j];
    	}
    }
}
ll sub_h(int lo, int hi, int tipo){
    ll ans = ((h[tipo][hi + 1] + mod[tipo] - h[tipo][lo]) + mod[tipo]) % mod[tipo];
    ans = (ans * p_pow[tipo][n - lo - 1]) % mod[tipo];
    return ans;
}
vector<ll> hash_s(){
	vector<ll> ans(nhash, 0);
	for(int j = 0; j < nhash; ++j){
		for(int i = 0; i < n; ++i)
			ans[j] = (ans[j] + A[i]*p_pow[j][i])%mod[j];
	}
	return ans;
}
int main(){
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
	init();
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> A[i];
	computeh();
	map<ll, vector<int> > ids; // (numero, posiciones)
	for(int i = 0; i < n; ++i){
		ids[A[i]].push_back(i);
	}
	int ans = 0;
	for(int i = 0; i < n; ++i){
		if(i < ans) continue;
		auto next = upper_bound(ids[A[i]].begin(), ids[A[i]].end(), i );
		if(next == ids[A[i]].end()) continue;
		
		int id_next = *next;
		int len = id_next - i;
		if(id_next + len - 1 >= n) continue;
		
		ll sub_prev1 = sub_h(i, id_next - 1, 0);
		ll sub_now1 = sub_h(id_next, id_next + len - 1, 0);
			
		ll sub_prev2 = sub_h(i, id_next - 1, 1);
		ll sub_now2 = sub_h(id_next, id_next + len - 1, 1);
			
		if(sub_prev1 == sub_now1 and sub_prev2 == sub_now2){
			ans = id_next;
		}	
	}
	cout << n - ans << endl;
	for(int i = ans; i < n; ++i) cout << A[i] << " ";
	return 0;
}
