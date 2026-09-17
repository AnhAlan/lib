#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rand(long long l,long long r){
    uniform_int_distribution<long long> dist(l,r);
    return dist(rng);
}

vector<tuple<int, int, int>> random_tree(int n) {
    vector<tuple<int, int, int>> edges;
    if (n <= 1) return edges;
    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end(), rng);
    for (int i = 1; i < n; i++) {
        int u = vertices[i];
        int v = vertices[rand(0, i - 1)]; 
        long long w = rand(1, 10000);           
        edges.push_back({u, v, w});
    }
    shuffle(edges.begin(), edges.end(), rng);
    return edges;
}
string random_string(int n){
    string s(n, ' ');
    for(int i = 0; i < n; i++){
        s[i] = 'a' + rand(0,25);
    }
    return s;
}
vector<tuple<int,int,int> > random_graph(int n, int m){
    long long max_edges = 1ll * n * (n - 1) / 2;
    if (m > max_edges) m = max_edges; 
    vector<tuple<int,int,int> > adj;
    set<pair<int,int>> seen;
    for(int i = 0; i < m; i++){
        int u = rand(1,n);
        int v = rand(1,n);
        int w = rand(1,10);
        while(u == v || seen.count({u,v}) || seen.count({v,u})){
            u = rand(1,n);
            v = rand(1,n);
        }
        seen.insert({u,v});
        seen.insert({v,u});
        adj.push_back({u, v, w});
    }
    return adj;
}
vector<int> random_vector(int n){
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    shuffle(a.begin(), a.end(), rng);
    return a;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    system("gen.exe > input.txt");
    system("sol.exe < input.txt > output.txt");
    system("brute.exe < input.txt > answer.txt");
    if (system("fc output.txt answer.txt > nul") != 0) {
        cout << "WA at test " << '\n';
        return 0;
    }
    /*
    if (system("diff output.txt answer.txt > /dev/null") != 0) {
        cout << "WA at test " << '\n';
        return 0;
    }   
    LINUX
    */
    this_thread::sleep_for(chrono::milliseconds(100));
    
}