struct Hopcroft{
    int n, INF;
    vector<vector<int> > adj;
    vector<int> level, ptr, pair_u, pair_v;
    Hopcroft(){}
    Hopcroft(int _n, int _m){
        n = _n;
        INF = (int) 1e9;
        adj.assign(_n + 1, {});
        level.assign(_n + 1, 0);
        ptr.assign(_n + 1, 0);
        pair_u.assign(_n + 1, 0);
        pair_v.assign(_m + 1, 0);
    }
    void add(int u, int v){
        adj[u].push_back(v);
    }
    bool bfs(){
        queue<int> q;
        for(int u = 1; u <= n; u++){
            if(!pair_u[u]){
                level[u] = 0;
                q.push(u);
            }else level[u] = INF;
        }
        bool found = false;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v : adj[u]){
                int nxt = pair_v[v];
                if(nxt == 0){
                    found = true;
                }
                else if(level[nxt] == INF){
                    level[nxt] = level[u] + 1;
                    q.push(nxt);
                }
            }
        }
        return found;
    }
    bool dfs(int u){
        for (int &i = ptr[u]; i < (int) adj[u].size(); i++){
            int v = adj[u][i];
            int nxt = pair_v[v];
            if(!nxt || (level[nxt] == level[u] + 1 && dfs(nxt))){
                pair_u[u] = v;
                pair_v[v] = u;
                return true;
            }
        }
        return false;
    }
    int max_matching(){
        int cnt = 0;
        while(bfs()){
            fill(ptr.begin(), ptr.end(), 0);
            for(int u = 1; u <= n; u++){
                if(!pair_u[u] && dfs(u)){
                    cnt++;
                }
            }
        }
        return cnt;
    }
};