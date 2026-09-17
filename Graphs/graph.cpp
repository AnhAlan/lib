template<typename T>
class Graph{
    public:
    struct Edge{
        int from, to;
        T cost;
    };
    int n;
    bool digraph;
    vector<vector<int> > adj;
    vector<Edge> edges;
    Graph() {}
    void init(int _n, bool _digraph = false) {
        n = _n;
        digraph = _digraph;
        adj.assign(n + 1, {});
        edges.clear();
    }
    void add(int from, int to, T cost = 1) {
        int id = (int) edges.size();
        adj[from].push_back(id);
        if (!digraph) adj[to].push_back(id);
        edges.push_back({from, to, cost});
    }
};