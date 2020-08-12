#include <bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemsets/acmsguru/problem/99999/106
typedef long long ll;
ll ans = LLONG_MAX; 
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
bool find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
    if(a == 0 or b == 0){
    	ans = 1; // one solution
    	return ((a == 0 and c%b == 0) or (b == 0 and c%a == 0));
    }
    ll x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    ll sign_a = a > 0 ? +1 : -1;
    ll sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return false;
    ll lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    ll rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return false;
    ll lx2 = x;
    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    ll rx2 = x;
    if (lx2 > rx2)
        swap(lx2, rx2);
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);

    if (lx > rx)
        return false;
    ans = (rx - lx)/abs(b) + 1; // #solutions (rx - lx)/abs(b) + 1
    return true;
}
int main() {
	ll a,b,c,x1,x2,y1,y2;
	cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
	if(a == 0 and b == 0 and c != 0){
		cout << 0;
		return 0;
	}
	if(find_all_solutions(a,b,-c,x1,x2,y1,y2)) cout << ans << endl; 
	else cout << 0 << endl;
	return 0;
}
