#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 1, M = 20;
vector<int> g[N];
int dep[N], arr[N];
pair<int, int> par[N][M]; // binary lifting table for every node and its kth parent values

void dfs(int node, int parent)
{

    for (int i = 0; i < M; i++)
    {
        par[node][i] = {0, INT_MAX};
    }
    dep[node] = dep[parent] + 1;
    par[node][0] = {parent, min(arr[node], arr[parent])};

    for (int j = 1; j < M; j++)
    {
        par[node][j] = {par[par[node][j - 1].first][j - 1].first,
                        min(par[node][j - 1].second, par[par[node][j - 1].first][j - 1].second)};
    }

    for (auto x : g[node])
    {
        if (x != parent)
        {
            dfs(x, parent);
        }
    }
}

int Min(int u, int v)
{
    int Mn = min(arr[u], arr[v]);
    if (dep[u] < dep[v])
        swap(u, v);
    int diff = dep[u] - dep[v];

    for (int j = M - 1; j >= 0; j--)
    {
        if ((1 << j) & diff)
        {
            Mn = min(Mn, par[u][j].second);
            u = par[u][j].first;
        }
    }
    if (u == v)
        return Mn;

    for (int j = M - 1; j >= 0; j--)
    {
        if (par[u][j].first != par[v][j].first)
        {
            Mn = min(Mn, min(par[u][j].second, par[v][j].second));
        }

        u = par[u][j].first;
        v = par[v][j].first;
    }

    Mn = min(Mn, par[u][0].second);
    Mn = min(Mn, par[v][0].second);

    return Mn;
}
