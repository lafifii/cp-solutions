#include <bits/stdc++.h>
using namespace std;
string s;
/*
  Given is a string S consisting of digits from 1 through 9. 
  Find the number of pairs of integers ( i , j ) ( 1 ≤ i ≤ j ≤ | S | ) that satisfy the following condition: 
  Condition: In base ten, the i -th through j -th characters of S form an integer that is a multiple of 2019 .
*/
int main() {
	cin >> s;
	vector<long long> prev(2019, 0);
	long long ans = 0;
	prev[s[0] - '0'] = 1;  // empezar
	for(int pos = 1; pos < s.size(); ++pos){
		vector<long long> now(2019);
		for(int res = 0; res < 2019; ++res)
			now[(res*10 + s[pos] - '0')%2019] = prev[res]; 
		ans+= now[0]; // sumar los que tienen resto es 0
		prev = now;
		prev[s[pos] - '0']++; // como empezar de nuevo
	}
	cout << ans;
	
	return 0;
}
