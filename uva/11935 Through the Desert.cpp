#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
// 1: leak
// 2: gas
// 3: mec
int km[maxn], tipo[maxn], n, consume[maxn];
bool pred(double f){
	int estoy = 0, nw = 0, lk = 0;
	double st = f;
	for(int i = 1; i < n; ++i){
		double dif = ((km[i] - estoy)/100.0)*consume[nw] + (km[i] - estoy)*lk;
		f-= dif;
		if(f < 0) return false;
		
		if(tipo[i] == 1) lk++;
		if(tipo[i] == 2) f = st;
		if(tipo[i] == 3) lk = 0;
		if(tipo[i] == 4) nw++;
		
		estoy = km[i];
	}
	return true;
}
int main(){
	int idc = 0;
	n = 0;
	int a, b;
	string s;
	while(cin >> a >> s >> s >> consume[idc] and consume[idc]){
		idc++;
		km[n++] = 0, tipo[0] = 0;
		while(cin >> a >> s and s != "Goal"){
			km[n] = a;
			if(s == "Leak") tipo[n] = 1;
			else if(s == "Gas"){
				cin >> s;
				tipo[n] = 2;
			}
			else if(s == "Mechanic") tipo[n] = 3;
			else{ 
				cin >> s >> consume[idc];
				tipo[n] = 4;
				idc++;
			}
			n++;
		}
		tipo[n] = 0;
		km[n++] = a;
		
		double lo = 0, hi = 1e7, ans = 1e7;
		for(int i = 0; i <= 100; ++i){
			double mid = (lo + hi)/2.0;
			if(pred(mid)) ans = min(ans, mid), hi = mid;
			else lo = mid;
		}
		
		printf("%.3f\n", ans);
		n = 0;
		idc = 0;
	}
	
	return 0;
}
