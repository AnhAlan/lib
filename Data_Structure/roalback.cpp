struct Save{
    int u, old_par_u;
    int v, old_par_v;
    Save(){}
    Save(int _u, int _old_par_u, int _v, int _old_par_v){
        u = _u, old_par_u = _old_par_u;
        v = _v, old_par_v = _old_par_v;
    }
};
struct Dsu_rollback {
	int n, comp;
	vector<int> par;
	stack<Save> st;
	Dsu_rollback(){}
	Dsu_rollback(int _n) : n(_n){
		comp = _n;
		par.assign(n + 1, -1);
	}
	void reset(){
		for(int i = 1; i <= n; i++){
			par[i] = -1;
		}
	}
	int find(int u){
		while(par[u] >= 0){
			u = par[u];
		}
		return u;
	}
	bool unite(int u, int v){
		u = find(u);
		v = find(v);
		if(u == v){
			st.push({-1, -1, -1, -1});
			return false;
		}
		if(par[u] > par[v]) swap(u, v);
		comp--;
		st.push({u, par[u], v, par[v]});
		par[u] += par[v];
		par[v] = u;
		return true;
	}
	void roll_back(){
		Save sv = st.top();
		st.pop();
		if(sv.u == -1) return;
		comp++;
		par[sv.u] = sv.old_par_u;
		par[sv.v] = sv.old_par_v;
	}
};
