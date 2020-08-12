/* https://www.codechef.com/problems/NPLFLF 
1. Add: Add a given string to the collection.
2. Ask: Ask if there exists a group of k strings such that they have a common suffix of length l .
3. Remove i: Remove the string that was added in the ith operation (if the string is not already removed). 
It is guaranteed that ith operation was an Add operation.
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10, alp = 27; // suma de caracteres, alp
int t[maxn][alp], term[maxn], vis[maxn], nodos = 1;
bool del[maxn];
vector<set<int>> lvl(maxn);
int getid(char c){
	return c - 'a';
}
void add(string s){
	int act = 0;
	lvl[0].insert(0);
	for(int i = 0; i < s.size(); ++i){
		int id = getid(s[i]);
		if(t[act][id] == 0) t[act][id] = nodos++;
		vis[act]++;
		act = t[act][id];
		lvl[i + 1].insert(act);
	}
	term[act]++;
	vis[act]++;
}
void remove_oc(string s){
	int act = 0, id, parent = -1;
	for(int i = 0; i < s.size(); ++i){
		id = getid(s[i]);
		vis[act]--;
		if(vis[act] == 0 and parent != -1){ 
			t[parent][getid(s[i - 1])] = 0;
			lvl[i + 1].erase(act);
		}
		parent = act;
		act = t[act][id];
	}
	vis[act]--;
	if(vis[act] == 0 and parent != -1){ 
		t[parent][id] = 0;
		lvl[s.size()].erase(act);
	}
	term[act]--;
}
string query(int k, int len){
	for(int x: lvl[len]){
		if(vis[x] >= k) return "YES\n";
	}
	return "NO\n";
}
void init(){
	memset(t,0,sizeof(t));
	memset(term,0,sizeof(term));
	memset(vis,0,sizeof(vis));
}
int main(){
	memset(del,0,sizeof(del));
	int q, k, len, op;
	init();
	cin >> q;
	vector<string> v;
	string s;
	while(q--){
		cin >> op;
		if(op == 1){ 
			cin >> s;
			reverse(s.begin(), s.end());
			add(s);
			v.push_back(s);
		}
		else if(op == 2){
			cin >> k >> len; 
			cout << query(k, len);
			v.push_back("");
		} 
		else{
			cin >> op;
			if(!del[op - 1]) remove_oc(v[op - 1]);
			del[op - 1] = 1;
			v.push_back("");
		}
	}
}
