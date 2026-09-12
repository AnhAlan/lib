template<typename T>
struct Mcmf : public Flow<T> {
    using Flow<T>::EPS;
    using Flow<T>::INF;
    using Flow<T>::n;
    using Flow<T>::st;
    using Flow<T>::fin;
    using Flow<T>::adj;
    using Flow<T>::edges;
    using Flow<T>::flow;
    vector<T> dist, pot;
    vector<int> par_v, par_e;
    Mcmf(int _n, int _st, int _fin) : Flow<T>(_n, _st, _fin) {
        dist.resize(n + 1);
        pot.resize(n + 1);
        par_v.resize(n + 1);
        par_e.resize(n + 1);
    }
    void reset_all() {
        this->reset();
        fill(pot.begin(), pot.end(), 0);
    }
    bool dijkstra() {
        const T INF_DIST = INF;
        fill(dist.begin(), dist.end(), INF_DIST);
        using P = pair<T, int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        dist[st] = 0;
        pq.push({0, st});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            for (int id : adj[u]) {
                auto &e = edges[id];
                if (e.cap - e.f <= EPS) continue;
                T nd = d + e.cost + pot[u] - pot[e.to];
                if (nd < dist[e.to]) {
                    dist[e.to] = nd;
                    par_v[e.to] = u;
                    par_e[e.to] = id;
                    pq.push({nd, e.to});
                }
            }
        }
        return dist[fin] < INF_DIST;
    }
    pair<T, T> min_cost_max_flow(T need = INF) {
        flow = 0;
        T total_cost = 0;
        const T INF_FLOW = INF;
        while (flow < need && dijkstra()) {
            for (int i = 1; i <= n; i++) {
                if (dist[i] < INF_FLOW) {
                    pot[i] += dist[i];
                }
            }
            T f = need - flow;
            for (int v = fin; v != st; v = par_v[v]) {
                int id = par_e[v];
                f = min(f, edges[id].cap - edges[id].f);
            }
            for (int v = fin; v != st; v = par_v[v]) {
                int id = par_e[v];
                edges[id].f += f;
                edges[id ^ 1].f -= f;
            }
            flow += f;
            total_cost += f * pot[fin];
        }
        if (flow < need && need != INF_FLOW) return {-1, -1};
        return {flow, total_cost};
    }
};