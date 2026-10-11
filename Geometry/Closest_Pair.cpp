long long brute_force(vector<P> &p, int l, int r) {
    long long ans = LLONG_MAX;
    for (int i = l; i <= r; i++) {
        for (int j = i+1; j <= r; j++) {
            ans = min(ans, p[i].dist2(p[j]));
        }
    }
    return ans;
}
long long close(vector<P> &Px, vector<P> &Py, int l, int r) {
    int n = r - l + 1;
    if (n <= 3) return brute_force(Px, l, r);
    int mid = (l + r) / 2;
    long long midx = Px[mid].x;
    vector<P> Pyl, Pyr;
    for (auto &p : Py) {
        if (p.x <= midx) Pyl.push_back(p);
        else Pyr.push_back(p);
    }
    long long dl = close(Px, Pyl, l, mid);
    long long dr = close(Px, Pyr, mid+1, r);
    long long d = min(dl, dr);
    vector<P> strip;
    for (auto &p : Py) {
        long long dx = llabs(p.x - midx);
        if (dx * dx < d) strip.push_back(p);
    }
    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i+1; j < (int)strip.size() && j <= i+7; j++) {
            d = min(d, strip[i].dist2(strip[j]));
        }
    }
    return d;
}
long long close_pair(const vector<P> &p) {
    int n = (int) p.size();
    vector<P> px = p, Py = p;
    sort(px.begin(), px.end(), [](const P &a, const P &b){ return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](const P &a, const P &b){ return a.y < b.y; });
    return close(px, Py, 0, n - 1);
}
