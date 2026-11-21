struct Spf {
    int n;
    vector<int> spf;
    Spf(int _n) {
        n = _n;
        assert(n <= (int) 1e6);
        spf.assign(n + 1, 0);
    }
    void build() {
        for (int i = 2; 1LL * i * i <= n; i++) {
            if (spf[i] == 0) {
                for (int j = i * i; j <= n; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) spf[i] = i;
        }
    }
    vector<pair<int,int>> factor(int x) {
        vector<pair<int,int>> res;
        while (x > 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            res.push_back({p, cnt});
        }
        return res;
    }
};