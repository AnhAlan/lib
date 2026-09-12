template<typename T>
struct Scc {
    const Digraph<T> &g;
    int n;
    int timer = 0;
    int scc_cnt = 0;
    vector<int> num, low, comp;
    vector<bool> in_stack;
    vector<vector<int>> scc;
    stack<int> st;
    Scc(const Digraph<T> &_g) : g(_g), n(_g.n){
        num.assign(n + 1, 0);
        low.assign(n + 1, 0);
        comp.assign(n + 1, 0);
        in_stack.assign(n + 1, false);
        scc.resize(n + 1);
    }
    void dfs(int u) {
        num[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;
        for(int id : g.adj[u]) {
            int v = g.edges[id].to;
            if(!num[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if(in_stack[v]) {
                low[u] = min(low[u], num[v]);
            }
        }
        if(low[u] == num[u]) {
            ++scc_cnt;
            while(true) {
                int v = st.top();
                st.pop();
                in_stack[v] = false;
                comp[v] = scc_cnt;
                scc[scc_cnt].push_back(v);
                if(v == u) break;
            }
        }
    }
    void build_scc() {
        if(scc_cnt > 0) return;
        for(int i = 1; i <= n; i++) {
            if(!num[i]) 
                dfs(i);
        }
    }
    vector<vector<int>> build_dag() {
        build_scc();
        vector<vector<int>> dag(scc_cnt + 1);
        for(int u = 1; u <= n; u++) {
            int a = comp[u];
            for(int id : g.adj[u]) {
                int v = g.edges[id].to;
                int b = comp[v];
                if(a != b) {
                    dag[a].push_back(b);
                }
            }
        }
        for(int i = 1; i <= scc_cnt; i++) {
            sort(dag[i].begin(), dag[i].end());
            dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
        }
        return dag;
    }
};