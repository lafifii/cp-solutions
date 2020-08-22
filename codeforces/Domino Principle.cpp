#include <bits/stdc++.h>
using namespace std;
struct node{ long long x, h, id; };
const int maxn =  1e5;
int t[4*maxn];
node a[maxn];

void update(int v, int l, int r, int pos, int val){
    if(l == r) t[v] = val;
    else{
        int mid = (l + r)/2;
        if(pos<=mid) update(2*v,l,mid,pos,val);
        else update(2*v+1,mid+1,r,pos,val);
        t[v] = max(t[2*v], t[2*v+1]);
    }
}
int query(int v, int l, int r, int lo, int hi){
    if(lo > hi) return -1;
    if(lo == l and hi == r) return t[v];
    int mid = (l+r)/2;
    return max(query(2*v,l,mid,lo,min(mid,hi)) , query(2*v+1,mid+1,r,max(mid+1,lo),hi));
}
int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%lld%lld", &a[i].x, &a[i].h);
        a[i].id = i;
    }
    /*
    10 10
    16 5
    18 2
    20 5
    */
    sort(a, a + n, [](node a, node b){return a.x < b.x; });
    vector<long long> x(n);
    vector<int> dp(n, 0);
    for(int i = 0; i < n; ++i) x[i] = a[i].x;
    for(int i = n - 1; i >= 0; --i){
        if(i == n - 1) dp[i] = n - 1;
        else{
            int llega = max(upper_bound(x.begin(), x.end(), x[i] + a[i].h - 1LL) - x.begin() - 1, 0);
            if(x[llega] <= x[i] + a[i].h - 1LL and llega > i and llega < n){
                dp[i] = query(1,0,n-1,i, llega);
            }
            else dp[i] = i;
        }
        update(1,0,n-1,i,dp[i]);
    }

    for(int i = 0; i < n; ++i){ 
        int id = a[i].id;
        x[id] = dp[i] - i + 1;
    }
    
    for(int i = 0; i < n; ++i) printf("%d ", x[i]);
    
    return 0;
}