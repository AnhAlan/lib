const int mod1 = 1e9 + 7, mod2 = 998244353;
const int base1 = 256, base2 = 512;
pair<int, int> pw[maxn], has[maxn];
void build(int n) {
    pw[0] = {1, 1};
    has[0] = {0, 0};
    for (int i = 1; i <= n; i++) {
        pw[i].fi = 1ll * pw[i - 1].fi * base1 % mod1;
        pw[i].se = 1ll * pw[i - 1].se * base2 % mod2;
        has[i].fi = (1ll * has[i - 1].fi * base1 + a[i]) % mod1;
        has[i].se = (1ll * has[i - 1].se * base2 + a[i]) % mod2;
    }
}
pair<int, int> get_hash(int l, int r) {
    pair<int, int> res;
    res.fi = (has[r].fi - 1ll * has[l - 1].fi * pw[r - l + 1].fi % mod1 + mod1) % mod1;
    res.se = (has[r].se - 1ll * has[l - 1].se * pw[r - l + 1].se % mod2 + mod2) % mod2;
    return res;
}