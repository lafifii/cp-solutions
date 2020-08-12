#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 30;
int ST[maxn][40], a[maxn];
long long dp[maxn];
/*
  ai es puedo comprar tickets de i a [i + 1, a[i]]
  quiero llegar de i todos los j , i < j con el minimo numero de tickets
  
  dp[i] = cuanto cuesta llegar a n , siempre seria n - i - 1 pero
  si yo entre [i, a[i]] puedo llegar a un i mayor a a[i] entonces deberia
  ir a ese porque ese al menos me dara un ticket menos
  entonces la distancia es
  dp[i] = (n - 1 - i) - (a[i] - mayor) + dp[mayor]
  
  valor_mayor = get_max(i, a[i]) y luego buscas su indice con binary search
  indice = mayor
  
*/
void build(int n){ 
	for(int i = 0; i < n; i++) ST[i][0] = a[i];
	for(int j = 1; (1 << j) <= n; ++j) 
		for(int i = 0; i + ( 1<< j) <= n; ++i){
			ST[i][j] = max(ST[i][j - 1], ST[i + (1 << (j - 1) ) ][j - 1]);
		}
}
int query(int L, int R){ //[L, R]
	int ans = a[L], T =  R - L + 1;
	int lg = 31 - (__builtin_clz(T));
	for(int j = lg; j >= 0; --j){
		if( (1<<j) <= T){
			ans = max(ans, ST[L][j]);
			L+= ( 1 << j );
			T-= ( 1 << j );
		}
	}
	return ans;
}
int main() {
	int n;
	long long ans = 0;
	cin >> n;
	for(int i = 0; i < n - 1; ++i){
		cin >> a[i]; 
		a[i]--;
	}
	a[n - 1] = n - 1;
	build(n);
	dp[n - 1] = 0;
	for(int i = n - 2; i >= 0; --i){
		// FFFFFFVVVVV
		int mayor = query(i, a[i]);
		int lo = i + 1, hi = a[i], m = hi;
		while(lo <= hi){
			int mid = (lo + hi)/2;
			int qq = query(i + 1, mid);
			if(qq >= mayor) m = min(m, mid), hi = mid - 1;
			else lo = mid + 1;
		}
		dp[i] = (n - i - 1) -  (a[i] - m) + dp[m];
		
		ans+= dp[i];
	}
	cout << ans << endl;
	return 0;
}
