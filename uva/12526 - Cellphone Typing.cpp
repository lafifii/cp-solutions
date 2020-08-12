#include <bits/stdc++.h>
using namespace std;
/*
   average number of keystrokes needed to type a
   word in the dictionary 
   https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3971
*/
const int maxn = 2e6 + 30, alp = 27; // suma de caracteres, alp
int t[maxn][alp], vis[maxn], nodos = 1, ans;
bool term[maxn]; 

int getid(char c){
	return c - 'a';
}
void add(string s){
	int act = 0;
	for(char c: s){
		int id = getid(c);
		if(t[act][id] == 0) t[act][id] = nodos++;
		vis[act]++;
		act = t[act][id];
	}
	vis[act]++;
	term[act] = 1;
}
void init(){
	memset(t,0,sizeof(t));
	memset(term,0,sizeof(term));
	memset(vis,0,sizeof(vis));
}
void dfs(int u, map<int,int>&mp){
	mp[vis[u]]++;
	if(term[u]) ans+= mp.size();
	for(int i = 0; i < alp; ++i){
		if(t[u][i])
			dfs(t[u][i], mp);
	}
	mp[vis[u]]--; 
	if(mp[vis[u]] == 0) mp.erase(vis[u]);
}
int main(){
	int n;
	string s;
	while(cin >> n){
		init();
		ans = 0;
		for(int i = 0; i < n; ++i){
			cin >> s;
			add(s);
		}
		for(int i = 0; i < alp; ++i){
			map<int, int> mp;
			if(t[0][i]) dfs(t[0][i], mp);
		}
		printf("%.2f\n", (double)ans/n);
	}
	return 0;
}
