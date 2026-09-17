vector<int> find_topo(const vector<vector<int>> &dag) {
    int n = (int) dag.size() - 1;
    vector<int> indeg(n + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : dag[u]) {
            indeg[v]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) q.push(i);
    }
    vector<int> path_topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        path_topo.push_back(u);
        for (int v : dag[u]) {
            if (--indeg[v] == 0)
                q.push(v);
        }
    }
    return path_topo;
}