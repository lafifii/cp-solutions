#include <bits/stdc++.h>
using namespace std;
// contar triangulos tal que (x,y,z) a <= x <= b <= y <= c <= z <= d 
const int limite = 2e6;

int main() {
	vector<long long> suma(limite, 0);
	int a, b, c , d;
	cin >> a >> b >> c >> d;
	for(int i = a; i <= b; ++i){
		suma[i + b]++;
		suma[i + c + 1]--; // contar (x, y)
	}
	for(int i = 1; i < limite; ++i) suma[i]+= suma[i - 1];
	
	long long ans = 0;
	for(int z = c; z < limite; ++z)
		ans+= suma[z]*(long long)max( ( min(d, z - 1) - c + 1) , 0 ); 
	// z - 1 pq 1 es = x + y no cuenta y min con d pq no puede pasar de d el lado (x + y)
	cout << ans << endl;
	
	return 0;
}
