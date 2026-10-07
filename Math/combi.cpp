struct Combi {
    int maxn;
    int mod = 1e9 + 7;
    vector<long long> fac, inv;
    Combi(int _maxn) {
        maxn = _maxn;
        fac.resize(maxn + 1);
        inv.resize(maxn + 1);
    }
    long long pow_mod(long long a, long long b) {
        long long res = 1;
        a %= mod;
        while (b) {
            if (b & 1) {
                res = res * a % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
    void build() {
        fac[0] = 1;
        for (int i = 1; i <= maxn; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
        inv[maxn] = pow_mod(fac[maxn], mod - 2);
        for (int i = maxn; i >= 1; i--) {
            inv[i - 1] = inv[i] * i % mod;
        }
    }
    long long C(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * inv[k] % mod * inv[n - k] % mod;
    }
    long long A(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * inv[n - k] % mod;
    }
};