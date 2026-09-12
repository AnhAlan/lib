template<typename T>
struct Dinic : Flow<T> {
    using Flow<T>::EPS;
    using Flow<T>::INF;
    using Flow<T>::n;
    using Flow<T>::st;
    using Flow<T>::fin;
    using Flow<T>::flow;
    using Flow<T>::adj;
    using Flow<T>::edges;
    vector<int> level, ptr;
    Dinic(int _n, int _st, int _fin) : Flow<T>(_n, _st, _fin) {
        level.resize(n + 1);
        ptr.resize(n + 1);
    }
    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(st);
        level[st] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                auto &e = edges[id];
                if (level[e.to] == -1 && e.cap - e.f > EPS) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[fin] != -1;
    }
    T dfs(int u, T pushed) {
        if (pushed <= EPS) return 0;
        if (u == fin) return pushed;
        for (int &i = ptr[u]; i < (int)adj[u].size(); i++) {
            int id = adj[u][i];
            auto &e = edges[id];
            if (level[e.to] != level[u] + 1) continue;
            T rem = e.cap - e.f;
            if (rem <= EPS) continue;
            T tr = dfs(e.to, min(pushed, rem));
            if (tr <= EPS) continue;
            e.f += tr;
            edges[id ^ 1].f -= tr;
            return tr;
        }
        return 0;
    }
    T max_flow() {
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (true) {
                T pushed = dfs(st, INF);
                if (pushed <= EPS) break;
                flow += pushed;
            }
        }
        return flow;
    }
    vector<bool> min_cut_side() {
        vector<bool> vis(n + 1, false);
        vis[st] = true;
        queue<int> q;
        q.push(st);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                auto &e = edges[id];
                if (!vis[e.to] && e.cap - e.f > EPS) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }
    vector<pair<int,int>> get_min_cut_edges() {
        vector<pair<int,int>> res;
        vector<bool> vis = min_cut_side();
        for (int i = 0; i < (int)edges.size(); i += 2) {
            auto &e = edges[i];
            if (vis[e.from] && !vis[e.to] && e.cap > EPS) {
                res.push_back({e.from, e.to});
            }
        }
        return res; 
    }
    vector<vector<int>> get_paths(int max_flow_dinic) {
        vector<vector<int>> ans;
        for (int it = 0; it < max_flow_dinic; it++) {
            vector<int> path;
            vector<int> parent_edge(n + 1, -1);
            queue<int> q;
            q.push(st);
            parent_edge[st] = -2;
            while (!q.empty() && parent_edge[fin] == -1) {
                int u = q.front();
                q.pop();
                for (int id : adj[u]) {
                    auto &e = edges[id];
                    if (parent_edge[e.to] != -1)  continue;
                    if (e.f <= EPS) continue;
                    parent_edge[e.to] = id;
                    q.push(e.to);
                }
            }
            assert(parent_edge[fin] != -1);
            int cur = fin;
            while (cur != st) {
                int id = parent_edge[cur];
                path.push_back(cur);
                edges[id].f -= 1;
                cur = edges[id].from;
            }
            path.push_back(st);
            reverse(all(path));
            ans.push_back(path);
        }
        return ans;
    }
};
