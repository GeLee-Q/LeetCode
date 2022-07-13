class Trie{
    struct Node{
        bool isEnd;
        Node * next[26];
        Node:isEnd(false), next{nullptr}
    }

    /* 
    根节点
     */
    Node * root = new Node();

    void add(string s){
        Node * p = root;
        for(int i = 0; i < s.size(); i++){
            int u = s[i] - 'a';
            if(root->next[u] == nullptr){
                root->next[u] = new Node();
            }
            p = p->next[u];
        }
        p->isEnd = true;
    }

    bool search(string s){
        Node * p = root;
        for(int i = 0; i < s.size(); i++){
            int u = s[i] - 'a';
            if(p->next[u] == nullptr) return false;
            p = p->next[u];
        }
        return p->isEnd;
    }

    bool startWith(string s){
        Node * p = root;
        for(int i = 0; i < s.size(); i++){
            int u = s[i] - 'a';
            if(p->next[u] == nullptr) return false;
            p = p->next[u];
        }
        return true;
    }

}


