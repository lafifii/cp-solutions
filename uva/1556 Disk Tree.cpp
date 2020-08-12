#include <bits/stdc++.h>
using namespace std;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4331

const int maxn = 1e6, alp = 70; // suma de caracteres, alp
int t[maxn][alp], nodos = 1;
string pos = "!#$%&'()-@^_`{}~\\";
int getid(char c){
	return pos.find(c);
}
void add(string s){
	int act = 0;
	for(char c: s){
		int id = getid(c);
		if(t[act][id] == 0) t[act][id] = nodos++;
		act = t[act][id];
	}
}
char transform(int num){
	return pos[num];
}
int maxl = 0, lim;
void dfs(int u, int letra, string &s, int cn = 0){
	char l = transform(letra);
	maxl = max(maxl, cn);
	if(letra == lim){ 
		for(int i = 0; i < cn; ++i) cout << ' ';
		int id = s.size() - 2;
		while(id >= 0 and s[id] != '\\') id--;
		id++;
		cout << s.substr(id) << endl;
	}
	s+=l;
	if(t[u][lim]) 
			dfs(t[u][lim], lim, s, cn + (l == '\\'));
	for(int i = 0; i <= pos.size();++i){
		if(i == lim) continue;
		if(t[u][i]) 
			dfs(t[u][i], i, s, cn + (l == '\\'));
	}
	s.pop_back();
}
void init(){
	memset(t,0,sizeof(t));
}
void init1(){
	for(char a = 'A'; a <= 'Z'; ++a) pos+=a;
	for(char a = '0'; a <= '9'; ++a) pos+=a;
	sort(pos.begin(), pos.end());
	lim = pos.find('\\');
}
int main(){
	int n;
	init1();
	while(cin >> n){
		init(); 
		string s;
		for(int i = 0; i < n; ++i){
			cin >> s;
			s+= '\\';
			add(s);
		}
		for(int i = 0; i < pos.size(); ++i){
			if(pos[alp] == '\\' ) continue;
			s = "";
			if(t[0][i]) dfs(t[0][i], i, s);
		}
		cout << endl; 
	}
	return 0;
}
