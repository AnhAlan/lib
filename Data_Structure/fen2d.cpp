template<typename T>
struct FenWick2D{
    int n, m;
    vector<vector<T> > bit;
    FenWick2D(){}
    FenWick2D(int _n, int _m) : n(_n), m(_m), bit(_n + 2, vector<T>(_m + 2, 0)) {}
    void update(int x, int y, T v) { 
        for(int i = x; i <= n; i += (i & -i)){
            for(int j = y; j <= m; j += (j & -j)){
                bit[i][j] += v;
            }
        }
    }
    T get(int x, int y) { 
        T res = 0;
        for(int i = x; i > 0; i -= (i & -i)){
            for(int j = y; j > 0; j -= (j & -j)){
                res += bit[i][j];
            }
        }
        return res;
    }
    T get_range(int x1, int y1, int x2, int y2) { 
        return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
    }
};