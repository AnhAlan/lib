template<typename T>
struct Prim {
    struct Edge {
        int u, v;
        T w;
    };
    int n;
    vector<bool> used;
    vector<int> parent;
    vector<T> d;
    vector<Edge> MST;
    Prim() {}
    void init() {
        n = g.n;
        assert(!g.digraph);
        used.assign(n + 1, false);
        parent.assign(n + 1, -1);
        d.assign(n + 1, numeric_limits<T>::max());
        MST.clear();
    }
    T mst(int start = 1){
        MST.clear();
        fill(used.begin(), used.end(), false);
        fill(d.begin(), d.end(), numeric_limits<T>::max());
        fill(parent.begin(), parent.end(), -1);
        d[start] = 0;
        return mst_from(start);
    }
    T mst_forest(){
        MST.clear();
        fill(used.begin(), used.end(), false);
        fill(d.begin(), d.end(), numeric_limits<T>::max());
        fill(parent.begin(), parent.end(), -1);
        T total = 0;
        for(int s = 1; s <= n; s++){
            if(!used[s]){
                d[s] = 0;
                total += mst_from(s);
            }
        }
        return total;
    }
    Graph<T> build_tree(){
        Graph<T> tree;
        tree.init(n);
        for(auto [u, v, w] : MST){
            tree.add(u, v, w);
        }
        MST.clear();
        return tree;
    }
private:
    T mst_from(int start){
        uisng P = pair<T, int>;
        priority_queue< P, vector<P>, greater<P>> pq;
        T cost = 0;
        pq.push({0, start});
        while(!pq.empty()){
            auto [w, u] = pq.top();
            pq.pop();
            if(used[u]) continue;
            used[u] = true;
            cost += w;
            if(parent[u] != -1){
                MST.push_back({parent[u], u, w});
            }
            for(int id : g.adj[u]){
                int v = g.edges[id].from ^ g.edges[id].to ^ u;
                T nw = g.edges[id].cost;
                if(!used[v] && nw < d[v]){
                    d[v] = nw;
                    parent[v] = u;
                    pq.push({nw, v});
                }
            }
        }
        return cost;
    }
};