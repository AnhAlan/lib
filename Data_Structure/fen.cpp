template<typename T>
struct Fenwick{
    int n;
    vector<T> bit;
    Fenwick(){}
    Fenwick(int _n){
        n = _n;
        bit.assign(n + 1, 0);
    }
    void update(int i, T v){
        for (; i <= n; i += (i & -i)){
            bit[i] += v;
        }
    }
    T get(int i){
        T res = 0;
        for (; i > 0; i -= (i & -i)){
            res += bit[i];
        }
        return res;
    }
    T get_range(int l, int r){
        assert(l > 0);
        if(l > r) return 0;
        return get(r) - get(l - 1);
    }
    T kth(int k) {
        int pos = 0;
        int LOG = __lg(n);
        for (int i = LOG; i >= 0; i--) {
            int nxt = pos + (1 << i);
            if (nxt <= n && bit[nxt] < k) {
                pos = nxt;
                k -= bit[nxt];
            }
        }
        return pos + 1;
    }
};