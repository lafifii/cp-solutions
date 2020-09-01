#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e6 + 20;

string s = "i lik   to   xplor   univ rs ";
string dictionary[] = {"like", "explore", "toe", "universe", "rse"};
vector<string> ans;
int t[maxn][30], fin[maxn], nd = 1;

bool ok(string aux, int deb = 0){
	if(aux=="") return 1;
	
    int lo = 0, es = 0;
    for(char c: aux) es|= (c == 'e');
    
    if(!es){
    	if(deb) return 1;
    	int i = 0;
    	for(; i < aux.size(); ++i){
    		int cc = aux[i] - 'a';
    		if(t[lo][cc] == 0) break;
    		lo = t[lo][cc];
    	}
    	if(i == aux.size()) return 0;
    	return 1;
    		
    }
    
    lo = 0;
    for(char c: aux){
    	int cc = c - 'a';
        if(t[lo][cc] == 0) return false;
        lo = t[lo][cc];
    }
    
	return fin[lo];
}
string f(string aux, int fi = 0){
	string aux2 = "";
	int sp = -1, i = (int)aux.size() - 1;
	while(aux[i] == ' ') i--;
	
	for( ; i >= 0; --i) 
		if(aux[i] == ' ')
		{
			sp = i;
			break;
		}
	
	if(sp == -1) return aux;
	sp++;
	for(; sp < aux.size() and aux[sp] != ' '; ++sp)
		aux2+= aux[sp];
		
	return aux2;
}
void bt(int pos, string last, string curs){
    if(pos > s.size()) return;
    if(pos == s.size()){ 
       if(ok(f(curs))) cout << curs <<  endl;
       return;
    }
	
    // can break the word
    if(s[pos] == ' '){
     
        bt(pos+1,last, curs + "e");
        // break it
        int nw;
        // i can 
        if(pos + 1 < s.size() and s[pos+1] != ' ') nw = ok(f(curs), 1);
        else nw = ok(f(curs));
        
        if(nw){
            bt(pos+1, f(curs) , curs + s[pos]);
        }
    }
    else{ 
        bt(pos + 1, last, curs + s[pos]);
    }
}
void add(string &s){
    int lo = 0;
    for(char c: s){
        int cc = c - 'a';
        if(t[lo][cc] == 0) t[lo][cc] = nd++;
        lo = t[lo][cc];
    }
    fin[lo] = 1;
}
int main(){
    vector<string> cur;
    cur.push_back("");
    memset(fin,0,sizeof(fin));
    for(int i = 0; i < 5; ++i) add(dictionary[i]);
    
    bt(0,"","");
	return 0;
}
