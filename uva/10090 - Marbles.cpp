#include <bits/stdc++.h>
// ax + by = n, minimize xc1 + y c2
// https://vjudge.net/problem/21257/origin
using namespace std;
typedef long long ll;
ll gcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    ll x1, y1;
    ll d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
int main() {
	ll n, c1, c2, n1, n2, x, y;
	bool ans;
	while(cin >> n and n){
		cin >> c1 >> n1 >> c2 >> n2;
		ll d = gcd(n1,n2,x,y);
		if(n%d){
			cout << "failed\n";
			continue;
		}
		x = x*n/d, y = y*n/d; //x = x + (b/d)*N;
		n1 = n1/d, n2 = n2/d; //y = y - (a/d)*N;
		//y/n1 >= t >= -x/n2
		// minimize x*c1 + y*c2 -> monotic, solve tmin or tmax
		ll t1 = (ll)ceil(-1.0*x/n2);
		ll t2 = (ll)floor(1.0*y/n1);
		if(t2 < t1) cout << "failed\n";
		else{
			//calculate in tmin and tmax
			ll ans = 0;
			ll x0 = x + n2*t1, y0 = y - n1*t1;
			ll x1 = x + n2*t2, y1 = y - n1*t2;
			if((x0 < 0 or y0 < 0) and (x1 < 0 or y0 < 0))
				cout << "failed\n";
			else if(x0 < 0 or y0 < 0)
				cout << x1 << ' ' << y1 << endl;
			else if(x1 < 0 or y1 < 0)
				cout << x0 << ' ' << y0 << endl;
			else{
				ll c_t1 = x0*c1 + y0*c2;
				ll c_t2 = x1*c1 + y1*c2;
				if(c_t1 < c_t2) cout << x0 << ' ' << y0 << endl;
				else cout << x1 << ' ' << y1 << endl;
			}
		}
	}
	return 0;
}
