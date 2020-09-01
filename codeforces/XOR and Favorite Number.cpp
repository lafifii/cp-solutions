#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int a[maxn], qsz, pre[maxn];
long long cnt[10000000];
struct query{ int l, r, id;};
bool cmp(const query &a, const query &b){
    if(a.l/qsz != b.l/qsz) return a.l < b.l;
    return (a.l/qsz &1 ) ? a.r < b.r : a.r > b.r;
}
long long sz = 0;
int k;
void add(int id){
    int preff = k^pre[id];
    sz+= cnt[preff];
    cnt[pre[id]]++;
}
void rem(int id){
    cnt[pre[id]]--;
    int preff = k^pre[id];
    sz-= cnt[preff];
}
int main(){
    int n, q;
    scanf("%d%d%d", &n, &q, &k);
    vector<query> qs(q);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 0; i < q; ++i){
        scanf("%d%d", &qs[i].l, &qs[i].r);
        qs[i].l--;
        qs[i].id = i;
    }
    
    pre[0] = 0;
    for(int i = 1; i <= n; ++i) pre[i] = a[i]^pre[i-1];

    qsz = sqrt(n) + 1;
    sort(qs.begin(), qs.end(), cmp);
    vector<long long> ans(q, 0);
    int lo = 1, hi = 0;
    for(query qq : qs){
        while (lo > qq.l) {
            lo--;
            add(lo);
        }
        while (hi < qq.r) {
            hi++;
            add(hi);
        }
        while (lo < qq.l) {
            rem(lo);
            lo++;
        }
        while (hi > qq.r) {
            rem(hi);
            hi--;
        }
        ans[qq.id] = sz;
    }
    for(long long x: ans) printf("%lld\n", x);
    return 0;
}