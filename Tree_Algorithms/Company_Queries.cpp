#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
#define endl '\n'
const int MOD = 32768;
const int mod = 1e9 + 7;
const int LOG = 18;
int lca(int node, int &k, vector<vector<int>> &dp)
{
    for (int j = 0; j < LOG; j++)
    {
        if (k & (1LL << j))
        {
            if (node == -1)
                break;
            node = dp[node][j];
        }
    }
    return node;
}
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    vector<int> parent(n + 1);
    for (int i = 2; i <= n; i++)
    {
        int b;
        cin >> b;
        adj[b].push_back(i);
        parent[i] = b;
    }
    vector<vector<int>> dp(n + 1, vector<int>(LOG, -1));
    for (int i = 1; i <= n; i++)
        dp[i][0] = parent[i];
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < 18; j++)
        {
            if (dp[i][j - 1] != -1)
            {
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            }
        }
    }
    while (q--)
    {
        int x, k;
        cin >> x >> k;
        int ans = lca(x, k, dp);
        cout << (ans == 0 ? -1 : ans) << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}