#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 20;
int a[maxn], qsz;
unordered_map<int, int> cnt;
struct query{ int l, r, id;};
bool cmp(const query &a, const query &b){
    if(a.l/qsz != b.l/qsz) return a.l < b.l;
    return (a.l/qsz &1 ) ? a.r < b.r : a.r > b.r;
}
int sz = 0;
void add(int id){
    cnt[a[id]]++;
    int val = cnt[a[id]];
    if(val == a[id]) sz++;
    else if(val - 1 == a[id]) sz--;
}
void rem(int id){
    cnt[a[id]]--;
    int val = cnt[a[id]];
    if(val == a[id]) sz++;
    else if(val + 1 == a[id]) sz--;
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
    vector<int> ans(q, 0);
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
    for(int x: ans) printf("%d\n", x);
    return 0;
}