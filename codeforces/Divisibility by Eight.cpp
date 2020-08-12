#include <bits/stdc++.h>
using namespace std;
const int maxn = 300;
int dp[maxn][10][2];
string a;
bool f(int pos, int modulo, bool tome){
	if(pos == a.size()) return ( modulo == 0 and tome );
	if(dp[pos][modulo][tome]!=-1) return dp[pos][modulo][tome];
	bool tomo = f(pos + 1, ( modulo*10 + ( a[pos]  - '0') ) % 8, 1);
	bool notomo = f(pos + 1, modulo, tome);
	return dp[pos][modulo][tome] = tomo | notomo;
}
void rec(int pos, int modulo, bool tome){
	if(pos == a.size()) return;
	bool tomo = f(pos + 1, ( modulo*10 + ( a[pos]  - '0') ) % 8, 1);
	bool notomo = f(pos + 1, modulo, tome);
	if(tomo){
		cout << a[pos];
		return rec(pos + 1, ( modulo*10 + ( a[pos]  - '0') ) % 8, 1);
	}
	rec(pos + 1, modulo, tome);
}
int main() {
	cin >> a;
	memset(dp,-1,sizeof(dp));
	if(f(0,0, 0)){ 
		puts("YES");
		rec(0,0, 0);
	}
	else puts("NO");
	return 0;
}
