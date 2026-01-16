#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
using ll = long long;
vector<int> start, endt;
vector<int> flat;
vector<int> adj[200001];

class RangeSumQuery
{
public:
    vector<ll> seg;
    RangeSumQuery(int n)
    {
        seg.resize(4 * n);
    }
    void build(int ind, int low, int high, vector<ll> &arr)
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    ll query(int ind, int low, int high, int l, int r)
    {
        if (r < low || high < l)
            return -1e7;
        if (low >= l && high <= r)
            return seg[ind];
        int mid = (low + high) >> 1;
        return max(query(2 * ind + 1, low, mid, l, r), query(2 * ind + 2, mid + 1, high, l, r));
    }

    void update(int ind, int low, int high, int i, ll val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val);
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};

void dfs(int node, int pv, int &timer, vector<int> &Nodes)
{
    start[node] = timer;
    flat[timer] = Nodes[node];
    timer++;
    for (int &child : adj[node])
    {
        if (child == pv)
            continue;
        dfs(child, node, timer, Nodes);
    }
    endt[node] = timer;
    flat[timer] = -Nodes[node];
    timer++;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    start.assign(n + 1, 0);
    endt.assign(n + 1, 0);
    flat.assign(2 * n + 1, 0);
    vector<int> nodes(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> nodes[i];
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int timer = 0;
    dfs(1, 0, timer, nodes);
    RangeSumQuery st(2 * n);
    st.build(0, 0, 2 * n, flat);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int s, x;
            cin >> s >> x;
            st.update(0, 0, 2 * n, start[s], x);
            st.update(0, 0, 2 * n, endt[s], -x);
            nodes[s] = x;
        }
        else
        {
            int s;
            cin >> s;
            int subt = st.query(0, 0, 2 * n, 0, start[s]);
            cout << subt << endl;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
