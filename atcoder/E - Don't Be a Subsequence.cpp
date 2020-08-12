#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
vector<int> lad[27];
int n, dp[maxn];
int f(int pos){
	if(pos > n) return 1;
	if(dp[pos] != -1) return dp[pos];
	int ans = INT_MAX;
	for(char i = 'a'; i <= 'z'; ++i){
		auto next = upper_bound(lad[i - 'a'].begin(), lad[i - 'a'].end(), pos);
		if(next == lad[i - 'a'].end()) ans = 1;
		else ans = min(ans, 1 + f(*next));
	}
	return dp[pos] = ans;
}
void rec(int pos){
	if(pos > n) return;
	int ans = f(pos), siguiente;
	char imprimir = 'z' + 2;
	for(char i = 'a'; i <= 'z'; ++i){
		auto next = upper_bound(lad[i - 'a'].begin(), lad[i - 'a'].end(), pos);
		if(next == lad[i - 'a'].end())
			imprimir = min(imprimir, i);
		else if(1 + f(*next) == ans){ 
			if(i < imprimir)
				imprimir = i, siguiente = *next;
		}
	}
	cout << imprimir;
	if(ans != 1) rec(siguiente);
}

int main(){
	string s;
	cin >> s;
	n = s.size();
	for(int i = 0; i < s.size(); ++i)
		lad[s[i] - 'a'].push_back(i + 1);
	memset(dp,-1,sizeof(dp));
	rec(0);
	return 0;
}
