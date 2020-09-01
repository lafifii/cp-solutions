#include <bits/stdc++.h>
using namespace std;
const int maxn = 800;
const int lim = 500000 + 3;
int mp[maxn][maxn];
int a[lim];

int main(){
    int q, sq;
    scanf("%d", &q);
    sq = sqrt(q) + 1;
    while(q--){
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if(t == 1){
            a[x]+= y;
            for(int j = 1; j <= sq; ++j) mp[x%j][j]+= y;
        }
        else{
            if(x < sq){
                printf("%d\n", mp[y][x]);
            }
            else{
                int ans = 0;
                for(int j = y; j < lim; j+=x) ans+= a[j];
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}