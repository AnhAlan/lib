double PI = acos(-1.0);
template<class T>
int sgn(T x) {return (x > 0) - (x < 0);}
template<class T>
struct Point {
    T x, y;
    explicit Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    bool operator == (const Point &o) const {return sgn(x - o.x) == 0 && sgn(y - o.y) == 0;}
    bool operator != (const Point &o) const {return !(o == *this);}
    bool operator < (const Point &o) const {return sgn(x - o.x) ? sgn(x - o.x) < 0 : (y - o.y) < 0;}
    bool operator > (const Point &o) const {return o < *this;}
    bool operator <= (const Point &o) const {return !(*this > o);}
    bool operator >= (const Point &o) const {return !(*this < o);}
    Point operator - (const Point &o) const {return Point(x - o.x, y - o.y);}
    Point operator + (const Point &o) const {return Point(x + o.x, y + o.y);}
    Point operator * (T k) const {return Point(x * k, y * k);}
    Point operator / (T k) const {return Point(x / k, y / k);}
    T len2() const {return (x * x) + (y * y);}
    double len() const {return sqrt((double)len2());}
    T dist2(const Point &o) const {return (*this - o).len2();}
    double dist(const Point &o) const {return sqrt((double)dist2(o));}
    T dot(const Point &o) const {return x * o.x + y * o.y;}
    T cross(const Point &o) const {return (x * o.y) - (o.x * y);}
    // return radian [-pi, pi]
    double angle() const {return atan2l((double)y, (double)x);}
    static double angle(const Point &a, const Point &b) {
        return atan2l((double)a.cross(b), (double)a.dot(b));
    }
    double degree() const {return angle() * (180.0 / PI);}
    // rad > 0: rotate ccw. < 0 cw
    Point rotate(double radian) const {
        double c = cosl(radian), s = sinl(radian);
        return Point((double)x * c - (double)y * s, (double)x * s + (double)y * c);
    } 
    Point rotate(const Point &o, double radian) const {
        return (*this - o).rotate(radian) + o;
    }
    Point unit() {return *this / len();}
    // center = total point of hull / size
    static bool polar_cmp(const Point &a, const Point &b, const Point &center = Point(0, 0)) {
        Point ca = a - center;
        Point cb = b - center;
        auto quad = [](const Point &p) {
            return (sgn(p.y) > 0 || (sgn(p.y) == 0 && sgn(p.x) > 0)) ? 1 : 0;
        };
        int qa = quad(ca);
        int qb = quad(cb);
        if (qa != qb) return qa > qb;
        T cr = ca.cross(cb);
        if (sgn(cr) != 0) return cr > 0; 
        return ca.len2() < cb.len2(); 
    }
    friend ostream& operator<<(ostream& os, Point p) {
		return os << "(" << p.x << "," << p.y << ")"; 
    }
};