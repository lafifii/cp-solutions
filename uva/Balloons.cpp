#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxN = 3e5;
int n, c;
vector<int> g[maxN];

struct Point {
	int x, y;
	Point(int x=0, int y=0):x(x), y(y) {}
	Point operator +(Point other) {return Point(x+other.x, y+other.y);}
	Point operator -(Point other) {return Point(x-other.x, y-other.y);}
	ll operator *(Point other) {return x*1ll*other.x + y*1ll*other.y;}
	ll operator ^(Point other) {return x*1ll*other.y - y*1ll*other.x;}
};

struct Segment {
	Point a, ab;
	Segment(Point a=Point(), Point b=Point(), bool twoPoints=true): a(a), ab(twoPoints?b-a:b) {}
	Point b() {
		return a + ab;
	}
} seg[maxN];
int elem = 0;

struct Node {
	Segment s;
	int prior;
	int l, r;
	int id;
} T[maxN];

bool cmp(int i, int x, int key) {
	return	(T[i].s.ab ^ (T[i].s.a - Point(x, 0))) < key *1ll* T[i].s.ab.x; 
}

bool cmp2(int i, int x, int key) {
	return	(T[i].s.ab ^ (T[i].s.a - Point(x, 0))) <= key *1ll* T[i].s.ab.x; 
}

void split(int t, int& l, int& r, int x, int key) {
	if (t == 0) {
		l = r = 0;
		return;
	}
	if (cmp(t, x, key)) {
		split(T[t].r, T[t].r, r, x, key), l = t;
	} else {
		split(T[t].l, l, T[t].l, x, key), r = t;
	}
}

void split2(int t, int& l, int& r, int x, int key) {
	if (t == 0) {
		l = r = 0;
		return;
	}
	if (cmp2(t, x, key)) {
		split2(T[t].r, T[t].r, r, x, key), l = t;
	} else {
		split2(T[t].l, l, T[t].l, x, key), r = t;
	}
}

void merge(int& t, int l, int r) {
	if (l == 0 or r == 0) {
		t = l ^ r;
		return;
	}
	if (T[l].prior > T[r].prior) {
		merge(T[l].r, T[l].r, r), t = l;
	} else {
		merge(T[r].l, l, T[r].l), t = r;
	}
}

int begin(int t) {
	if (T[t].l) return begin(T[t].l);
	return t;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<> dis(1, 1000000000);

int p[maxN];
void add(int &t, int id) {
	int u;
	split(t, t, u, seg[id].a.x, seg[id].a.y);
	if (seg[id].a.y > seg[id].b().y) {
		int v = begin(u);
		p[id] = T[v].id;
	}
	T[++elem] = {seg[id], dis(rng), 0, 0, id};
	merge(t, t, elem);
	merge(t, t, u);
}

void print(int t) {
	if (t == 0) return;
	print(T[t].l);
	cout << T[t].id << " ";
	print(T[t].r);
}

void erase(int &t, int id) {
	int u, v;
	split(t, t, u, seg[id].b().x, seg[id].b().y);
	split2(u, u, v, seg[id].b().x, seg[id].b().y);
	if (seg[id].b().y > seg[id].a.y) {
		int w = begin(v);
		p[id] = T[w].id;
	}
	merge(t, t, v);
}

struct ToSort {
	Point p;	
	bool open;
	int id;
} Q[maxN];

Point ans[maxN];
bool vis[maxN];
Point lans;
void dfs(int pos) {
	vis[pos] = 1;
	ans[pos] = lans;	
	for (int v : g[pos]) {
		if (not vis[v]) {
			if (seg[pos].a.y == seg[pos].b().y) {
				lans.x = seg[v].a.y > seg[v].b().y ? seg[v].a.x : seg[v].b().x;
				lans.y = pos ? seg[pos].a.y: -1;
			} 
			dfs(v);
		}
	}	
}

int main() {
	while (scanf("%d %d", &n, &c) == 2) {		
		for (int i = 0; i <= n+c; ++i) {
			g[i].clear();
			vis[i] = 0;
			p[i] = 0;
		}
		elem = 0;
		for (int i = 1; i <= n; ++i) {
			int x_1, y_1, x_2, y_2;
			scanf("%d %d %d %d", &x_1, &y_1, &x_2, &y_2);
			if (x_1 > x_2) {
				swap(x_1, x_2);
				swap(y_1, y_2);
			}		
			seg[i] = Segment(Point(x_1, y_1), Point(x_2, y_2));
		}
		for (int i = 1; i <= c; ++i) {
			int x;	
			scanf("%d", &x);
			seg[n+i] = Segment(Point(x-1, -1), Point(x, 0));
		}
		for (int i = 0; i < n+c; ++i) {
			Q[2*i] = {seg[i+1].a, 1, i+1};
			Q[2*i+1] = {seg[i+1].b(), 0, i+1};
		}	
		sort(Q, Q + 2*(n+c), [](ToSort p, ToSort q) {
			return p.p.x < q.p.x or p.p.x == q.p.x and 
			((p.open and not q.open) or 
			((p.open and q.open) and p.p.y > q.p.y) or
			((not p.open and not q.open) and p.p.y < q.p.y));
		});
		int	root = 0;
		for (int i = 0; i < 2*(n+c); ++i) {
			if (Q[i].open) {
				add(root, Q[i].id);
			} else {
				erase(root, Q[i].id);
			}
		}
		for (int i = 1; i <= n+c; ++i) {
			g[p[i]].push_back(i);
		}
		dfs(0);
		for (int i = 1; i <= c; ++i) {
			if (~ans[n+i].y) printf("%d %d\n", ans[n+i].x, ans[n+i].y);
			else printf("%d\n", ans[n+i].x);
		}	
	}
	return 0;
}
