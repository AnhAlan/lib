template<typename T>
struct Node {
    T sum, pref, suff, best;
    bool is_null; 
    Node() : sum(0), pref(0), suff(0), best(0), is_null(true) {}
    Node(T val) {
        sum = val;
        pref = suff = best = max(T(0), val);
        is_null = false;
    }
};

template<typename T>
struct Merge {
    Node<T> operator()(const Node<T> &a, const Node<T> &b) const {
        if (a.is_null) return b;
        if (b.is_null) return a;
        Node<T> res;
        res.is_null = false;
        res.sum = a.sum + b.sum;
        res.pref = max(a.pref, a.sum + b.pref);
        res.suff = max(b.suff, b.sum + a.suff);
        res.best = max({a.best, b.best, a.suff + b.pref});
        return res;
    }
    static Node<T> none() { 
        return Node<T>();
    }
};

template<typename T, typename F = Merge<T>>
struct Segtree {
    int n;
    F merge;
    vector<Node<T>> seg;
    Segtree(int _n = 0) {
        n = _n;
        seg.assign(4 * n + 5, F::none());
    }
    void build(int id, int l, int r, const vector<T> &a) {
        if (l == r) {
            seg[id] = Node<T>(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid, a);
        build(id * 2 + 1, mid + 1, r, a);
        seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
    }
    
    // only update 1 point
    void update(int id, int l, int r, int pos, T v){
        if(l == r){
            seg[id] = Node<T>(v); 
            return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid) update(id * 2, l, mid, pos, v);
        else update(id * 2 + 1, mid + 1, r, pos, v); 
        seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
    }
    Node<T> get_range(int id, int l, int r, int u, int v) {
        if (r < u || l > v) return F::none(); 
        if (u <= l && r <= v) return seg[id];
        int mid = (l + r) / 2;
        Node<T> left = get_range(id * 2, l, mid, u, v);
        Node<T> right = get_range(id * 2 + 1, mid + 1, r, u, v);
        return merge(left, right);
    }
    /*
        Segtree<long long, Merge<long long>> st(n);
    */
};