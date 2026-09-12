struct Line {
    mutable long long a, b, p;
    Line(long long _a, long long _b, long long _p) : a(_a), b(_b), p(_p) {}
    bool operator < (const Line &other) const {return a < other.a; }
    bool operator < (long long t) const {return p < t; }
};
struct Line_container : multiset<Line, less<>> {
    static const long long inf = 1e18;
    void print() {
        for (const auto &line : *this) {
            cout << "y = " << line.a << "* x + " << line.b << " | p = " << (line.p == inf ? "INF" : to_string(line.p)) << "\n";
        }
    }
    long long div(long long a, long long b) {
        return a / b - ((a ^ b) < 0 && a % b != 0);
    }
    bool isect(iterator prev, iterator next) {
        if (next == end()) {
            prev->p = inf;
            return false;
        }
        if (prev->a == next->a) {
            prev->p = (prev->b > next->b ? inf : -inf);
        } else prev->p = div(next->b - prev->b, prev->a - next->a);
        return prev->p >= next->p;
    }
    void add(long long a, long long b) {
        auto cur = insert(Line(a, b, 0));
        auto next = cur; next++;
        auto prev = cur;
        while (isect(cur, next)) next = erase(next);
        if (prev != begin() && isect(--prev, cur)) isect(prev, erase(cur));
        while ((cur = prev) != begin() && (--prev)->p >= cur->p) {
            isect(prev, erase(cur));
        }
    }
    long long query(long long t) {
        assert(!empty());
        auto l = *lower_bound(t);
        return l.a * t + l.b;
    }
};