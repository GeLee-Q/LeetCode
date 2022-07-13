class Trie {
    int Trie [100009][26] ;
    int count [100009 * 26] ;
    int idx = 0;

    Trie() {
        trie = new int[N][26];
        count = new int[N];
        index = 0;
    }
    
    void insert(String s) {
        int p = 0;
        for (int i = 0; i < s.length(); i++) {
            int u = s[i] - 'a';
            if (trie[p][u] == 0) trie[p][u] = ++index;
            p = trie[p][u];
        }
        count[p]++;
    }
    
    bool search(String s) {
        int p = 0;
        for (int i = 0; i < s.length(); i++) {
            int u = s[i] - 'a';
            if (trie[p][u] == 0) return false;
            p = trie[p][u];
        }
        return count[p] != 0;
    }
    
    bool startsWith(String s) {
        int p = 0;
        for (int i = 0; i < s.length(); i++) {
            int u = s[i] - 'a';
            if (trie[p][u] == 0) return false;
            p = trie[p][u];
        }
        return true;
    }
}