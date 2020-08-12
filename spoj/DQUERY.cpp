#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 40;
/*
  Problema: Cuantos numeros unicos hay entre [L, R]
  Solucion: BIT con respuestas Offline. Vamos de i = 0 a n,
  y en el bit mantenemos si para una posicion i hay un elemento
  que es unico entre [0, i] si tienes 1 1 2 por ejemplo
  cuando i = 0 -> arreglo 1 0 0 
  cuando i = 1 -> arreglo 0 1 0 , cosa que podemos responder para 
  todas las queries con R = i cuantos unicos hay a su derecha 
*/
int bit[maxn], last[maxn], ans[maxn], n;
vector<pair<int,int>> lad[maxn];

void update(int x, int val){
	for(; x <= n; x+=x&-x) bit[x]+= val;
}
int query(int x){
	int sum = 0;
	for(; x > 0; x-=x&-x) sum+= bit[x];
	return sum;
}
int main() {
	
	memset(last,0,sizeof(last));
	memset(bit, 0, sizeof(bit));

	cin >> n;
	
	vector<int> a(n + 1);
	for(int i = 1; i <= n; ++i) cin >> a[i];
	
	int q, l, r; 
	cin >> q;
	for(int i = 0; i < q; ++i){
		cin >> l >> r;
		lad[r].push_back({l, i});
	}

	for(int i = 1; i <= n; ++i){
		if(last[a[i]]) update(last[a[i]], -1);
		last[a[i]] = i;
		update(i, 1);
		for(auto x: lad[i]) ans[x.second] = query(i) - query(x.first - 1);
	}
	for(int i = 0; i < q; ++i) cout << ans[i] << endl;
	
	return 0;
}
