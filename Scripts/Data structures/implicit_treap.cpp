// Неявный ключ: позиция в последовательности.
// Индексы с 0, отрезки [l, r] включительно.
// Операции: ожидаемо O(log n), память O(n).
struct Treap {
    struct Node {
        int val, cnt = 1;
        li sum;
        unsigned long long prior = rnd();
        Node *l = nullptr, *r = nullptr;
        bool rev = false;

        Node(int x) : val(x), sum(x) {}
        ~Node() {
            delete l;
            delete r;
        }
    };
    Node* root = nullptr;

    static int size(Node* t) {
        return t ? t->cnt : 0;
    }
    static li sum(Node* t) {
        return t ? t->sum : 0LL;
    }
    int size() const {
        return size(root);
    }
    void pull(Node* t) {
        t->cnt = 1 + size(t->l) + size(t->r);
        t->sum = sum(t->l) + t->val + sum(t->r);
    }
    void push(Node* t) {
        if (!t || !t->rev) return;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
        t->rev = false;
    }

    // a: первые k элементов, b: остальные.
    void split(Node* t, int k, Node*& a, Node*& b) {
        if (!t) {
            a = b = nullptr;
            return;
        }
        push(t);
        int left = size(t->l);
        if (k <= left) {
            split(t->l, k, a, t->l);
            b = t;
        } else {
            split(t->r, k - left - 1, t->r, b);
            a = t;
        }
        pull(t);
    }
    // Конкатенация непересекающихся деревьев.
    Node* merge(Node* a, Node* b) {
        if (!a || !b) return a ? a : b;
        push(a);
        push(b);
        if (a->prior > b->prior) {
            a->r = merge(a->r, b);
            pull(a);
            return a;
        }
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }

    // Вставка перед pos; pos = size(): в конец.
    void insert(int pos, int val) {
        Node *a, *b;
        split(root, pos, a, b);
        root = merge(merge(a, new Node(val)), b);
    }
    void erase(int pos) {
        Node *a, *b, *c;
        split(root, pos, a, b);
        split(b, 1, b, c);
        delete b;
        root = merge(a, c);
    }
    li get_sum(int l, int r) {
        Node *a, *b, *c;
        split(root, l, a, b);
        split(b, r - l + 1, b, c);
        li ans = sum(b);
        root = merge(merge(a, b), c);
        return ans;
    }
    void reverse(int l, int r) {
        Node *a, *b, *c;
        split(root, l, a, b);
        split(b, r - l + 1, b, c);
        b->rev ^= 1;
        root = merge(merge(a, b), c);
    }
    void clear() { // O(n)
        delete root;
        root = nullptr;
    }

    Treap() = default;
    // Построение: ожидаемо O(n log n).
    Treap(const vi& a) {
        for (int x : a)
            insert(size(), x);
    }
    ~Treap() {
        clear();
    }
    Treap(const Treap&) = delete;
    Treap& operator=(const Treap&) = delete;
};
