#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

vector<int> res;
vector<vector<int>> adj;
vector<int> colors;

set<int> *dfs(int u, int p)
{
    set<int> *curSet = new set<int>();
    curSet->insert(colors[u]);

    for (int v : adj[u])
    {
        if (v == p)
            continue;

        set<int> *childSet = dfs(v, u);

        if (childSet->size() > curSet->size())
        {
            swap(curSet, childSet);
        }

        for (const int &x : *childSet)
        {
            curSet->insert(x);
        }

        delete childSet;
    }

    res[u] = curSet->size();
    return curSet;
}

void solve()
{
    int n;
    cin >> n;

    colors.assign(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> colors[i];
    }

    adj.assign(n + 1, {});
    for (int i = 1; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    res.assign(n + 1, 0);
    dfs(1, 0);

    for (int i = 1; i <= n; i++)
    {
        cout << res[i] << " ";
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
