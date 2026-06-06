const int N = 2'300'000, A = 26;

struct node {
    node* to[A];
    int cntEnd, cnt;
} nodes[N];

typedef node* trie;

int T = 0;

trie new_node() {
    memset(nodes[T].to, 0, A * (sizeof nodes[T].to[0]));
    nodes[T].cnt = 0;
    nodes[T].cntEnd = 0;
    return &nodes[T++];
}

void add_string(trie r, const string& s, int val = 1) {
    for (char _c : s) {
        int c = _c - 'a';
        r->cnt += val;
        if (!r->to[c])
            r->to[c] = new_node();
        r = r->to[c];
    }
    r->cntEnd += val;
    r->cnt += val;
}

trie find(trie r, const string& s) {
    for (char _c : s) {
        int c = _c - 'a';
        if (!r->to[c])
            return nullptr;
        r = r->to[c];
    }
    return r;
}

int get_cnt(trie r, const string& s) {
    trie result = find(r, s);
    return (result == nullptr ? 0 : result->cnt);
}

int get_cntEnd(trie r, const string& s) {
    trie result = find(r, s);
    return (result == nullptr ? 0 : result->cntEnd);
}