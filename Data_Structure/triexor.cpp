struct Node {
    int child[2];
    int cnt;
    Node() {
        child[0] = child[1] = -1;
        cnt = 0;
    }
};
struct Trie {
    vector<Node> nodes;
    int root;
    int xor_mask;
    Trie() {}
    void init(int max) {
        root = 0;
        xor_mask = 0;
        nodes.emplace_back();
    }
    void add(int k) {
        int cur = root;
        nodes[cur].cnt++;
        for (int i = 30; i >= 0; i--) { 
            int b = (k >> i) & 1;
            if (nodes[cur].child[b] == -1) {
                nodes[cur].child[b] = (int)nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].child[b];
            nodes[cur].cnt++;
        }
    }
};