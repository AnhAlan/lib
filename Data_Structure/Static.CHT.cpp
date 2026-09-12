struct Line {
    long long x, a, b;
    Line(long long _x = 0, long long _a = 0, long long _b = 0) : x(_x), a(_a), b(_b) {}
    bool operator < (const Line &other) const {
        return x < other.x;
    }
};
struct Convex_hull {
    static constexpr long long inf = 2e18;
    vector<Line> line;
    Convex_hull() {}
    long long dvi(long long a, long long b) {
        return a / b - ((a ^ b) < 0 && a % b != 0);
    }
    void add_line(long long a, long long b) {
        while (!line.empty()) {
            long long lx = line.back().x;
            long long la = line.back().a;
            long long lb = line.back().b;
            if (lx * la + lb <= lx * a + b) {
                line.pop_back();
            } else {
                break;
            }
        }
        if (line.empty()) {
            line.push_back(Line(-inf, a, b));
            return;
        }
        long long la = line.back().a;
        long long lb = line.back().b;
        if (la == a) {
            if (b <= lb) return; 
            line.pop_back();    
            if (line.empty()) {
                line.push_back(Line(-inf, a, b));
                return;
            }
            la = line.back().a;
            lb = line.back().b;
        }
        long long inter = dvi(lb - b, a - la);
        line.push_back(Line(inter, a, b));
    }
    long long query(long long t) {
        int id = int(upper_bound(line.begin(), line.end(), Line(t)) - line.begin() - 1);
        return line[id].a * t + line[id].b;
    }
};
