#include <bits/stdc++.h>
using namespace std;
/*
  There are N pieces of sushi. Each piece has two parameters: "kind of topping" t i and "deliciousness" d i . 
  You are choosing K among these N pieces to eat. Your "satisfaction" here will be calculated as follows: 
  The satisfaction is the sum of the "base total deliciousness" and the "variety bonus". 
  The base total deliciousness is the sum of the deliciousness of the pieces you eat. 
  The variety bonus is x ∗ x , where x is the number of different kinds of toppings of the pieces you eat. 
  You want to have as much satisfaction as possible. Find this maximum satisfaction.
*/
bool cmp(pair<int,long long> a, pair<int,long long> b){
	return a.second > b.second;
}
int main() {
	int n,k;
	long long cnt = 0, num = 0;
	long long ans = 0, sz;
	cin >> n >> k;
	vector<pair<int,long long>> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
	sort(a.begin(), a.end(), cmp);
	map<int,int> mp;
	stack<pair<int,long long>> st;
	
	for(int i = 0; i < n; ++i){
		if(num < k){
			num++;
			cnt+= a[i].second;
			mp[a[i].first]++;
			if(mp[a[i].first] > 1) st.push(a[i]);
		}
		else{
			if(st.size() == 0) break;
			if(mp[a[i].first]) continue;
			cnt-= st.top().second;
			cnt+= a[i].second;
			st.pop();
			mp[a[i].first]++;
		}
		sz = mp.size();
		ans = max(ans, cnt + sz*sz);
	}
	cout << ans;
	return 0;
}
