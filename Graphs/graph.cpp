template<typename T>
class Graph{
    public:
    struct Edge{
        int from, to;
        T cost;
    };
    int n;
    vector<vector<int> > adj;
    vector<Edge> edges;
    Graph() {}
    void init(int _n) {
        n = _n;
        adj.assign(n + 1, {});
    }
    virtual int add(int from, int to, T cost = 1) = 0;
};
