struct Node {
    Node *child[apl];
    Node *nxt[apl];
    Node *fail;
    vector<int> found;
    Node() {
        for (int i = 0; i < apl; i++) {
            child[i] = nullptr;
            nxt[i] = nullptr;
        }
        fail = nullptr;
    }
};

struct Aho_corasick {
    vector<Node> nodes;
    Node *root;
    int cnt_node;
    Aho_corasick(int max_node) {
        nodes.resize(max_node);
        cnt_node = 0;
        root = create();
    }
    Node *create() {
        return &nodes[cnt_node++];
    }
    void add(const string &s, int id) {
        Node *cur = root;
        for (const char &c : s) {
            int x = c - 'a';
            if (cur->child[x] == nullptr) {
                cur->child[x] = create();
            }
            cur = cur->child[x];
        }
        cur->found.push_back(id);
    }
    void build() {
        root->fail = root;
        queue<Node*> q;
        for (int i = 0; i < apl; i++) {
            if (root->child[i] != nullptr) {
                Node *u = root->child[i];
                root->nxt[i] = u;
                u->fail = root;
                q.push(u);
            }
            else {
                root->nxt[i] = root;
            }
        }
        while (!q.empty()) {
            Node *u = q.front();
            q.pop();
            for (int id : u->fail->found) {
                u->found.push_back(id);
            }
            for (int i = 0; i < apl; i++) {
                if (u->child[i] == nullptr) {
                    u->nxt[i] = u->fail->nxt[i];
                    continue;
                }
                Node *v = u->child[i];
                v->fail = u->fail->nxt[i];
                u->nxt[i] = v;
                q.push(v);
            }
        }
    }
};