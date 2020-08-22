#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int t[4*maxn];
pair<int,int> a[maxn];
void update(int v, int l, int r, int pos, int val){
    if(l == r) t[v] = val > 0 ? min(t[v] + 1, 1) : max(t[v]-1, 0);
    else{
        int mid = (l+r)/2;
        if(pos<=mid) update(2*v,l,mid,pos,val);
        else update(2*v+1,mid+1,r,pos,val);
        t[v] = t[2*v] + t[2*v+1];
    }
}
int kth(int v, int l, int r, int k){
    if(t[v] < k) return -1;
    if(l == r) return r;
    int mid = (l+r)/2;
    if(t[2*v] >= k) return kth(2*v,l,mid,k);
    return kth(2*v+1,mid+1,r,k-t[2*v]);
}
int sum(int v, int l, int r, int lo, int hi){
    if(lo > hi) return 0;
    if(lo == l and hi == r) return t[v];
    int mid = (l+r)/2;
    return sum(2*v,l,mid,lo,min(mid,hi)) + sum(2*v+1,mid+1,r,max(lo,mid+1), hi);
}
int main(){
    int q, id = 0;
    map<int,int> mp;
    map<int,int> rev;
    scanf("%d", &q);
    for(int i = 0; i < q; ++i){
        char c; int num;
        scanf(" %c%d", &c, &num);
        if(c == 'I') a[i] = {0,num};
        else if(c == 'D') a[i] = {1,num};
        else if(c == 'K') a[i] = {2,num};
        else a[i] = {3,num};
        
        if(a[i].first!=2) mp[num];
    }

    for(auto &x: mp){ x.second = id++;}
    for(auto x: mp) rev[x.second] = x.first;
    for(int i = 0; i < q; ++i) if(a[i].first != 2) a[i].second = mp[a[i].second];
    for(int i = 0; i < q; ++i){ 
        if(a[i].first == 0) update(1,0,id-1,a[i].second,1);
        else if(a[i].first == 1) update(1,0,id-1,a[i].second,-1);
        else if(a[i].first == 2){
            int ans = kth(1,0,id-1,a[i].second);
            if(ans == -1) puts("invalid");
            else printf("%d\n", rev[ans]);
        }
        else{
            printf("%d\n", sum(1,0,id-1,0,a[i].second-1));
        }
    }
    return 0;
}