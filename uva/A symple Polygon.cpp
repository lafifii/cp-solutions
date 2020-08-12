#include <bits/stdc++.h>
using namespace std;

const int maxn = 4e4 + 5;
const double eps = 1e-6;

struct Point{ int x, y; };

int n;
Point point[maxn];
int direction(Point p0, Point p1, Point p2){
	long long value;

	value = (p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y);
	if (value > 0) return 1;
	if (value < 0) return -1;
	return 0;
}
 
int on_segment(Point p1, Point p2, Point p3){
  if( min(p1.x, p2.x) <= p3.x and p3.x <= max(p1.x, p2.x) and
      min(p1.y, p2.y) <= p3.y and p3.y <= max(p1.y, p2.y) ) return 1;
  return 0;
}

double y_of_segment(int seg, double x){
	int x1 = point[seg].x;
	int y1 = point[seg].y;
	int x2 = point[(seg+1) % n].x;
	int y2 = point[(seg+1) % n].y;
 
	if(x1==x2) {  
		if( x == x1 ) return min(y1,y2);
		if( x < x1 ) return -INFINITY;
		else	 return +INFINITY;
	}
	else 
		return y1+(x-x1)/(x2-x1)*(y2-y1);
}

bool segment_above(int seg1, int seg2, double x){
	double y1, y2;
	Point p1, p2, p3, p4, pom, pmax, pmin;
 
	y1 = y_of_segment(seg1, x);
	y2 = y_of_segment(seg2, x);
	if( abs(y1 - y2) < eps ) { 
		p1 = point[seg1];
		p2 = point[(seg1+1)%n];
		p3 = point[seg2];
		p4 = point[(seg2+1)%n];
		if( ( p1.x > p2.x ) or ( p1.x == p2.x and p1.y > min(p1.y, p2.y)  ))
			{ pom = p1; p1 = p2; p2 = pom; }
		if( ( p3.x > p4.x ) or ( p3.x == p4.x and p3.y > min(p3.y, p4.y)  ))
			{ pom = p3; p3 = p4; p4 = pom; }

		pmax = p2; if(p2.x < p4.x)  pmax = p4;
		pmin = p1; if(p3.x < p1.x)  pmin = p3;
		if( pmax.x > x ) {
			y1 = y_of_segment(seg1, pmax.x);
			y2 = y_of_segment(seg2, pmax.x);
		} else if( pmin.x < x ) {
			y1 = y_of_segment(seg1, pmin.x);
			y2 = y_of_segment(seg2, pmin.x);
		}
	}
	return( y1 > y2 );	
}

int intersect(Point p1, Point p2, Point p3, Point p4){
 
	int d1 = direction(p3, p4, p1);
	int d2 = direction(p3, p4, p2);
	int d3 = direction(p1, p2, p3);
	int d4 = direction(p1, p2, p4);
 
	if(  ((d1>0 and d2 <0) or (d1<0 and d2>0)) and
	     ((d3>0 and d4 <0) or (d3<0 and d4>0)) )  return 1;
	else if (d1 == 0 and on_segment(p3, p4, p1))  return 1;
	else if (d2 == 0 and on_segment(p3, p4, p2))  return 1;
	else if (d3 == 0 and on_segment(p1, p2, p3))  return 1;
	else if (d4 == 0 and on_segment(p1, p2, p4))  return 1;
	
	return 0;
}
 
// arbol binario
struct Node{
	int seg;
	struct Node *down;
	struct Node *up;
};

Node *root;
int nodes_last;
Node nodes[maxn];
int empty_nodes_last;
Node *empty_nodes[maxn]; 
 
void init_bin_tree() {
	root = NULL;
	nodes_last = -1;
	empty_nodes_last = -1;
}
 
Node* new_node(int seg) {
	Node * node;
 
	if( empty_nodes_last < 0) {
		node = &nodes[++nodes_last];
		assert(nodes_last < maxn);
	} else {
		node = empty_nodes[empty_nodes_last--];
	}
	node->seg = seg;
	node->up = NULL;
	node->down = NULL;
	return node;
}
 
Node* inserNode(Node *node, int seg, int x){
	if(node == NULL)
		return new_node(seg);
	else {
		if( segment_above( seg, node->seg, x)  ) {
			node->up = inserNode(node->up, seg, x);
		}
		else {
			node->down = inserNode(node->down, seg, x);
		}
		return node;
	}
}
 
Node* delete_node(Node* node, int seg, int x){
	Node* repl_node;
 
	if(node == NULL)
		return NULL;
	else {
	  if(node->seg == seg) {
		if(node->down == NULL) {
			empty_nodes[++empty_nodes_last] = node;
			return node->up;
		} else if(node->up == NULL) {
			empty_nodes[++empty_nodes_last] = node;
			return node->down;
		} else {
			repl_node = node->down;
			while( repl_node->up != NULL) repl_node = repl_node->up;				
			node->seg = repl_node->seg;
			node->down = delete_node(node->down, node->seg, x);
			return node;
		}
	  }
	  else {
		if( segment_above(seg, node->seg, x) ) {
			node->up = delete_node(node->up, seg, x);
		}
		else {
			node->down = delete_node(node->down, seg, x);
		}
		return node;
	  }  
	}
}

int above(int seg, int x){
	Node* node = root;
	Node* parent_above = NULL;
 
	while (node != NULL and node->seg != seg){
		if( segment_above( seg, node->seg, x) ) {
			node = node->up;		
		}
		else {
			parent_above = node;
			node = node->down;
		}
	}
	if (node->up == NULL) {
		return (parent_above ? parent_above->seg : -1 ) ;
	}
	else {
		node = node->up;
		while (node->down != NULL)
			node = node->down;
		return node->seg;
	}
}
int below(int seg, int x){
	Node* node = root;
	Node* parent_below = NULL;
 
	while (node != NULL and node->seg != seg){
		if( segment_above( seg, node->seg, x) ) {
			parent_below = node;
			node = node->up;		
		}
		else {
			node = node->down;
		}
	}
	if (node->down == NULL)
		return (parent_below ? parent_below->seg : -1 ) ;
	else {
		node = node->down;
		while (node->up != NULL)
			node = node->up;
		return node->seg;
	}
}

struct Event{
	int x;
	int y;
	int seg;
	char is_left;
};

Event events[2*maxn];

void create_events(){
	int i;
	for(i=0 ; i<n; i++) {
		events[2*i].x = point[i].x;
		events[2*i].y = point[i].y;
		events[2*i].seg = i;
		if (point[i].x == point[ (i+1) % n].x )
			events[2*i].is_left = (point[i].y < point[ (i+1) % n].y );  
		else
			events[2*i].is_left = (point[i].x < point[ (i+1) % n].x );
		events[2*i+1].x = point[i].x;
		events[2*i+1].y = point[i].y;
		events[2*i+1].seg = (i-1+n) % n;
		if (point[i].x == point[ (i-1+n) % n].x )
			events[2*i+1].is_left = (point[i].y < point[ (i-1+n) % n].y );  
		else
			events[2*i+1].is_left = (point[i].x < point[ (i-1+n) % n].x );
	}
}
 
int cmp_points(const void* p, const void* q){
	int value;
	value =  ((Event*) p)->x - ((Event*) q)->x ;
	if (value != 0)
		return value;
	else
		return (((Event*) p)->is_left ? -1 : 1 ); 
}
bool solve(){
	
	Event* event;
	int seg, seg_above, seg_below;
	int dist_seg_above_below, dist_seg_segabove,dist_seg_segbelow;
	
	create_events();
	qsort( events, 2*n, sizeof(Event), cmp_points);	
	init_bin_tree();
	int intersections = 0;
	
	for(int e=0; e < 2*n; ++e){
		event = events + e;
		seg = event->seg;
		if( event->is_left ){
			root = inserNode(root, seg, event->x);
			seg_above = above( seg, event->x);
			seg_below = below( seg, event->x);
			dist_seg_segabove = abs(seg-seg_above);
			dist_seg_segbelow = abs(seg-seg_below);
			if(  (seg_above != -1 and (dist_seg_segabove > 1 and dist_seg_segabove < n-1) 
				and  intersect( point[seg], point[(seg+1)%n], point[seg_above], point[(seg_above+1)%n] ))
			  or (seg_below != -1 and (dist_seg_segbelow > 1 and dist_seg_segbelow < n-1) 
				and  intersect( point[seg], point[(seg+1)%n], point[seg_below], point[(seg_below+1)%n] ))  ) 
			{
				intersections++;
				break;
			}
		}
		else {
			seg_above = above( seg, event->x);
			seg_below = below( seg, event->x);
			dist_seg_above_below = abs(seg_below-seg_above);
			if(  (seg_above != -1 and  seg_below != -1 
				and (dist_seg_above_below > 1 and dist_seg_above_below < n-1) 
				and intersect( point[seg_below], point[(seg_below+1)%n], point[seg_above], point[(seg_above+1)%n] )) )
			{
				intersections++;
				break;
			}
			root = delete_node(root, seg, event->x);
		}
	}
	return intersections > 0;
}

int main(){
	while(cin >> n and n > 0) {
		for(int i=0; i<n; i++)  cin >> point[i].x >> point[i].y;
		if (solve() > 0) puts("NO");
		else puts("YES");
	}
	return 0;
}
