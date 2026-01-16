#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
#define endl '\n'
const int MOD = 32768;
const int mod = 1e9 + 7;
void dfs1(int u, int p, vector<vector<int>> &adj, vector<int> &dp1, vector<int> &dp2)
{
    dp1[u] = 1;
    dp2[u] = 0;
    for (int &v : adj[u])
    {
        if (v == p)
            continue;
        dfs1(v, u, adj, dp1, dp2);
        dp1[u] += dp1[v];
        dp2[u] += dp2[v] + dp1[v]; // dry run is important to understand this line
    }
}
void dfs2(int u, int p, vector<vector<int>> &adj, vector<int> &dp1, vector<int> &dp2, const int &totalNodes)
{
    for (int &v : adj[u])
    {
        if (v == p)
            continue;
        dp2[v] = dp2[u] - dp1[v] + (totalNodes - dp1[v]); // dry important for this line too
        dfs2(v, u, adj, dp1, dp2, totalNodes);
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
    vector<int> dp1(n + 1, 0), dp2(n + 1, 0); // dp1 is the no of nodes in subtree of v,
    //  dp2 is the sum of distances from node u to all nodes in its subtree
    dfs1(1, 0, adj, dp1, dp2);
    dfs2(1, 0, adj, dp1, dp2, n);
    for (int i = 1; i <= n; i++)
    {
        cout << dp2[i] << " \n"[i == n];
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}