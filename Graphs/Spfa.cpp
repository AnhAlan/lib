template<typename T>
vector<T> Spfa(const Graph<T> &g, int start) {
    T INF = numeric_limits<T>::max() / 2;
    vector<T> dist(g.n + 1, INF);
    vector<bool> in_queue(g.n + 1, false);
    vector<int> cnt(g.n + 1, 0);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    in_queue[start] = true;
    cnt[start] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int id : g.adj[u]) {
            int v = g.edges[id].to;
            T cost = g.edges[id].cost;
            if (dist[u] != INF && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                if (!in_queue[v]) {
                    if (++cnt[v] >= g.n) {
                        // cycle
                        return {};
                    }
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return dist;
}