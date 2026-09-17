#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define nx(i) (i+1)%n
#define pv(i) (i-1+n)%n
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

int sign(ll num) {
    if (num < 0) return -1;
    else if (num == 0) return 0;
    else return 1;
}

using P = Point<long double>;

vector<pii> all_anti_podal(int n, vector<P> &p){
    int p1 = 0, p2 = 0;
    vector<pii> result;

    vector<bool> vis(n, false);

    for (; p1 < n; p1++){
        P base = p[nx(p1)] - p[p1];

        while (p2 == p1 || p2 == nx(p1) || sign(base.cross(p[nx(p2)] - p[p2])) == sign(base.cross(p[p2] - p[pv(p2)])))
            p2 = nx(p2);
        
        if (vis[p1]) continue;
        vis[p1] = true;

        result.pb({p1, p2});
        result.pb({nx(p1), p2});

        // case where both edges from p1 and p2 are parallel
        if (base.cross(p[nx(p2)] - p[p2]) == 0){
            result.pb({p1, nx(p2)});
            result.pb({nx(p1), nx(p2)});
            vis[p2] = true;
        }
    }

    return result;
}