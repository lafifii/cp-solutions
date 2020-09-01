#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 20;
int a[maxn], qsz;
int cnt[1000006];
struct query{ int l, r, id;};
bool cmp(const query &a, const query &b){
    if(a.l/qsz != b.l/qsz) return a.l < b.l;
    return (a.l/qsz &1 ) ? a.r < b.r : a.r > b.r;
}
long long sz = 0;
void add(int id){
    long long val = cnt[a[id]];
    cnt[a[id]]++;
    sz-= (val*val*a[id]);
    val++;
    sz+= (val*val*a[id]);
}
void rem(int id){
    long long val = cnt[a[id]];
    cnt[a[id]]--;
    sz-= (val*val*a[id]);
    val--;
    sz+= (val*val*a[id]);
}
int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    vector<query> qs(q);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for(int i = 0; i < q; ++i){
        scanf("%d%d", &qs[i].l, &qs[i].r);
        qs[i].l--;
        qs[i].r--;
        qs[i].id = i;
    }
    qsz = sqrt(n) + 1;
    sort(qs.begin(), qs.end(), cmp);
    vector<long long> ans(q, 0LL);
    int lo = 0, hi = -1;
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
    for(long long x: ans) printf("%I64d\n", x);
    return 0;
}