#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 10;
int p[maxn], rk[maxn];

void init(int x){
	p[x] = x;
	rk[x] = 1;
}
int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}
void merge(int a, int b){
	a = find(a), b = find(b);
	if(rk[a] < rk[b]) swap(a, b);
	if(a != b){
		p[b] = a;
		if(rk[a] == rk[b]) rk[a]++;
	}
}
struct query{ int l, r, t, id; };
int main() {
	
	int n, m; 
	string s;
	
	while(cin >> n >> m and n != -1){
		
		vector<query> q(m); 
		map< pair<int,int> , int > mp; 
		int id = 1, ans = 0;
		
		for(int i = 0; i < m; ++i){
			cin >> q[i].l >> q[i].r >> s;
			q[i].t = (s[0] == 'e');
			
			mp[{0, q[i].l - 1}];
			mp[{1, q[i].l - 1}];
			mp[{0, q[i].r}];
			mp[{1, q[i].r}];
			
		}
		for(auto &x: mp) x.second = id++;
		
		for(int i = 0; i < m; ++i){
			int l1, r1, l2, r2;
			l1 = mp[{0, q[i].l - 1}];
			l2 = mp[{1, q[i].l - 1}];
			r1 = mp[{0, q[i].r}];
			r2 = mp[{1, q[i].r}];
			
			init(l1), init(l2), init(r1), init(r2);
		}
		
		for(int i = 0; i < m; ++i){
			int l1, r1, l2, r2;
			l1 = mp[{0, q[i].l - 1}];
			l2 = mp[{1, q[i].l - 1}];
			r1 = mp[{0, q[i].r}];
			r2 = mp[{1, q[i].r}];
			
			if(q[i].t){
				/* si es par (0, x - 1) = (0, y) en paridad
				 sino son diferente y para eso podemos usar que
				 (0, x - 1) = (1, y) en paridad y 
				 (1, x - 1) = (0, y) en paridad 
				 
				 cada nodo es un rango y estan en el mismo componenete
				 si es que tienen la misma paridad
				 
				*/
				merge(l1, r1); 
				merge(l2, r2);
			}
			else{
				merge(l1, r2);
				merge(l2, r1);
			}
			
			if(find(l1) == find(l2)) break;
			if(find(r1) == find(r2)) break;
			
			ans++;
		}
		
		cout << ans << endl;
	}
	return 0;
}
