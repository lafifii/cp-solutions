#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 20;
const int mod = 1e9 + 7;

struct node{ 
    array<long long,4> m; 
    array<long long,4> a;
};

node a[maxn], neu;
array<long long,4> aux;

long long mul(long long a, long long b, long long c, long long d){
    return ( (a%mod * b%mod)%mod + (c%mod * d%mod)%mod )%mod;
}
long long tr(const array<long long,4> &am){
    return (am[0] + am[3])%mod;
}
array<long long,4> merge(const array<long long,4> &a, const array<long long,4> &b){
    aux[0] = mul(a[0],b[0],a[1],b[2]);
    aux[1] = mul(a[0],b[1],a[1],b[3]);
    aux[2] = mul(a[2],b[0],a[3],b[2]);
    aux[3] = mul(a[2],b[1],a[3],b[3]);
    return aux;
}
int n;
vector<node> rev(deque<node>&S){
    vector<node> cc;
    while(S.size() > 0){
        node tp = S.front();
        S.pop_front();
        if(cc.size() == 0){ 
            tp.m = tp.a;
            cc.push_back(tp);
        }
        else{ 
            tp.m = merge(cc.back().m, tp.a);
            cc.push_back(tp);
        }
    }
    return cc;
}
long long solve(int d){
    
    deque<node> S;
    vector<node> E;
    for(int i = n - d; i < n; ++i) S.push_back(a[i]);
    E = rev(S);
    long long ans = tr(E.back().m);
    
    node naux;
    for (int i = n - d - 1; i >= 0; i--)
    {
        if(E.size() == 0) E = rev(S);
        E.pop_back();

        if(S.size() == 0) S.push_back(a[i]);
        else{
            naux = a[i];
            naux.m = merge(a[i].a, S.front().m); 
            S.push_front(naux);
        }

        if( S.size() > 0 and E.size() > 0) ans = max(ans, tr(merge(S.front().m, E.back().m)));
        else if( S.size() ) ans = max(ans, tr(S.front().m));
        else ans = max(ans, tr(E.back().m));
    }
    
    return ans;
}
int main(){
    int q, d;
    scanf("%d%d", &n, &q);

    for(int i = 0; i < n; ++i){
        for (int j = 0; j < 4; ++j) scanf("%d", &aux[j]);
        a[i].m = aux;
        a[i].a = aux;
    }
    
    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &d);
        printf("%lld\n", solve(d));
    }
    
    return 0;
}