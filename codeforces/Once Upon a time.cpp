// statement: https://codeforces.com/gym/100963/attachments/download/4256/20072008-summer-petrozavodsk-camp-japanese-contest-20070829-en.pdf (J)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a1, a2, r1, r2; 
ll inf = LLONG_MAX;
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
 
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}
void shift_solution(ll & x, ll & y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}
ll find_all_solutions(ll a, ll b, ll c, ll minx, ll miny) {
    ll x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return -inf;
    a /= g;
    b /= g;
 
    ll sign_a = a > 0 ? +1 : -1;
    ll sign_b = b > 0 ? +1 : -1;
 
    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    ll lx1 = x;
    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);

    ll lx2 = x;
    ll lx = max(lx1, lx2);
    return lx;
}
int main() {
	ll c,d,n,m;
	while(cin >> a1 >> r1 >> r2 >> a2){
		if(!a1 and !r1 and !a2 and !r2) break;
		c = -a1 + a2 + r1 - r2; 
		d = gcd(r1,-r2,n,m);
		if(c%d){
			cout << "Impossible" << endl;
			continue;
		}
		ll n = find_all_solutions(r1, -r2, c,  1, 2); 
		// first element is the only important thing
		if(n == -inf) cout << "Impossible";
		else cout << a1 +  (n - 1)*r1 << endl;
	}
	return 0;
}
