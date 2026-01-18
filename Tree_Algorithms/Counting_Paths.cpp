#include <iostream>
#include <vector>
#include <algorithm>
const int LOG = 18;

void dfs(size_t u, size_t p, std::vector<std::vector<size_t>> &adj, std::vector<size_t> &depth, std::vector<std::vector<size_t>> &dp)
{
    dp[u][0] = p;
    for (size_t v : adj[u])
    {
        if (v == p)
            continue;
        depth[v] = depth[u] + 1;
        dfs(v, u, adj, depth, dp);
    }
}

size_t lca(size_t a, size_t b, std::vector<std::vector<size_t>> &dp, std::vector<size_t> &depth)
{
    if (depth[a] < depth[b])
        std::swap(a, b);

    size_t diff = depth[a] - depth[b];

    for (int j = LOG - 1; j >= 0; j--)
        if (diff & (1ULL << j))
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

void dfs2(size_t u, size_t p, std::vector<std::vector<size_t>> &adj, std::vector<size_t> &dp2, std::vector<size_t> &dp3)
{
    dp3[u] = dp2[u];
    for (size_t v : adj[u])
    {
        if (v == p)
            continue;
        dfs2(v, u, adj, dp2, dp3);
        dp3[u] = dp3[u] + dp3[v];
    }
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<std::vector<size_t>> adj(n + 1);
    for (size_t i = 1; i < n; i++)
    {
        size_t a, b;
        std::cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    std::vector<std::vector<size_t>> dp(n + 1, std::vector<size_t>(LOG, 0));
    std::vector<size_t> depth(n + 1, 0);

    dfs(1, 0, adj, depth, dp);

    for (size_t j = 1; j < LOG; j++)
        for (size_t i = 1; i <= n; i++)
            dp[i][j] = dp[dp[i][j - 1]][j - 1];

    std::vector<size_t> dp2(n + 1, 0);
    std::vector<size_t> dp3(n + 1, 0);
    while (q--)
    {
        size_t a, b;
        std::cin >> a >> b;
        dp2[a]++;
        dp2[b]++;
        size_t LCA = lca(a, b, dp, depth);
        dp2[LCA]--;
        if (dp[LCA][0] != 0)
        {
            dp2[dp[LCA][0]]--;
        }
    }
    dfs2(1, 0, adj, dp2, dp3);
    for (size_t i = 1; i <= n; i++)
    {
        std::cout << dp3[i] << " \n"[i == n];
    }
    return 0;
}
