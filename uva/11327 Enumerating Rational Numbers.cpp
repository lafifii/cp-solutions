#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7;
long long lp[maxn + 5], phi[maxn + 5], sum[maxn + 5];
vector<int> pr;
void calphi(){
    phi[1] = 1;
    for (int i = 2; i <= maxn; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            phi[i] = i - 1;
            pr.push_back(i);
        }
        else
        {
            if (lp[i] == lp[i / lp[i]]) phi[i] = phi[i / lp[i]] * lp[i];
            else phi[i] = phi[i / lp[i]] * (lp[i] - 1);
        }
        for (int j = 0; j < (int)pr.size() and pr[j] <= lp[i] and i * pr[j] <= maxn; ++j)
            lp[i * pr[j]] = pr[j];
    }
    sum[0] = 0;
    phi[1] = sum[1] = 2; 
    for(int i = 2; i <= maxn; ++i) sum[i] = phi[i] + sum[i - 1];
}
int main(){
	calphi();
	long long k;
	while(cin >> k and k){
		long long num = lower_bound(sum, sum + maxn, k) - sum;
		if(num == 1LL) cout << (k == 1LL ? 0 : 1) << '/' << 1 << endl;
		else{
			long long tr = sum[num - 1], i = 1; 
			for(; i <= num; ++i){
				if(__gcd(num,i) == 1LL) ++tr;
				if(tr == k){
					cout << i << '/' << num << endl;
					break;
				}
			}
		
			
		}

	}

	return 0;
}
