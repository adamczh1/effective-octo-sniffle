struct graph{
    int n;
    vector< vector<int> > adj;
    graph(int n=0) : n(n), adj(n) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int add_node() {
        adj.push_back({});
        return n++;
    }
 	vector<int>& operator[](int u) { return adj[u]; }
};
struct bcc_graph {
    int n;
    vector< vector<int> > adj;
    bcc_graph(int n=0) : n(n), adj(n) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int add_node()
    {
        adj.push_back({});
        return n++;
    }
    vector<int>& operator[](int u) { return adj[u]; }
    vector<int> num, low, art, stk, id;
    vector<vector<int>> comps;
    tgraph tree;
    void biconnected_components(){
        num = vector<int>(n);
        low = vector<int>(n);
        art = vector<int>(n);
        stk = vector<int>();
        comps = vector<vector<int>>();
        function<void(int, int, int&)> dfs = [&](int u, int p, int &t){
            num[u] = low[u] = ++t;
            stk.push_back(u);
            for (int v : adj[u]) if (v != p){
                if (!num[v]){
                    dfs(v, u, t);
                    low[u] = min(low[u], low[v]);
                    if (low[v] >= num[u]){
                        art[u] = (num[u] > 1 || num[v] > 2);
                        comps.push_back({u});
                        while (comps.back().back() != v)
                            comps.back().push_back(stk.back()),
                            stk.pop_back();
                    }
                }
                else low[u] = min(low[u], num[v]);
            }
        };
        for (int u = 0, t; u < n; ++u)
            if (!num[u]) dfs(u, -1, t = 0);
        bct = graph(0);
        id = vector<int>(n);
        for (int u = 0; u < n; ++u)
            if (art[u]) id[u] = bct.add_node();
        for (auto &comp : comps){
            int node = bct.add_node();
            for (int u : comp)
                if (!art[u]) id[u] = node;
                else bct.add_edge(node, id[u]);
        }
    }
    bool connected(int u, int v){
        if (art[u]) swap(u, v);
        if (art[u]){
            //art art
            set<int> X;
            for (auto x : bct[id[v]])
                X.insert(x);
            for (auto x : bct[id[u]])
                if (X.find(x) != X.end())
                    return 1;
            return 0;
        }
        else if (!art[v]){
            // ~art ~art
            return id[u] == id[v];
        }
        else{
            // ~art art
            for (auto x : bct[id[v]]){
                if (x == id[u])
                    return 1;
            }
            return 0;
        }
    }
};
