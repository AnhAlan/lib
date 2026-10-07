template<typename T>
struct Node {
    T mn, mx;
    Node() {
        mn = numeric_limits<T>::max();
        mx = numeric_limits<T>::lowest();
    }
    Node(T val) {
        mn = mx = val;
    }
};
template<typename T>
Node<T> merge(const Node<T> &A, const Node<T> &B) {
    Node<T> res;
    res.mn = min(A.mn, B.mn);
    res.mx = max(A.mx, B.mx);
    return res;
}
template<typename T>
Node<T> none() {
    return Node<T>();
}
template<typename T>
struct Lca {
    int n, LOG;
    vector<vector<int> > par;
    vector<vector<Node<T> > > lca_edges;
    vector<int> high;
    vector<bool> vis;
    Lca() {}
    void init() {
        n = g.n;
        assert(n > 0);
        LOG = 32 - __builtin_clz(n);
        par.assign(n + 1, vector<int>(LOG + 1, 0));
        lca_edges.assign(n + 1, vector<Node<T> >(LOG + 1, none<T>()));
        high.assign(n + 1, 0);
        vis.assign(n + 1, false);
    }
    void dfs(int u) {
        vis[u] = true;
        for(int id : g.adj[u]) {
            int v = g.edges[id].from ^ g.edges[id].to ^ u;
            if(v == par[u][0]) continue;
            lca_edges[v][0] = Node<T>(g.edges[id].cost);
            par[v][0] = u;
            high[v] = high[u] + 1;
            dfs(v);
        }
    }
    void build() {
        high[0] = -1;
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                high[i] = 0;
                par[i][0] = 0;
                lca_edges[i][0] = none<T>();
                dfs(i);
            }
        }
        for(int j = 1; j <= LOG; j++) {
            for(int i = 1; i <= n; i++) {
                if(par[i][j - 1] != 0) {
                    int p = par[i][j - 1];
                    par[i][j] = par[p][j - 1];
                    lca_edges[i][j] = merge(lca_edges[i][j - 1],lca_edges[p][j - 1]);
                }
                else {
                    par[i][j] = 0;
                    lca_edges[i][j] = none<T>();
                }
            }
        }
    }
    int lca(int u, int v) {
        if(high[u] < high[v]) swap(u, v);
        for(int i = LOG; i >= 0; i--) {
            if(par[u][i] != 0 &&
               high[par[u][i]] >= high[v]) {

                u = par[u][i];
            }
        }
        if(u == v) return u;
        for(int i = LOG; i >= 0; i--) {
            if(par[u][i] != par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[u][0];
    }
    Node<T> get_path(int u, int v) {
        Node<T> res = none<T>();
        if(high[u] < high[v]) swap(u, v);
        for(int i = LOG; i >= 0; i--) {
            if(par[u][i] != 0 && high[par[u][i]] >= high[v]) {
                res = merge(res, lca_edges[u][i]);
                u = par[u][i];
            }
        }
        if(u == v) return res;
        for(int i = LOG; i >= 0; i--) {
            if(par[u][i] != par[v][i]) {
                res = merge(res, lca_edges[u][i]);
                res = merge(res, lca_edges[v][i]);
                u = par[u][i];
                v = par[v][i];
            }
        }
        res = merge(res, lca_edges[u][0]);
        res = merge(res, lca_edges[v][0]);
        return res;
    }
};