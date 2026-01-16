#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #define int long long
#define endl '\n'
const int MOD = 32768;
const int mod = 1e9 + 7;
void dfs1(int u, int p, vector<vector<int>> &adj, vector<int> &dp1)
{
    dp1[u] = 0;
    for (int &v : adj[u])
    {
        if (v == p)
            continue;
        dfs1(v, u, adj, dp1);
        dp1[u] = max(dp1[u], dp1[v] + 1);
    }
}
void dfs2(int u, int p, vector<vector<int>> &adj, int par_ans, vector<int> &dp1, vector<int> &dp2)
{
    vector<int> prefix, suffix, child;
    for (int &v : adj[u])
    {
        if (v == p)
            continue;
        child.push_back(dp1[v] + 1);
    }
    int n = (int)child.size();
    if (n == 0)
    {
        dp2[u] = par_ans;
        return;
    }
    prefix.resize(n);
    suffix.resize(n);
    prefix[0] = child[0];
    for (int i = 1; i < n; i++)
        prefix[i] = max(prefix[i - 1], child[i]);
    suffix[n - 1] = child[n - 1];
    for (int i = n - 2; i >= 0; i--)
        suffix[i] = max(suffix[i + 1], child[i]);
    dp2[u] = max(dp1[u], par_ans);
    int c_no = 0;
    for (int &v : adj[u])
    {
        if (v == p)
            continue;
        int left = c_no == 0 ? 0 : prefix[c_no - 1];
        int right = c_no == n - 1 ? 0 : suffix[c_no + 1];
        int nextUp = 1 + max(par_ans, max(left, right));
        dfs2(v, u, adj, nextUp, dp1, dp2);
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
    vector<int> dp1(n + 1, 0); // this calcuates the max depth of each subtree childs v's
    dfs1(1, 0, adj, dp1);
    vector<int> dp2(n + 1, 0);
    dfs2(1, 0, adj, 0, dp1, dp2); // par_ans is parAnsOfParentIfThisSubtreeNodeIsExcluded
    for (int i = 1; i <= n; i++)
    {
        cout << dp2[i] << " ";
    }
}

int main()
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