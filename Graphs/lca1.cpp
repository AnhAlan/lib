struct Lca{
    int n, cnt, LOG;
    vector<int> high, in, out, node;
    vector<vector<int> > min_h;
    vector<int> comp;
    vector<bool> vis;
    vector<vector<int>> st;
    Lca() {}
    void init() {
        n = g.n;
        assert(n > 0);
        LOG = 32 - __builtin_clz(2 * n + 5);
        cnt = 0;
        high.assign(n + 1, 0);
        node.assign(2 * n + 5, 0);
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
        comp.assign(n + 1, 0);
        min_h.assign(2 * n + 5, vector<int>(LOG + 1, 0));
        vis.assign(n + 1, false);
        st.assign(n + 1, vector<int>(LOG + 1));
    }
    void dfs(int u, int p, int cid){
        comp[u] = cid;
        vis[u] = true;
        node[++cnt] = u;
        in[u] = cnt;
        for(int id : g.adj[u]){
            int v = g.edges[id].from ^ g.edges[id].to ^ u;
            if(v == p) continue;
            high[v] = high[u] + 1;
            dfs(v, u, cid);
            node[++cnt] = u;
        }
        out[u] = cnt;
    }
    int min_high(int u, int v){
        return high[u] < high[v] ? u : v;
    }
    void build(){
        high[0] = -1;
        int cid = 0;
        for(int i = 1; i <= n; i++){
            if(!vis[i]){
                high[i] = 0;
                dfs(i, -1, ++cid);
            }
        }
        for(int i = 1; i <= cnt; i++){
            min_h[i][0] = node[i];
        }
        for(int j = 1; j <= LOG; j++){
            for(int i = 1; i + (1 << j) - 1 <= cnt; i++){
                min_h[i][j] = min_high(
                    min_h[i][j - 1],
                    min_h[i + (1 << (j - 1))][j - 1]
                );
            }
        }
        for (int i = 1; i <= n; i++) {
            st[i][0] = i;
        }
        for (int j = 1; j <= LOG; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                st[i][j] = lca(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int lca(int u, int v){
        assert(comp[u] == comp[v]);
        int pu = in[u];
        int pv = in[v];
        if(pu > pv) swap(pu, pv);
        int len = pv - pu + 1;
        int k = 31 - __builtin_clz(len);
        return min_high(
            min_h[pu][k],
            min_h[pv - (1 << k) + 1][k]
        );
    }
    int range_lca(int l, int r) {
        int len = r - l + 1;
        int k = __lg(len);
        return lca(st[l][k], st[r - (1 << k) + 1][k]);
    }
};