#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void dfs(int u, int p, vector<vector<int>> &adj, vector<int> &dp)
{
    for (int v : adj[u])
    {
        if (v == p)
            continue;
        dfs(v, u, adj, dp);
        dp[u] = max(dp[u], 1 + dp[v]);
    }
}

void dfs2(int u, int p, vector<vector<int>> &adj, vector<int> &dp, vector<int> &dp2)
{
    int mx1 = -1, mx2 = -1;

    for (int v : adj[u])
    {
        if (v == p)
            continue;
        if (dp[v] >= mx1)
        {
            mx2 = mx1;
            mx1 = dp[v];
        }
        else if (dp[v] > mx2)
        {
            mx2 = dp[v];
        }
    }
    if (mx1 == -1)
        return;
    for (int v : adj[u])
    {
        if (v == p)
            continue;

        int best_sibling = (dp[v] == mx1 ? mx2 : mx1);
        int from_sibling = (best_sibling == -1 ? 0 : 2 + best_sibling);
        dp2[v] = max(1 + dp2[u], from_sibling);
        dfs2(v, u, adj, dp, dp2);
    }
}

void solve()
{
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> dp(n + 1, 0), dp2(n + 1, 0);

    dfs(1, 0, adj, dp);
    dfs2(1, 0, adj, dp, dp2);

    for (int i = 1; i <= n; i++)
        cout << max(dp[i], dp2[i]) << " ";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}