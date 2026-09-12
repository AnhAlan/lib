template<typename T, typename F = Merge<T>>
struct Hld {
    const Forest<T> &f;
    Segtree<T, F> st; 
    F merge;         
    int n;
    vector<int> par, high;
    vector<int> heavy, head, pos;
    vector<int> sz;
    vector<int> edge_to_node;
    vector<int> par_id;
    int cur_pos;

    Hld(const Forest<T> &_f) : f(_f), n(_f.n) {
        st = Segtree<T, F>(n);
        par.assign(n + 1, 0);
        high.assign(n + 1, 0);
        heavy.assign(n + 1, 0);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        par_id.assign(n + 1, 0);
        edge_to_node.assign(f.edges.size() + 5, 0);
        cur_pos = 0;
    }

    void dfs(int u, int p) {
        sz[u] = 1;
        par[u] = p;
        heavy[u] = 0;
        int maxSz = 0;
        for (int id : f.adj[u]) {
            int v = f.edges[id].from ^ f.edges[id].to ^ u;
            if (v == p) continue;
            high[v] = high[u] + 1;
            par_id[v] = id;
            edge_to_node[id] = v;
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > maxSz) {
                maxSz = sz[v];
                heavy[u] = v;
            }
        }
    }

    void dfs_hld(int u, int h) {
        head[u] = h;
        pos[u] = ++cur_pos;
        if (heavy[u]) {
            dfs_hld(heavy[u], h);
        }
        for (int id : f.adj[u]) {
            int v = f.edges[id].from ^ f.edges[id].to ^ u;
            if (v == par[u] || v == heavy[u]) continue;
            dfs_hld(v, v);
        }
    }

    void build(int root = 1) {
        high[root] = 0;
        dfs(root, 0);
        dfs_hld(root, root);
    }

    void build_node(const vector<T> &a) {
        vector<T> v(n + 1); 
        for (int i = 1; i <= n; i++) {
            v[pos[i]] = a[i];
        }
        st.build(1, 1, n, v);
    }

    void build_edges() {
        vector<T> v(n + 1);
        for (int i = 1; i <= n; i++) {
            if (par_id[i] != 0) {
                int id = par_id[i];
                v[pos[i]] = f.edges[id].cost;
            }
        }
        st.build(1, 1, n, v);
    }

    Node<T> get_node(int u, int v) {
        Node<T> res = merge.none(); 
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            res = merge(res, st.get_range(1, 1, n, pos[head[u]], pos[u]));
            u = par[head[u]];
        }
        if (high[u] > high[v]) swap(u, v);
        res = merge(res, st.get_range(1, 1, n, pos[u], pos[v]));
        return res;
    }

    void update_node_range(int u, int v, T w) {
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            st.update_range(1, 1, n, pos[head[u]], pos[u], w);
            u = par[head[u]];
        }
        if (high[u] > high[v]) swap(u, v);
        st.update_range(1, 1, n, pos[u], pos[v], w);
    }

    void update_node_point(int u, T w) {
        st.update_range(1, 1, n, pos[u], pos[u], w);
    }

    Node<T> get_edges(int u, int v) {
        Node<T> res = merge.none(); 
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            res = merge(res, st.get_range(1, 1, n, pos[head[u]], pos[u]));
            u = par[head[u]];
        }
        if (u == v) return res;
        if (high[u] > high[v]) swap(u, v);
        res = merge(res, st.get_range(1, 1, n, pos[u] + 1, pos[v]));
        return res;
    }

    void update_edges_range(int u, int v, T w) {
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            st.update_range(1, 1, n, pos[head[u]], pos[u], w);
            u = par[head[u]];
        }
        if (u == v) return;
        if (high[u] > high[v]) swap(u, v);
        st.update_range(1, 1, n, pos[u] + 1, pos[v], w);
    }

    void update_edge_point(int edge_id, T w) {
        int u = edge_to_node[edge_id];
        st.update_range(1, 1, n, pos[u], pos[u], w);
    }
};