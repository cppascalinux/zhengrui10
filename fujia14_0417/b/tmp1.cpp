#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <set>
using pii = std::pair<int, int>;
const int maxn = 105;
int n, m, tm[maxn];
namespace RS {
  const int maxno = 60 * 60 + 5;
  struct Edge {
    int u, v, cap, flow;
  };
  std::vector<int> G[maxno];
  std::vector<Edge> edges;
  inline void ins_edge(int u, int v, int f) {
    edges.push_back((Edge){u, v, f, 0});
    edges.push_back((Edge){v, u, 0, 0});
    int m = edges.size();
    G[u].push_back(m - 2);
    G[v].push_back(m - 1);
  }
  
  int d[maxno]; bool vis[maxno];
  int s, t;
  bool bfs() {
    memset(d, 0, sizeof(d));
    memset(vis, 0, sizeof(vis));
    d[s] = 1; vis[s] = true;
    std::queue<int> Q; Q.push(s);
    while(!Q.empty()) {
      int u = Q.front(); Q.pop();
      for(int id : G[u]) {
        Edge &e = edges[id];
        int v = e.v;
        if(e.cap > e.flow && !vis[v]) {
          d[v] = d[u] + 1;
          Q.push(v); vis[v] = true;
        }
      }
    }
    return vis[t];
  }
  int cur[maxno];
  int dfs(int x, int a) {
    if(a == 0 || x == t) return a;
    int fl = 0;
    for(int &i = cur[x]; i < G[x].size(); i ++) {
      Edge &e = edges[G[x][i]]; int v = e.v, f;
      if(d[v] == d[x] + 1 && (f = dfs(v, std::min(e.cap - e.flow, a))) > 0) {
        fl += f; a -= f;
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        if(!a) break;
      }
    }
    if(a > 0) d[x] = -1;
    return fl;
  }
  inline int dinic() {
    int ans = 0;
    while(bfs()) {
      memset(cur, 0, sizeof(cur));
      ans += dfs(s, 0x7fffffff);
    }
    return ans;
  }

  inline int get_id(int i, int j) {
    return (i - 1) * n + j;
  }
  inline int get_cost(int i, int val) {
    if(i != 1 && val == 0) return 0x7fffffff;
    int dl = val - tm[i];
    return (int)floor(10.00 * log(1 + 233 * dl * dl));
  }
  inline void solve() {
    s = n * n; t = s + 1;
    for(int i = 1; i <= n; i ++) {
      int las = s;
      for(int j = 0; j < n; j ++) {
        int np = get_id(i, j);
        ins_edge(las, np, get_cost(i, j));
        las = np;
      }
      ins_edge(las, t, get_cost(i, n));
    }
    ins_edge(get_id(1, 0), t, 0x7fffffff);
    while(m --) {
      int x, y; scanf("%d%d", &x, &y);
      for(int j = 1; j < n; j ++) {
        ins_edge(get_id(x, j), get_id(y, j - 1), 0x7fffffff);
        ins_edge(get_id(y, j), get_id(x, j - 1), 0x7fffffff);
      }
    }
    printf("%d\n", dinic());
  }
};

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i ++) {
    scanf("%d", &tm[i]);
  }
  RS::solve();
  return 0;
}