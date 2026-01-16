#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
#define endl '\n'
const int MOD = 32768;
const int mod = 1e9 + 7;
void dfs(int u, int p, vector<vector<int>> &adj, vector<vector<int>> &dp)
{
    vector<int> children;
    vector<int> childs;
    for (int &v : adj[u])
    {
        if (v == p)
            continue;
        dfs(v, u, adj, dp);
        children.push_back(max(dp[v][0], dp[v][1]));
        childs.push_back(v);
    }
    int n = (int)children.size();
    if (n == 0)
        return;
    vector<int> prefix(n, 0), suffix(n, 0);
    prefix[0] = children[0];
    suffix[n - 1] = children[n - 1];
    for (int i = 1; i < n; i++)
        prefix[i] = prefix[i - 1] + children[i];
    for (int i = n - 2; i >= 0; i--)
        suffix[i] = suffix[i + 1] + children[i];
    dp[u][0] = prefix.back();
    int c_no = 0;
    for (int i = 0; i < n; i++)
    {
        int left = c_no == 0 ? 0 : prefix[c_no - 1];
        int right = c_no == n - 1 ? 0 : suffix[c_no + 1];
        dp[u][1] = max(dp[u][1], 1 + dp[childs[c_no]][0] + left + right);
        c_no++;
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
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    dfs(1, 0, adj, dp);
    cout << max(dp[1][1], dp[1][0]) << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
