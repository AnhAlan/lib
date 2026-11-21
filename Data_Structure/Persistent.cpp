template<typename T>
struct Node {
    Node *left, *right;
    T sum, lazy;
    explicit Node(Node* _l = nullptr, Node* _r = nullptr, T _s = 0, T _lz = 0)
        : left(_l), right(_r), sum(_s), lazy(_lz) {}
};

template<typename T>
struct Persistent {
    vector<Node<T>> st;
    Node<T>* null_node;
    int n;
    int cnt;
    Persistent() {}
    void init(int _n, int q) {                               
        n = _n;
        cnt = 0;
        int len = 1;
        while ((1ll << len) < n) len++;
        st.resize(2ll * n + 1ll * q * 8 * (len + 1) + 5);      
        null_node = create();
        null_node->left = null_node->right = null_node;    
    }
    Node<T>* create(Node<T>* old = nullptr) {
        if (old == nullptr) st[cnt] = Node<T>();
        else st[cnt] = *old;                                   
        return &st[cnt++];
    }
    void apply(Node<T>* id, int l, int r, T val) {
        id->sum += val * (r - l + 1);
        id->lazy += val;
    }
    void push(Node<T>* id, int l, int r) {
        if (id->lazy == 0 || l == r) return;
        int mid = (l + r) >> 1;
        id->left  = create(id->left);
        id->right = create(id->right);
        apply(id->left,  l, mid, id->lazy);
        apply(id->right, mid + 1, r, id->lazy);
        id->lazy = 0;
    }
    Node<T>* build(int l, int r) {
        Node<T>* id = create();
        if (l == r) {
            id->sum = a[l];
            return id;
        }
        int mid = (l + r) >> 1;
        id->left  = build(l, mid);
        id->right = build(mid + 1, r);
        id->sum = id->left->sum + id->right->sum;
        return id;
    }
    Node<T>* update(Node<T>* old, int l, int r, int pos, T val) {
        Node<T>* id = create(old);
        if (l == r) {
            id->sum = val;
            id->lazy = 0;
            return id;
        }
        push(id, l, r);
        int mid = (l + r) >> 1;
        if (pos <= mid)
            id->left = update(id->left, l, mid, pos, val);
        else
            id->right = update(id->right, mid + 1, r, pos, val);
        id->sum = id->left->sum + id->right->sum;
        return id;
    }
    Node<T>* update_range(Node<T>* old, int l, int r, int u, int v, T val) {
        if (l > v || r < u) return old;
        Node<T>* id = create(old);
        if (u <= l && r <= v) {
            apply(id, l, r, val);
            return id;
        }
        push(id, l, r);
        int mid = (l + r) >> 1;
        id->left  = update_range(id->left,  l, mid, u, v, val);
        id->right = update_range(id->right, mid + 1, r, u, v, val);
        id->sum = id->left->sum + id->right->sum;
        return id;
    }
    T get(Node<T>* id, int l, int r, int u, int v) {
        if (!id || l > v || r < u) return 0;
        if (u <= l && r <= v) return id->sum;
        int L = max(l, u), R = min(r, v);
        T res = 0;
        if (L <= R) res += id->lazy * (R - L + 1);
        int mid = (l + r) >> 1;
        res += get(id->left,  l, mid, u, v);
        res += get(id->right, mid + 1, r, u, v);
        return res;
    }
    Node<T>* build() { return build(1, n); }
    Node<T>* update(Node<T>* root, int pos, T val) {
        return update(root, 1, n, pos, val);
    }
    Node<T>* update_range(Node<T>* root, int l, int r, T val) {
        return update_range(root, 1, n, l, r, val);
    }
    T get(Node<T>* root, int l, int r) {
        return get(root, 1, n, l, r);
    }
};