#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 40;
int bit[maxn][maxn], n, m;
bool a[maxn][maxn];

void update(int y, int x, int val){
	for( ; y <= n; y+= y&-y)
		for(int j = x; j <= m; j+= j&-j)
			bit[y][j]+= val;
		
}
int query(int y, int x){
	int sum = 0;
	for(; y > 0; y-= y&-y)
		for(int j = x; j > 0; j-= j&-j) sum+= bit[y][j];
	
	return sum;
}
int query_sq(int x1, int y1, int x2, int y2){
	int v1 = query(y2, x1 - 1);
	int v2 = query(y1 - 1, x2);
	int v3 = query(y1 - 1, x1 - 1);
	return query(y2, x2) - v1 - v2 + v3;
}
int main() {
	int t, q, x, y, x1, y1, x2, y2, tipo;
	scanf("%d", &t);

	n = m = maxn - 10;
	int tc = 1;
	while(t--){
		printf("Case %d:\n", tc++);
		memset(bit,0,sizeof(bit));
		memset(a,0,sizeof(a));
		
		scanf("%d", &q);
		while(q--){
			scanf("%d", &tipo);
			if(tipo){
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				x1++, y1++, x2++, y2++;
				printf("%d\n", query_sq(x1,y1,x2,y2));
			}
			else{
				scanf("%d%d", &x, &y);
				x++, y++;
				if(not a[y][x]) update(y,x,1);
				a[y][x] = 1;
			}
		}
	}
	return 0;
}
