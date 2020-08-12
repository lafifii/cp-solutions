#include <bits/stdc++.h>
using namespace std;
// https://www.spoj.com/problems/DICT/cstart=10
const int maxn = 1e6, alp = 27; // suma de caracteres, alp
int t[maxn][alp], term[maxn], vis[maxn], nodos = 1;
vector<int> pref[maxn];
vector<string> V;
int getid(char c){
	return c - 'a';
}
void add(string s, int idx){
	int act = 0;
	for(char c: s){
		int id = getid(c);
		vis[act]++;
		if(t[act][id] == 0) t[act][id] = nodos++;
		pref[act].push_back(idx);
		act = t[act][id];
	}
	pref[act].push_back(idx);
	term[act]++;
	vis[act]++;
}
bool search(string s){
	int act = 0;
	for(char c: s){
		int id = getid(c);
		if(t[act][id] == 0) return 0;
		act = t[act][id];
	}
	set<string> st;
	for(int i = 0; i < alp; ++i){
		if(t[act][i])
			for(int x: pref[t[act][i]])
				st.insert(V[x]);
	}
	if(st.size() == 0) return 0;
	for(auto x: st) cout << x << endl;
	return 1;
}
void init(){
	memset(t,0,sizeof(t));
	memset(term,0,sizeof(term));
	memset(vis,0,sizeof(vis));
}
int main(){
	int n, q; string s;
	init();
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> s;
		add(s, V.size());
		V.push_back(s);
	}
	cin >> q;
	for(int i = 1; i <= q; ++i){
		cin >> s;
		cout << "Case #" << i << ":\n";
		if(not search(s)) cout << "No match.\n";
	}
}
