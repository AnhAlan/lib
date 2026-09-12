template<typename T>
class Forest : public Graph<T> {
public:
    using Graph<T>::adj;
    using Graph<T>::edges;
    using Graph<T>::n;
    using Graph<T>::init;
    Forest(int _n = 0) {
        if (_n) init(_n);
    }
    int add(int from, int to, T cost = 1) override {
        int id = (int)edges.size();
        assert(id < n - 1);
        adj[from].push_back(id);
        adj[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }
};