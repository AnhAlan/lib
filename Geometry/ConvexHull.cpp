template<typename T>
vector<Point<T>> convex_hull(vector<Point<T>> p) {
    int n = (int)p.size();
    if (n <= 2) return p;
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    n = (int)p.size();
    if (n <= 2) return p;
    vector<Point<T>> ch(2 * n); 
    int sz = 0;
    for (int i = 0; i < n; i++) {
        while (sz >= 2 && sgn((ch[sz - 1] - ch[sz - 2]).cross(p[i] - ch[sz - 2])) <= 0) {
            sz--;
        }
        ch[sz++] = p[i];
    }
    int t = sz;
    for (int i = n - 2; i >= 0; i--) {
        while (sz > t && sgn((ch[sz - 1] - ch[sz - 2]).cross(p[i] - ch[sz - 2])) <= 0) {
            sz--;
        }
        ch[sz++] = p[i];
    }
    ch.resize(sz - 1); 
    return ch;
}