static const int apl = 26;
struct Node{
    Node *child[apl];
    Node(){
        fill(child, child + apl, nullptr);
    }
};
struct Trie{
    vector<Node> node;
    int cnt_node;
    Node *root;
    Trie(int max_node){
        node.resize(max_node);
        cnt_node = 0;
        root = create();
    }
    Node* create(){
        return &node[cnt_node++];
    }
    void add(const string &s){
        Node *cur = root;
        for(char c : s){
            int id = c - 'a';
            if(!cur->child[id]){
                cur->child[id] = create();
            }
            cur = cur->child[id];
        }
    }
};