#include bitsstdc++.h
using namespace std;
long long tobase10(string a, int b){
	long long num = 0, pt = 1;
	for(int i = a.size() - 1; i = 0; --i){
		int digito = ( a[i] = '0' and a[i] = '9'  a[i] - '0'  a[i] - 'A' + 10);
		num+= (digitopt);
		pt= b;
	}
	return num;
}
int main() {
	string a, b;
	while(cin  a  b){
		int minb1 = 0, minb2 = 0;
		
		for(char c a){
			if(c = '0' and c = '9') minb1 = max(minb1, c - '0');
			else minb1 = max(minb1, c - 'A' + 10);
		}
		for(char c b){
			if(c = '0' and c = '9') minb2 = max(minb2, c - '0');
			else minb2 = max(minb2, c - 'A' + 10);
		}
		
		minb1 = max(minb1 + 1, 2);
		minb2 = max(minb2 + 1, 2);
		
		int ansb1 = -1 , ansb2 = -1;
		for(int b1 = minb1; b1 = 36; ++b1){
			long long numero1_base = tobase10(a, b1);
			for(int b2 = minb2; b2 = 36; ++b2){
				long long numero2_base = tobase10(b, b2);
				if(numero2_base == numero1_base and ansb1 == -1) ansb1 = b1, ansb2 = b2;
			}
		}
		cout  a;
		if(ansb1 == -1) cout   is not equal to   b   in any base 2..36  endl;
		else cout   (base   ansb1  ) = ;
		if(ansb2 != -1) cout  b   (base   ansb2 )  endl;
	}
	return 0;
}