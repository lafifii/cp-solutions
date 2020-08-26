#include <bits/stdc++.h>
using namespace std;
struct qs{ int t, p, x; };
const int maxn = 1e5 + 20;
qs a[maxn];
int v[maxn];

int main(){
    int n, q;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &v[i]);
    scanf("%d", &q);
    for(int i = 0; i < q; ++i){ 
        scanf("%d", &a[i].t);
        if(a[i].t == 1){
            scanf("%d%d", &a[i].p, &a[i].x);
            a[i].p--;
        }
        else scanf("%d", &a[i].x);
    }
    int mx = 0;
    vector<int> ans(n, -1);
    for(int i = q - 1; i >= 0; --i){
        if(a[i].t == 1){ 
            if(ans[a[i].p] == -1) ans[a[i].p] = max(mx, a[i].x);
        }
        else mx = max(mx, a[i].x);
    }
    for(int i = 0; i < n; ++i){
        if(ans[i] == -1) printf("%d ", max(v[i], mx) );
        else printf("%d ", ans[i]);
    }
    return 0;
}