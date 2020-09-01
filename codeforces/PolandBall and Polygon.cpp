#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e6 + 20;
long long bit[maxn];
void add(int x){
    x++;
    for(; x < maxn; x+= x&-x ) bit[x]++;
}
long long sum(int x){
    x++;
    long long ans = 0;
    for(; x > 0; x-=x&-x) ans+=bit[x];
    return ans;
}
int main(){
    int n, k, last = 0;
    long long ans = 1;
    scanf("%d%d", &n, &k);
    k = min(k,n-k);
    for(int i = 0; i < n; ++i){
        last%= n;
        int nw = last + k;
        ans+= 1LL + sum(nw - 1) - sum(last);
        add(last), add(nw%n);
        add(last + n), add(nw%n + n);
        last = nw;
        printf("%lld ", ans);
    }

    return 0;
}
