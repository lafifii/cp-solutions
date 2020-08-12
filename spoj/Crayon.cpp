#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e6 + 10;
/*
  queries. 1. agregar linea [l,r], 2. borrar iesima linea agregada
           3. cuantas lineas que al menos tengna un punto entre [l,r] hay
*/

long long bit[2][maxn]; // derecha izquierda
int id;

void update(int v, int x, int val){
	for(; x <= id; x+= x&-x) bit[v][x]+= val;
}
long long query(int v, int x){
	long long sum = 0;
	for(; x > 0; x-=x&-x) sum+= bit[v][x];
	return sum;
}
struct qr{
	int t, l, r;
};

int main() {
	int n;
	scanf("%d", &n);
	vector<qr> a(n);
	char c;
	map<int,int> mp;
	vector< pair<int,int> > add; 
	for(int i = 0; i < n; ++i){ 
		scanf(" %c", &c);
		if(c == 'D'){
			a[i].t = 1;
			scanf("%d%d", &a[i].l, &a[i].r);
			add.emplace_back(make_pair(a[i].l, a[i].r));
			mp[a[i].l], mp[a[i].r];
		}
		else if(c == 'C'){
			a[i].t = 2;
			scanf("%d", &a[i].l);
			a[i].l--;
		}
		else{
			a[i].t = 3;
			scanf("%d%d", &a[i].l, &a[i].r);
			mp[a[i].l], mp[a[i].r];
		}
	}
	id = 1;
	for(auto &x: mp) x.second = id++;
	memset(bit,0,sizeof(bit));
	
	for(int i = 0; i < n; ++i){
		if(a[i].t == 2) continue;
		a[i].l = mp[a[i].l];
		a[i].r = mp[a[i].r];
 	}
 	for(int i = 0; i < add.size(); ++i){
 		add[i].first = mp[add[i].first];
 		add[i].second = mp[add[i].second];
 	}
 	for(int i = 0; i < n; ++i){
 		if(a[i].t == 1){
 			update(0, a[i].l, 1);
 			update(1, a[i].r, 1);
 		}
 		else if(a[i].t == 2){
 			update(0, add[a[i].l].first, -1);
 			update(1, add[a[i].l].second, -1);
 		}
 		else{
 			long long ans = query(0, a[i].r) - query(1, a[i].l - 1); 
 			// cuantos estan atras de R y cuantos terminan hasta l
 			printf("%lld\n", ans);
 		}
 	}
	return 0;
}
