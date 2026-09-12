template<typename T>
struct Fenwick{
    int n;
    vector<T> bit_mul, bit_add;
    Fenwick(){}
    Fenwick(int _n){
        n = _n;
        bit_mul.assign(n + 2, 0);
        bit_add.assign(n + 2, 0);
    }
    void update(vector<T> &bit, int i, T v){
        for(; i <= n; i += (i & -i)) bit[i] += v;
    }
    T get(vector<T> &bit, int i){
        T res = 0;
        for(; i > 0; i -= (i & -i)) res += bit[i];
        return res;
    }
    void update_range(int l, int r, T v){
        update(bit_mul, l, v);
        update(bit_mul, r + 1, -v);
        update(bit_add, l, -v * (l - 1));
        update(bit_add, r + 1, v * r);
    }
    T get_prefix(int x){
        return get(bit_mul, x) * x + get(bit_add, x);
    }
    T get_range(int l, int r){
        return get_prefix(r) - get_prefix(l - 1);
    }
};