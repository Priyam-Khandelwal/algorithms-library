using ll = long long;
ll eval(array<ll, 2> a, ll x) {
    return a[0]*x + a[1];
}
struct LiChao {
    struct Node {
        Node *l, *r;
        array<ll, 2> f;
        Node() : l(0), r(0), f{0, -(1ll<<62)} {}
    };
    deque<Node> buf;
    template<class... Args>
    Node *newnode(Args... args) {
        return &buf.emplace_back(args...);
    }
    void update(Node *&v, ll l, ll r, array<ll, 2> f) {
        if(!v) {
            v = newnode(), v->f = f;
            return;
        }
        ll mid = l + (r-l)/2;
        if(eval(f, mid) < eval(v->f, mid)) swap(f, v->f);
        if(l == r) return;
        if(eval(f, l) < eval(v->f, l))
            update(v->l, l, mid, f);
        else
            update(v->r, mid+1, r, f);
    }
    ll query(Node *v, ll l, ll r, ll x) {
        if(!v) return (1ll<<62);
        ll mid = l + (r-l)/2;
        return min(eval(v->f, x),
            x <= mid ? query(v->l, l, mid, x) : query(v->r, mid+1, r, x));
    }
    void update(array<ll, 2> f) {
        update(root, -(n-1), n-1, f);
    }
    ll query(ll x) {
        return query(root, -(n-1), n-1, x);
    }
    ll n;
    Node *root;
    LiChao(ll n) : n(n), root(0) {}
};