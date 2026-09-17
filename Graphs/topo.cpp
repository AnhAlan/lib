vector<int> path_topo;
vector<bool> vis_topo;
void dfs_topo(int u, const vector<vector<int>> &dag) {
    vis_topo[u] = true;
    for (int v : dag[u])
        if (!vis_topo[v])
            dfs_topo(v, dag);
    path_topo.push_back(u);
}
vector<int> build_topo(const vector<vector<int>> &dag) {
    int n = (int) dag.size() - 1;
    path_topo.clear();
    vis_topo.assign(n + 1, false);
    for (int i = 1; i <= n; i++)
        if (!vis_topo[i])
            dfs_topo(i, dag);
    reverse(path_topo.begin(), path_topo.end());
    return path_topo;
}