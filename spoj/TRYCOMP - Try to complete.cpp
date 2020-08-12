#include <bits/stdc++.h>
using namespace std;
/*
Find the most occuring word in the book with S as prefix. 
If there are many such words, print the lexicographically smallest word.
*/
const int maxn = 5e6, alp = 27; // suma de caracteres, alp
int t[maxn][alp], term[maxn], nodos = 1, best[maxn];
vector<string> fin(maxn);
int getid(char c){
	return c - 'a';
}
void add(string s){
	int act = 0;
	for(char c: s){
		int id = getid(c);
		if(t[act][id] == 0) t[act][id] = nodos++;
		act = t[act][id];
	}
	term[act]++;
	fin[act] = s;
}
int search(string s){
	int act = 0;
	for(char c: s){
		int id = getid(c);
		if(t[act][id] == 0) return -1;
		act = t[act][id];
	}
	return best[act];
}
void init(){
	memset(t,0,sizeof(t));
	memset(term,0,sizeof(term));
}
pair<int,int> dfs(int u){
	int dis = (term[u] ? 0 : INT_MAX), nodo = u;
	for(int i = 0; i < alp; ++i){
		if(t[u][i]){
			pair<int,int> dis_nodo = dfs(t[u][i]); 
			if(term[dis_nodo.second] > term[nodo]){
				dis = 1 + dis_nodo.first;
				nodo = dis_nodo.second;
			}
		}
	}
	best[u] = nodo; 
	return {dis, nodo};
}
int main(){
	init();
	int n; string s;
	cin >> n;
	while(n--){
		cin >> s;
		add(s);
	}
	for(int i = 0; i < alp; ++i){
		if(t[0][i]) dfs(t[0][i]);
	}
	cin >> n;
	while(n--){
		cin >> s;
		int id = search(s);
		if(id == -1) cout << -1 << endl;
		else cout << fin[id] << ' ' << term[id] << endl;
	}
	return 0;
}
