#include <bits/stdc++.h>
using namespace std;
const int maxn = (1 << 14);
// c0ntar connected comp de 1s en matriz
int a[maxn], p[maxn*2 + 10];
int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}
bool merge(int c, int b){
	c = find(c), find(b);
	if(c != b){
		p[c] = b;
		return 1;
	}
	return 0;
}
char s[maxn];
int main() {
	int n, m, ans = 0;
	memset(p,-1,sizeof(p));
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i){
		scanf("%s", &s);
		int id = 0;
		for(int j = 0; j < m/4; ++j){
			int x = s[j] >= '0' and s[j] <= '9' ? s[j] - '0' : s[j] - 'A' + 10;
			for(int k = 0; k < 4; ++k, ++id){
				a[id] = x&( 1<<(3 - k) );
				if(a[id]) p[id + m] = id + m;
				else p[id + m] = -1;
			}
		}
		
		for(int j = 0; j < m; ++j){
			if(a[j]){
				ans++;
				if(p[j] != -1) ans-=merge(j, j + m);
				if(j < m - 1 and a[j + 1]) ans-= merge(j + m, j + m + 1);
			}
		}
		for(int j = m; j < 2*m; ++j){
			if(p[j] != -1) p[j - m] = find(j) - m;
			else p[j - m] = -1;
		}
	}
	printf("%d", ans);
	return 0;
}
