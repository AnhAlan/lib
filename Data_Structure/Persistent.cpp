template<typename T> 
struct Node { 
    int left, right; 
    T sum; 
    T lazy; 
    Node(int _left = 0, int _right = 0, T _sum = 0, T _lazy = 0) { 
        left = _left, right = _right; 
        sum = _sum; lazy = _lazy; 
    } 
}; 
template<typename T> 
struct Persistent { 
    vector<Node<T>> st; 
    Persistent(){ 
        st.emplace_back(); 
    } 
    int new_node(int old = 0) { 
        st.push_back(st[old]); 
        return (int) st.size() - 1; 
    } 
    void apply(int id, int l, int r, T val) { 
        st[id].sum += (val * (r - l + 1)); 
        st[id].lazy += val; 
    } 
    void push(int id, int l, int r) { 
        if (st[id].lazy == 0 || l == r) return; 
        int mid = (l + r) / 2; 
        int left = new_node(st[id].left); 
        int right = new_node(st[id].right); 
        apply(left, l, mid, st[id].lazy); 
        apply(right, mid + 1, r, st[id].lazy); 
        st[id].left = left; 
        st[id].right = right; 
        st[id].lazy = 0; 
    } 
    int build(int l, int r) { 
        // make sure have at least 1 node in vector 
        int id = new_node(); 
        if (l == r) { 
            st[id].sum = a[l]; 
            return id; 
        } 
        int mid = (l + r) / 2; 
        st[id].left = build(l, mid); 
        st[id].right = build(mid + 1, r); 
        st[id].sum = st[st[id].left].sum + st[st[id].right].sum;  
        return id; 
    } 
    int update(int old, int l, int r, int pos, T val) { 
        int id = new_node(old); 
        if (l == r) { 
            st[id].sum = val; 
            st[id].lazy = 0; 
            return id; 
        } 
        push(id, l, r); 
        int mid = (l + r) / 2; 
        if (pos <= mid) st[id].left = update(st[id].left, l, mid, pos, val); 
        else st[id].right = update(st[id].right, mid + 1, r, pos, val); 
        st[id].sum = st[st[id].left].sum + st[st[id].right].sum; 
        return id; 
    } 
    int update_range(int old, int l, int r, int u, int v, T val) { 
        if (l > v || r < u) return old; 
        int id = new_node(old); 
        if (l >= u && r <= v) { 
            apply(id, l, r, val); 
            return id; 
        } 
        push(id, l, r); 
        int mid = (l + r) / 2; 
        st[id].left = update_range(st[id].left, l, mid, u, v, val); 
        st[id].right = update_range(st[id].right, mid + 1, r, u, v, val); 
        st[id].sum = st[st[id].left].sum + st[st[id].right].sum; 
        return id; 
    } 
    // only get value dont make new node
    T get_range(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (u <= l && r <= v) {
            return st[id].sum;          
        }
        int mid = (l + r) >> 1;
        T res = get_range(st[id].left, l, mid, u, v) + get_range(st[id].right, mid + 1, r, u, v);
        int L = max(l, u);
        int R = min(r, v);
        if (L <= R) {
            res += st[id].lazy * (R - L + 1);
        }
        return res;
    }
}; 
 