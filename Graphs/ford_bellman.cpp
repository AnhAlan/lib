template<typename T>
vector<T> ford_bellman(const Graph<T> &_g, const vector<int> &starts) {
    assert(_g.digraph == true);
    T INF = numeric_limits<T>::max() / 2;
    vector<T> dist(_g.n + 1, INF);
    for (int s : starts) {
        dist[s] = 0;
    }
    for (int i = 1; i <= _g.n - 1; i++) {
        bool updated = false;
        for (const auto &e : _g.edges) {
            if (dist[e.from] != INF &&
                dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
                updated = true;
            }
        }
        if (!updated) break;
    }
    for (const auto &e : _g.edges) {
        if (dist[e.from] != INF &&
            dist[e.to] > dist[e.from] + e.cost) {
            return {}; // has negative cycle
        }
    }
    return dist;
}
