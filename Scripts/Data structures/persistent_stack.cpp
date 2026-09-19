struct StackNode {
    int val;
    int next_version;

    StackNode() : val(-INF), next_version(-1) {}
    StackNode(int x, int next_version) : val(x), next_version(next_version) {}
};

StackNode buf[20'000'000];
int cur = 1;

int makeNode(int val, int next_version) {
    buf[cur].val = val;
    buf[cur].next_version = next_version;
    return cur++;
}

void push(int val, int v = cur - 1) {
    makeNode(val, v);
}

void pop(int v = cur - 1) {
    if (buf[v].next_version != -1) {
        int u = buf[v].next_version;
        makeNode(buf[u].val, buf[u].next_version);
    } else makeNode(-INF, -1);
}

int top(int v = cur - 1) {
    return buf[v].val;
}

int get(int k, int v = cur - 1) {
    int u = v;
    for (int i = 0; i < k; ++i) {
        u = buf[u].next_version;
        if (u == -1) return -INF;
    }
    return buf[u].val;
}
