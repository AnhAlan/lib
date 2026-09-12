template<typename T>
struct Matrix {
    int n, m;
    vector<vector<T>> a;
    Matrix(int _n = 0, int _m = 0) {
        n = _n;
        m = _m;
        a.assign(n, vector<T>(m));
    }
    Matrix operator + (const Matrix &other) const {
        assert(n == other.n && m == other.m);
        Matrix res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.a[i][j] = a[i][j] + other.a[i][j];
                //if (res.a[i][j] >= mod) res.a[i][j] -= mod;
            }
        }
        return res;
    }
    Matrix operator * (const Matrix &other) const {
        assert(m == other.n);
        Matrix res(n, other.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < other.m; k++) {
                    res.a[i][k] += a[i][j] * other.a[j][k];
                    //if (res.a[i][k] >= 1LL * mod * mod) res.a[i][k] -= 1LL * mod * mod;
                }
            }
        }
        return res;
    }
    Matrix operator ^ (long long k) const {
        assert(n == m);
        Matrix res(n, n);
        for (int i = 0; i < n; i++) {
            res.a[i][i] = 1;
        }
        Matrix mul = *this;
        while (k > 0) {
            if (k & 1) {
                res = res * mul;
            }
            mul = mul * mul;
            k >>= 1;
        }
        return res;
    }
};