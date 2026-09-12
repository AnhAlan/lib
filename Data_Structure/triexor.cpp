struct Trie_node {
    int child[2];
    int cnt;
    Trie_node() {
        child[0] = child[1] = -1;
        cnt = 0;
    }
};
struct Trie {
    vector<Trie_node> node;
    int root;
    int xor_mask;
    Trie() {
        root = 0;
        xor_mask = 0;
        node.emplace_back(); 
    }
    void add(int k) {
        int cur = root;
        node[cur].cnt++;
        for (int i = 30; i >= 0; i--) { 
            int b = (k >> i) & 1;
            if (node[cur].child[b] == -1) {
                node[cur].child[b] = (int)node.size();
                node.emplace_back();
            }
            cur = node[cur].child[b];
            node[cur].cnt++;
        }
    }
};