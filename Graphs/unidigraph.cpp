template<typename T>
class Undigraph : public Graph<T> {
    public:
    using Graph<T>:: adj;
    using Graph<T>:: edges;
    using Graph<T>:: n;
    using Graph<T>::init;
    Undigraph(int _n = 0) {
        if (_n) init(_n);
    }
    int add(int from, int to, T cost = 1){
        int id = (int) edges.size();
        adj[from].push_back(id);
        adj[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }
};