template<typename T>
vector<T> dijkstra(const Graph<T> &g, const vector<int> &start) {
    const T inf = numeric_limits<T>::max() / 4;
    vector<T> dist(g.n + 1, inf);
    using P = pair<T, int>;                    
    priority_queue<P, vector<P>, greater<P>> pq;
    for (int u : start) {
        dist[u] = 0;
        pq.push({0, u});                    
    }
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;           
        for (int id : g.adj[u]) {
            const auto& e = g.edges[id];
            int v = e.from ^ e.to ^ u;          
            if (dist[v] > dist[u] + e.cost) {
                dist[v] = dist[u] + e.cost;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
