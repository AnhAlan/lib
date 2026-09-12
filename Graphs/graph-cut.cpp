template<typename T>
struct Graph_cut {
    const Undigraph<T> &g;
    int n, m, LOG, cnt;
    vector<int> low, num, in, out, high, num_child, dsu;
    vector<bool> is_bridge, is_cut;
    vector<vector<int>> par;
    vector<tuple<int, int, int>> sort_edges;
    int cnt_bridge, cnt_cut;
    Graph_cut(const Undigraph<T> &_g) : g(_g) {
        n = g.n;
        m = (int) g.edges.size();
        LOG = __lg(n) + 1;
        cnt = 0;
        low.resize(n + 1);
        num.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        high.resize(n + 1);
        num_child.resize(n + 1);
        dsu.assign(n + 1, -1);
        is_bridge.assign(m + 1, false);
        is_cut.assign(n + 1, false);
        par.assign(n + 1, vector<int>(LOG + 1));
        cnt_bridge = cnt_cut = 0;
    }
    int find(int u) {
        return dsu[u] < 0 ? u : dsu[u] = find(dsu[u]);
    }
    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (dsu[u] > dsu[v]) swap(u, v);
        dsu[u] += dsu[v];
        dsu[v] = u;
        return true;
    }

    void dfs(int u, int par_id) {
        low[u] = num[u] = ++cnt;
        in[u] = cnt;
        for (int id : g.adj[u]) {
            if (id == par_id) continue;
            int v = g.edges[id].from ^ g.edges[id].to ^ u;
            if (!num[v]) {
                par[v][0] = u;
                high[v] = high[u] + 1;
                num_child[u]++;
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if (par[u][0] != 0 && low[v] >= num[u]) {
                    is_cut[u] = true;
                    cnt_cut++;
                }
                if (low[v] > num[u]) {
                    is_bridge[id] = true;
                    cnt_bridge++;
                }
            } else {
                low[u] = min(low[u], num[v]);
            }
        }
        out[u] = cnt;
    }

    void build() {
        for (int i = 0; i < m; i++) {
            int u = g.edges[i].from;
            int v = g.edges[i].to;
            if (u > v) swap(u, v);
            sort_edges.push_back(make_tuple(u, v, i));
            unite(u, v);
        }
        sort(sort_edges.begin(), sort_edges.end());
        for (int u = 1; u <= n; u++) {
            if (!num[u]) {
                dfs(u, -1);
                if (num_child[u] >= 2) {
                    if (!is_cut[u]) {
                        cnt_cut++;
                        is_cut[u] = true;
                    }
                }
            }
        }
        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                if (par[i][j - 1]) {
                    par[i][j] = par[par[i][j - 1]][j - 1];
                }
            }
        }
    }

    bool in_subtree(int u, int v) {
        return num[u] <= num[v] && num[v] <= out[u];
    }

    int jump(int u, int k) {
        for (int j = LOG - 1; j >= 0; j--) {
            if ((1 << j) <= k) {
                u = par[u][j];
                k -= (1 << j);
            }
        }
        return u;
    }

    bool check_cut(int u, int v, int cut) {
        if (find(u) != find(v)) return false;
        if (!is_cut[cut]) return true;
        if (u == cut || v == cut) return false;
        int child_u = (in_subtree(cut, u) ? jump(u, high[u] - high[cut] - 1) : -1);
        int child_v = (in_subtree(cut, v) ? jump(v, high[v] - high[cut] - 1) : -1);
        if (child_u > 0 && low[child_u] < num[cut]) child_u = -1;
        if (child_v > 0 && low[child_v] < num[cut]) child_v = -1;
        return child_u == child_v;
    }

    bool check_bridge(int u, int v, int cut_u, int cut_v) {
        if (find(u) != find(v)) return false;
        if (cut_u > cut_v) swap(cut_u, cut_v);
        auto it = lower_bound(sort_edges.begin(), sort_edges.end(), make_tuple(cut_u, cut_v, -1));
        int id = get<2>(*it);
        if (!is_bridge[id]) return true;
        int child = (par[cut_v][0] == cut_u ? cut_v : cut_u);
        bool u_in = in_subtree(child, u);
        bool v_in = in_subtree(child, v);
        return u_in == v_in;
    }

};