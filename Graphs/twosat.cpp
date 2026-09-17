struct Two_sat {
    int n;
    vector<int> low, num, comp;
    vector<bool> in_stack;
    stack<int> st;
    int timer, scc_cnt;
    Two_sat() {}
    void init(int _n) {
        assert(g.digraph);
        assert(_n * 2 == g.n);
        n = _n;
        low.assign(2 * n + 1, 0);
        num.assign(2 * n + 1, 0);
        comp.assign(2 * n + 1, 0);
        in_stack.assign(2 * n + 1, false);
        timer = 0;
        scc_cnt = 0;
        while (!st.empty()) st.pop();
    }
    int NOT(int u) {
        return u + (u <= n ? n : -n);
    }
    // u OR v
    void add(int u, int v) {
        g.add(NOT(u), v);
        g.add(NOT(v), u);
    }
    void set_true(int u) {
        add(u, u);
    }
    void set_false(int u) {
        add(NOT(u), NOT(u));
    }
    void dfs(int u) {
        low[u] = num[u] = ++timer;
        st.push(u);
        in_stack[u] = true;
        for (int id : g.adj[u]) {
            int v = g.edges[id].to;
            if (!num[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (in_stack[v]) {
                low[u] = min(low[u], num[v]);
            }
        }
        if (low[u] == num[u]) {
            ++scc_cnt;
            while (true) {
                int v = st.top();
                st.pop();
                in_stack[v] = false;
                comp[v] = scc_cnt;
                if (v == u) break;
            }
        }
    }
    vector<bool> solve() {
        for (int u = 1; u <= 2 * n; u++) {
            if (!num[u]) {
                dfs(u);
            }
        }
        vector<bool> ans(n + 1);
        for (int u = 1; u <= n; u++) {
            if (comp[u] == comp[NOT(u)]) {
                return {}; // fail
            }
            ans[u] = comp[u] < comp[NOT(u)];
        }
        return ans;
    }
};
