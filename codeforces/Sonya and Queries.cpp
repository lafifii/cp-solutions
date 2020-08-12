#include <bits/stdc++.h>
using namespace std;
// https://codeforces.com/contest/713/problem/A
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
string binary(string n){
	string s = "";
	for(char x: n){
		if((x - '0')%2) s+='1';
		else s+='0';
	}
	return s;
}
int query(string s){
	int act = 0;
	for(char c: s){
		int id = getid(c);
		if(t[act][id] == 0) return 0;
		act = t[act][id];
	}
	if(term[act]) return term[act];
	return 0;
}
int main(){
	init();
	int ans, q; string s;
	char op;
	cin >> q;
	while(q--){
		cin >> op >> s;
		if(op == '+') add(binary(s));
		else if(op == '-') remove_oc(binary(s));
		else{
			int ans = 0;
			while(s.size() < 18) s = '0' + s;
			for(int i = 17; i >= 0; --i){
				string aux = s.substr(i);
				int si = 1;
				for(int j = 0; j < i; ++j) si&= (s[j] == '0');
				if(si) ans+=query(aux);
			}
			cout << ans << endl;
		}
	}
	return 0;
}
/* 
  type of queries
  +  ai — add non-negative integer ai to the multiset. 
     Note, that she has a multiset, thus there may be many occurrences of the same integer.
  -  ai — delete a single occurrence of non-negative integer ai from the multiset. 
     It's guaranteed, that there is at least one ai in the multiset.
  ?  s — count the number of integers in the multiset (with repetitions) that match some pattern s 
     consisting of 0 and 1. In the pattern, 0 stands for the even digits, while 1 stands for the odd. 
     Integer x matches the pattern s, if the parity of the i-th from the right digit in decimal notation 
     matches the i-th from the right digit of the pattern. If the pattern is shorter than this integer, 
     it's supplemented with 0-s from the left. Similarly, if the integer is shorter than the pattern its 
     decimal notation is supplemented with the 0-s from the left.
*/
