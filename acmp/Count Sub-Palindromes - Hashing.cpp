#include <bits/stdc++.h>
using namespace std;
const int nhash = 2, maxn = 2e5 + 20;
typedef long long ll;
 
int p[nhash] = {31,101}, n;
int mod[nhash] = {1000000009, 1000000007};
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
    return c - 'A' + 1;
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
bool solve(int len, int i){
    vector<ll> subf = sub_h(i, i + len - 1, 0);
    vector<ll> subr = sub_h(n - i - len, n - i - 1, 1);
    return (subf[0] == subr[0] and subf[1] == subr[1]);
}
string s;
int bs(int lo, int hi, int id){
    int ans = 0;
    while(lo <= hi){
        int mid = (lo + hi)/2;
        bool exists = solve(mid*2 + 1, id - mid);
        if(exists){ 
            ans = max(ans, mid*2 + 1);
            lo = mid + 1;
        }
        else hi = mid - 1;
    }
    return ans/2 + 1;
}
int main() {
    init();
 
    cin >> s;
    n = s.size();
    computeh(s, 0);
    reverse(s.begin(), s.end());
    computeh(s, 1);
    reverse(s.begin(), s.end());
    long long ans = 0;
    for(int i = 0; i < n; ++i){
        int len = min(i, n - 1 - i);
        ans+= bs(1, len, i);
    }
     
    string aux = "";
    aux+= s[0];
    for(int i = 1; i < n; ++i){
        aux+= " ";
        aux+= s[i];
    }
    n = aux.size();
    computeh(aux, 0);
    reverse(aux.begin(), aux.end());
    computeh(aux, 1);
    for(int i = 0; i < n; ++i){
        if(aux[i] != ' ') continue;
        int len = min(i, n - 1 - i);
        ans+= bs(1, len, i)/2;
    }
    cout << ans;
    return 0;
}
