struct Dsu{
	int n, comp;
	vector<int> par;
	Dsu(){}
	Dsu(int _n){
		n = _n;
		comp = _n;
		par.assign(n + 1, -1);
	}
	void reset(){
		fill(par.begin(), par.end(), -1);
		comp = n;
	}
	int find(int u){
		return par[u] < 0 ? u : par[u] = find(par[u]);
	}
	bool unite(int u, int v){
		u = find(u);
		v = find(v);
		if(u == v) return false;
		if(par[u] > par[v]) swap(u, v);
		comp--;
		par[u] += par[v];
		par[v] = u;
		return true;
	}
	int size(int u){
		return -par[find(u)];
	}
	bool same(int u, int v){
		return find(u) == find(v);
	}
	vector<vector<int> > group(){
		vector<vector<int> > res(n + 1);
		for(int i = 1; i <= n; i++){
			res[find(i)].push_back(i);
		}
		vector<vector<int> > ans;
		for(int i = 1; i <= n; i++){
			if(!res[i].empty()){
			    ans.push_back(res[i]);
			}
		}
		return ans;
	}
};