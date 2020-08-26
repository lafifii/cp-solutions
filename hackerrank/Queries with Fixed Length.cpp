#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 20;
int a[maxn];

void solve(int n, int len){
    int mn, i = 0;
    stack < pair<int,int> > s1, s2;
    for(; i < len; ++i){
        mn = s1.size() > 0 ? max(s1.top().second, a[i]) : a[i];
        s1.push({a[i], mn});
    }
    int ans = s1.top().second;
    for(; i < n; ++i){
        if(i < n){
            mn = s1.size() > 0 ? max(s1.top().second, a[i]) : a[i];
            s1.push({a[i], mn});
        }
        if(s2.empty()){
            while(s1.size() > 0){
                int el = s1.top().first;
                mn = s2.size() > 0 ? max(s2.top().second, el) : el;
                s1.pop();
                s2.push({el, mn});
            }
        }
        if(s2.size() > 0) s2.pop();
        int mx1 = s1.size() > 0  ? s1.top().second : INT_MIN;
        int mx2 = s2.size() > 0 ? s2.top().second : INT_MIN;
        ans = min(max(mx1,mx2), ans);
    }
    printf("%d\n", ans);
}

int main(){
    int n, q, num;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);  

    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &num);
        solve(n, num);
    }
    
    return 0;
}