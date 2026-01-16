#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #define int long long
#define endl '\n'
int ans = 0;
void dfs(int u, int p, vector<vector<int>> &adj, vector<int> &dp)
{
    int mx1 = -1, mx2 = -1; // we have to take(mx1 and mx2) as -1 because
    // if we have take it as 0 then in case of leaf node depth will 0 so will not update
    // but ideally we should update for the leaf node 2+0+0=2 as shown  in the sample test case
    // in the cses problem statement Tree Diameter
    dp[u] = 0;
    for (int &v : adj[u])
    {
        if (v == p)
            continue;
        dfs(v, u, adj, dp);            // first dfs as we want dp[v] ready
        dp[u] = max(dp[u], 1 + dp[v]); // depth of child of subtree from leaf
        // not from the root if we did dp[v]=dp[u]+1
        // we want it from the leaf not root or parent
        if (mx1 < dp[v])
        {
            mx2 = mx1;
            mx1 = dp[v];
        }
        else if (mx2 < dp[v])
        {
            mx2 = dp[v];
        }
    }
    if (mx1 == -1 && mx2 == -1)
        return;
    if (mx1 != -1 && mx2 != -1)
    {
        ans = max(ans, 2 + mx1 + mx2); // calculating on the fly
        // dp2[u] = max(dp2[u], 2 + mx1 + mx2); // as dp2[v] represents max depth of children to leaf
        //  so the +1 from the u to their children is not added so we add +2 here
    }
    else
    {
        ans = max(ans, 1 + mx1);
        // dp2[u] = max(dp2[u], 1 + mx1);
    }
}

void solve()
{
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << 0 << endl;
        return;
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dp(n + 1, 0);
    dfs(1, 0, adj, dp);
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
