template<typename T>
class Flow {
public:
    static constexpr T EPS = (T)1e-9;
    static constexpr T INF = (T)1e18;
    struct Edge {
        int from, to;
        T cap, f, cost;
    };
    int n, st, fin;
    vector<vector<int>> adj;
    vector<Edge> edges;
    T flow;
    Flow(int _n, int _st, int _fin) {
        n = _n;
        st = _st;
        fin = _fin;
        adj.resize(n + 1);
        flow = 0;
    }
    void reset() {
        for (auto &e : edges) {
            e.f = 0;
        }
        flow = 0;
    }
    int add(int from, int to, T forward_cap, T backup_cap = 0, T edge_cost = 0) {
        int id = (int)edges.size();
        adj[from].push_back(id);
        edges.push_back({from, to, forward_cap, 0, edge_cost});
        adj[to].push_back(id + 1);
        edges.push_back({to, from, backup_cap, 0, -edge_cost});
        return id;
    }
};