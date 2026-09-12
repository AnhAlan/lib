struct Dinic{
    struct OriEdge{
        int u, v;
        long long cap;
        OriEdge(){}
        OriEdge(int _u, int _v, long long _cap) : u(_u), v(_v), cap(_cap) {}
    };
    struct Edge{
        int to, rev; 
        long long cap;
        Edge(){}
        Edge(int _to, int _rev, long long _cap) : to(_to), rev(_rev), cap(_cap) {}
    };
    vector<OriEdge> edges;
    vector<vector<Edge> > adj;
    vector<int> level, ptr;
    Dinic(int _n){
        adj.assign(_n + 1, {});
        level.assign(_n + 1, 0);
        ptr.assign(_n + 1, 0);
    }
    void add(int u, int v, long long cap){
        Edge A = {v, (int) adj[v].size(), cap};
        Edge B = {u, (int) adj[u].size(), 0};
        adj[u].push_back(A);
        adj[v].push_back(B);
        edges.push_back({u, v, cap});
    }
    bool bfs(int s, int t){
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(Edge &e : adj[u]){
                if(e.cap > 0 && level[e.to] == -1){
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }
    long long dfs(int u, int t, long long pushed){
        if(!pushed) return 0;
        if(u == t) return pushed;
        for(int &i = ptr[u]; i < (int) adj[u].size(); i++){
            Edge &e = adj[u][i];
            if(e.cap <= 0 || level[e.to] != level[u] + 1) continue;
            long long tr = dfs(e.to, t, min(pushed, e.cap));
            if(tr == 0) continue;
            e.cap -= tr;
            adj[e.to][e.rev].cap += tr;
            return tr;
        }
        level[u] = -1;
        return 0;
    }
    long long max_flow(int s, int t){
        long long flow = 0;
        while(bfs(s, t)){
            fill(ptr.begin(), ptr.end(), 0);
            long long pushed;
            while((pushed = dfs(s, t, numeric_limits<long long>::max()))){
                flow += pushed;
            }
        }
        return flow;
    }
    vector<int> min_cut_side(int s){
        vector<int> vis((int) adj.size(), 0);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &e : adj[u]){
                if(e.cap > 0 && !vis[e.to]){
                    vis[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }
    vector<pair<int,int>> get_min_cut_edges(int s){
        vector<int> vis = min_cut_side(s);
        vector<pair<int,int>> cut;
        for(auto &e : edges){
            if(vis[e.u] && !vis[e.v]){
                cut.push_back({e.u, e.v});
            }
        }
        return cut;
    }
};