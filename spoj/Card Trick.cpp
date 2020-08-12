#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e4 + 5;
int bit[maxn], n;
/*
  The i's cards are moved to the bottom of the pack. 
  The new top card is dealt face up onto the table. It is the ith of Spades.
  
  encontrar en cada paso posicion tal que luego si quito i desde ahi la i + 1 
  sera igual a la del numero i
  
*/
void update(int x, int val){
	for(; x <= n; x+=x&-x) bit[x]+= val;
}
int query(int x){
	int sum = 0;
	for(; x > 0; x-=x&-x) sum+= bit[x];
	return sum;
}
int find(int lo){
	int hi = n, ans = n;
	while(lo <= hi){
		int mid = (lo + hi)/2;
		if(query(mid) > 0) ans = min(ans, mid), hi = mid - 1;
		else lo = mid + 1;
	}
	return ans;
}
int main() {
	int t, lo, hi, ans;
	cin >> t;
	while(t--){
		cin >> n;
		vector<int> v(n + 1, 0);
		memset(bit,0,sizeof(bit));
		for(int i = 1; i <= n; ++i) update(i, 1);
		int at = 1;
		for(int i = 1; i <= n; ++i){
			int qq = query(n) - query(at - 1);
			int k = i + 1;
			if(k > qq){ 
				k-= qq;
				k = k%query(n);
				if(k == 0) k = query(n);
				
				lo = 1, hi = n, ans = n;
				at = 1;
			}
			else{
				k = query(at - 1) + k;
				lo = at, hi = n, ans = n;
			}
			while(lo <= hi){
				int mid = (lo + hi)/2;
				if(query(mid) >= k) ans = min(mid, ans), hi = mid - 1;
				else lo = mid + 1;
			}
			update(ans, -1);
			v[ans] = i;
			at = find(ans + 1);
		}
		for(int i = 1; i <= n; ++i) cout << v[i] << " ";
		puts("");
	}
	return 0;
}
