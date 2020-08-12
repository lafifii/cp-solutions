#include <bits/stdc++.h>
using namespace std;

int main() {
	int num;
	cin >> num;
	if(num == 0){
		cout << 0;
		return 0;
	}
	int base = -2;
	vector<int> ans;
	while(num != 0){
		int res = num%base;
		num/=base;
		
		if(res < 0){
			res-= base;
			num++;
		}
		ans.push_back(res);
	}
	
	for(int i = ans.size() - 1; i >= 0; --i) cout << ans[i];
	
	return 0;
}
