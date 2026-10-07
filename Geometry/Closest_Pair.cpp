long double brute_force(vector<P> &P, int l, int r) {
    double ans = 1e18;
    for (int i = l; i <= r; i++) {
        for (int j = i+1; j <= r; j++) {
            ans = min(ans, P[i].dist(P[j]));
        }
    }
    return ans;
}
long double close(vector<P> &Px, vector<P> &Py, int l, int r) {
    int n = r - l + 1;
    if (n <= 3) return brute_force(Px, l, r);
    int mid = (l + r) / 2;
    long double midx = Px[mid].x;
    vector<P> Pyl, Pyr;
    for (auto &p : Py) {
        if (p.x <= midx) Pyl.push_back(p);
        else Pyr.push_back(p);
    }
    double dl = close(Px, Pyl, l, mid);
    double dr = close(Px, Pyr, mid+1, r);
    double d = min(dl, dr);
    vector<P> strip;
    for (auto &p : Py) {
        if (fabs(p.x - midx) < d) strip.push_back(p);
    }
    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i+1; j < (int)strip.size() && j <= i+7; j++) {
            d = min(d, strip[i].dist(strip[j]));
        }
    }
    return d;
}
long double close_pair(const vector<P> &p) {
    int n = (int) p.size();
    vector<P> px = p, Py = p;
    sort(px.begin(), px.end(), [](const P &a, const P &b){ return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](const P &a, const P &b){ return a.y < b.y; });
    return close(px, Py, 0, n - 1);
}