#include <bits/stdc++.h>
using namespace std;
//// https://codeforces.com/contest/706/problem/D , maximo xor entre x y multiset A, con queries
const int maxn = 6400020, alp = 2; // suma de caracteres, alp
int t[maxn][alp], term[maxn], vis[maxn], nodos = 1;
int getid(char c){
	return c - '0';
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
	term[act]++;
}
int max_xor(string s){
	int ans = 0, pot = 31, act = 0;
	
	for(char c: s){
		int id = not getid(c);
		if(t[act][id] == 0){
			id = !id;
			if(t[act][id] == 0) break;
		}
		if(id == 1) ans|=(1 << pot);
		pot--;
		act = t[act][id];
	}
	return ans; 
}
void remove_oc(string s){
	if(s.size() == 0) return;
	int act = 0, id, parent;
	vis[0]--;
	for(int i = 0; i < s.size(); ++i){
		id = getid(s[i]);
		parent = act;
		act = t[act][id];
		vis[act]--;
		if(!vis[act]) t[parent][id] = 0;
	}
	term[act]--;
}
void init(){
	memset(t,0,sizeof(t));
	memset(term,0,sizeof(term));
	memset(vis,0,sizeof(vis));
}
string binary(int n){
	string s = "";
	while(n){
		s+=(n%2 + '0');
		n/=2;
	}
	while(s.size() < 32) s+='0';
	reverse(s.begin(), s.end());
	return s;
}
int main(){
	init();
	int q, n;
	char op;
	cin >> q;
	add(binary(0));
	while(q--){
		cin >> op >> n;
		string s = binary(n);
		if(op == '+') add(s);
		else if(op == '-') remove_oc(s);
		else cout << (max_xor(s)^n) << endl;
	}
	return 0;
}
