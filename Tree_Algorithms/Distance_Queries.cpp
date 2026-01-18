#include <bits/stdc++.h>
using namespace std;
const int LOG = 18;

void dfs(int u, int p, vector<vector<int>> &adj, vector<int> &depth, vector<vector<int>> &dp)
{
    dp[u][0] = p;
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        depth[v] = depth[u] + 1;
        dfs(v, u, adj, depth, dp);
    }
}

int lca(int a, int b, vector<vector<int>> &dp, vector<int> &depth)
{
    if (depth[a] < depth[b])
        swap(a, b);

    int diff = depth[a] - depth[b];
    for (int j = LOG - 1; j >= 0; j--)
        if (diff & (1 << j))
            a = dp[a][j];

    if (a == b)
        return a;

    for (int j = LOG - 1; j >= 0; j--)
    {
        if (dp[a][j] != dp[b][j])
        {
            a = dp[a][j];
            b = dp[b][j];
        }
    }
    return dp[a][0];
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<vector<int>> dp(n + 1, vector<int>(LOG, 0));
    vector<int> depth(n + 1, 0);

    dfs(1, 0, adj, depth, dp);

    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= n; i++)
            dp[i][j] = dp[dp[i][j - 1]][j - 1];

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        int LCA = lca(a, b, dp, depth);
        cout << (depth[a] + depth[b] - 2 * depth[LCA]) << '\n';
    }
    return 0;
}