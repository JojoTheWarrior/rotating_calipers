#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ld, ld> pd;
typedef vector<int> vi;
#define F first
#define S second

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

using P = Point<ld>;
using Event = pair<ld, int>;

const int MM = 2000;

int N;
P C[MM+1];
ld rad[MM+1];
ld EPS = 1e-9;

const ld PI = acosl(-1.0L);
const ld TWO_PI = 2.0L * PI;

ld fitInRange(ld theta){
    theta = fmodl(theta, TWO_PI);
    if (theta < 0) theta += TWO_PI;
    return theta;
}

void add_circular_interval(ld L, ld R, vector<Event> &ivts, int &initially_active){
    L = fitInRange(L);
    R = fitInRange(R);

    if (L <= R){
        ivts.push_back({L, 1});
        ivts.push_back({R, -1});
    } else {
        ++initially_active;
        ivts.push_back({R, -1});
        ivts.push_back({L, 1});
    }
}

void solve(){
    cin >> N;

    for (int i = 1; i <= N; i++) cin >> C[i].x >> C[i].y >> rad[i];

    // trying all
    int ans = 1;
    
    for (int i = 1; i <= N; i++){
        vector<Event> evts;
        int initially_active = 0;
        for (int j = 1; j <= N; j++){
            if (i == j) continue;
            P delta = C[j] - C[i];
            ld D = delta.dist();
            ld alpha = atan2l(delta.y, delta.x);
            assert(rad[j] - rad[i] < D);
            ld b = acosl((rad[i] - rad[j]) / D);
            ld a = acosl((rad[j] + rad[i]) / D);
            add_circular_interval(alpha + a, alpha + b, evts, initially_active);
            add_circular_interval(alpha - b, alpha - a, evts, initially_active);
        }
        sort(evts.begin(), evts.end(), [](Event a, Event b){
            if (a.F != b.F) return a.F < b.F;
            return a.S > b.S;
        });
        ld pv = -69420; int cur_cnt = initially_active + 1;
        for (auto [t, d] : evts){
            if (d == 1){
                cur_cnt++;
                ans = max(ans, cur_cnt);
            } else {
                ans = max(ans, cur_cnt);
                cur_cnt--;
            }
        }
    }
    
    cout << ans << "\n";
}

int main(){
    int T;
    cin >> T;
    for (; T > 0; T--) solve();
}