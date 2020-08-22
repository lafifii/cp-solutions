#include <bits/stdc++.h>

using namespace std;
const int maxn = 3e5 + 10;
long long bit[maxn];
int d[1000005], a[maxn], n;

void update(int x, int val){
    for(; x <= n; x+=x&-x) bit[x]+=val;
}
long long query(int x){
    long long s = 0;
    for(;x>0;x-=x&-x) s+= bit[x]; 
    return s;
}
void init(){
    for(int i = 1; i < 1000005 ;i++){
        for(int j = i; j < 1000005; j+= i) d[j]++;
    }
}
int main(){
    int m;
    scanf("%d%d", &n, &m);
    set<int> st;
    for(int i = 1; i <= n; ++i){ 
        scanf("%d", &a[i]);
        if(a[i] > 2) st.insert(i);
        update(i,a[i]);
    }
    init();
    for(int i = 0; i < m; ++i){
        int c, l, r;
        scanf("%d%d%d", &c, &l, &r);
        if(c == 1){
            set<int> aux;
            for(auto it = st.lower_bound(l); it != st.end() and *it <= r; ++it){
                int id = *it;
                update(id, -a[id]);
                a[id] = d[a[id]];
                update(id, a[id]);
                if(a[id] <= 2) aux.insert(id);
            }
            for(int x: aux) st.erase(x);
        }
        else{
            printf("%lld\n", query(r) - query(l - 1));
        } 
    }
    return 0;
}