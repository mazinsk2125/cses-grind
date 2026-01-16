#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
#define endl '\n'
const int MOD = 32768;
const int mod = 1e9 + 7;
void dfs(int u, int p, vector<vector<int>> &adj, vector<int> &dp)
{
    dp[u] = 1;
    for (int &v : adj[u])
    {
        if (u == p)
            continue;
        dfs(v, u, adj, dp);
        dp[u] += dp[v];
    }
}
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) // important as 1 is the general director of the company can never be subordinate
    {
        int a;
        cin >> a;
        adj[a].push_back(i);
    }
    vector<int> dp(n + 1, 0);
    dfs(1, 0, adj, dp);
    for (int i = 1; i <= n; i++)
    {
        cout << max(0LL, dp[i] - 1) << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}