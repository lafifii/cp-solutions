#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 20;
map<int,int>mp[maxn];
int main(){
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);  
    for(int i = 0; i < m; ++i){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--, v--;
        auto it = mp[u].lower_bound(w);
        int x = 1;
        if(it!=mp[u].begin()){
            it--;
            x = it->second + 1;
        }
        auto it2 = mp[v].upper_bound(w);
        if(it2!=mp[v].begin()){ 
            it2--;
            if(it2->second > x) continue;
        }
        mp[v][w] = max(mp[v][w], x);
        ans = max(ans, x);
        it2 = mp[v].find(w);
        it2++;
        vector<int> aux;
        for(;it2!=mp[v].end(); it2++){
            if(it2->second > x) break;
            aux.emplace_back(it2->first);
        }
        for (int y: aux) mp[v].erase(y);
        
    }
    printf("%d", ans);
    return 0;
} 