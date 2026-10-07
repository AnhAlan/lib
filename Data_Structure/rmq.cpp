template<class X>
X merge(const X &x, const X &y) {
    return max(x, y);
    // return min(x, y);
}
template<typename T>
struct Rmq {
    int n;
    int LOG;
    vector<vector<T>> rmq;
    Rmq() {}
    void init(int _n, const vector<int> &a) {
        n = _n;
        assert(n >= 1);
        LOG = 31 - __builtin_clz(n) + 1;
        rmq.assign(n + 1, vector<T>(LOG));
        for (int i = 1; i <= n; i++) {
            rmq[i][0] = a[i];
        }
        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                rmq[i][j] = merge(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T get(int l, int r) {
        assert(l <= r && l >= 1 && r <= n);
        int k = 31 - __builtin_clz(r - l + 1);
        return merge(rmq[l][k], rmq[r - (1 << k) + 1][k]);
    }
};