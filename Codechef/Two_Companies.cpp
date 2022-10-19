#ifndef LOCAL
  #pragma GCC optimize("O3,unroll-loops")
  #pragma GCC target("avx2,abm,bmi,sse2,fpmath=sse")
#endif

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)


#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>


#include <vector>

namespace atcoder {

namespace internal {

template <class T> struct simple_queue {
    std::vector<T> payload;
    int pos = 0;
    void reserve(int n) { payload.reserve(n); }
    int size() const { return int(payload.size()) - pos; }
    bool empty() const { return pos == int(payload.size()); }
    void push(const T& t) { payload.push_back(t); }
    T& front() { return payload[pos]; }
    void clear() {
        payload.clear();
        pos = 0;
    }
    void pop() { pos++; }
};

}  // namespace internal

}  // namespace atcoder


namespace atcoder {

template <class Cap> struct mf_graph {
  public:
    mf_graph() : _n(0) {}
    explicit mf_graph(int n) : _n(n), g(n) {}

    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        int m = int(pos.size());
        pos.push_back({from, int(g[from].size())});
        int from_id = int(g[from].size());
        int to_id = int(g[to].size());
        if (from == to) to_id++;
        g[from].push_back(_edge{to, to_id, cap});
        g[to].push_back(_edge{from, from_id, 0});
        return m;
    }

    struct edge {
        int from, to;
        Cap cap, flow;
    };

    edge get_edge(int i) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        auto _e = g[pos[i].first][pos[i].second];
        auto _re = g[_e.to][_e.rev];
        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    std::vector<edge> edges() {
        int m = int(pos.size());
        std::vector<edge> result;
        for (int i = 0; i < m; i++) {
            result.push_back(get_edge(i));
        }
        return result;
    }
    void change_edge(int i, Cap new_cap, Cap new_flow) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto& _e = g[pos[i].first][pos[i].second];
        auto& _re = g[_e.to][_e.rev];
        _e.cap = new_cap - new_flow;
        _re.cap = new_flow;
    }

    Cap flow(int s, int t) {
        return flow(s, t, std::numeric_limits<Cap>::max());
    }
    Cap flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        std::vector<int> level(_n), iter(_n);
        internal::simple_queue<int> que;

        auto bfs = [&]() {
            std::fill(level.begin(), level.end(), -1);
            level[s] = 0;
            que.clear();
            que.push(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto e : g[v]) {
                    if (e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return;
                    que.push(e.to);
                }
            }
        };
        auto dfs = [&](auto self, int v, Cap up) {
            if (v == s) return up;
            Cap res = 0;
            int level_v = level[v];
            for (int& i = iter[v]; i < int(g[v].size()); i++) {
                _edge& e = g[v][i];
                if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
                Cap d =
                    self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));
                if (d <= 0) continue;
                g[v][i].cap += d;
                g[e.to][e.rev].cap -= d;
                res += d;
                if (res == up) return res;
            }
            level[v] = _n;
            return res;
        };

        Cap flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) break;
            std::fill(iter.begin(), iter.end(), 0);
            Cap f = dfs(dfs, t, flow_limit - flow);
            if (!f) break;
            flow += f;
        }
        return flow;
    }

    std::vector<bool> min_cut(int s) {
        std::vector<bool> visited(_n);
        internal::simple_queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            visited[p] = true;
            for (auto e : g[p]) {
                if (e.cap && !visited[e.to]) {
                    visited[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return visited;
    }

  private:
    int _n;
    struct _edge {
        int to, rev;
        Cap cap;
    };
    std::vector<std::pair<int, int>> pos;
    std::vector<std::vector<_edge>> g;
};

}  // namespace atcoder

using namespace atcoder;

struct LCA {
  vector<int> in, out, d;
  vector<vector<int>> p;
  
  LCA(const vector<vector<int>>& adj) {
    int n = sz(adj);
    in.resize(n);
    out.resize(n);
    d.resize(n);
    p.resize(n);
    int timer = 0;
    auto dfs = [&](auto self, int u) -> void {
      in[u] = timer++;
      p[u].reserve(d[u] ? __lg(d[u]) + 1 : 0);
      for (int i = 1; d[u] >> i; ++i) {
        p[u].emplace_back(p[p[u][i - 1]][i - 1]);
      }
      for (int v : adj[u]) {
        if (sz(p[u]) && v == p[u][0]) {
          continue;
        }
        p[v].emplace_back(u);
        d[v] = d[u] + 1;
        self(self, v);
      }
      out[u] = timer++;
    };
    dfs(dfs, 0);
  }
  
  bool is_p(int u, int v) const {
    return in[u] <= in[v] && out[v] <= out[u];
  }
  
  int lca(int u, int v) const {
    if (is_p(u, v)) {
      return u;
    }
    if (is_p(v, u)) {
      return v;
    }
    for (int i = sz(p[u]) - 1; i >= 0; --i) {
      if (sz(p[u]) > i && !is_p(p[u][i], v)) {
        u = p[u][i];
      }
    }
    return p[u][0];
  }
};

void solve() {
  int n, m1, m2;
  cin >> n >> m1 >> m2;
  vector<vector<int>> adj(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  LCA lca(adj);
  vector<array<int, 4>> r1(m1), r2(m2);
  for (auto& [u, v, w, p] : r1) {
    cin >> u >> v >> w;
    p = lca.lca(--u, --v);
  }
  for (auto& [u, v, w, p] : r2) {
    cin >> u >> v >> w;
    p = lca.lca(--u, --v);
  }
  const int s = m1 + m2;
  const int t = s + 1;
  mf_graph<int> g(t + 1);
  int ans = 0;
  for (int i = 0; i < m1; ++i) {
    g.add_edge(s, i, r1[i][2]);
    ans += r1[i][2];
  }
  for (int i = 0; i < m2; ++i) {
    g.add_edge(i + m1, t, r2[i][2]);
    ans += r2[i][2];
  }
  for (int i = 0; i < m1; ++i) {
    auto [u1, v1, w1, p1] = r1[i];
    for (int j = 0; j < m2; ++j) {
      auto [u2, v2, w2, p2] = r2[j];
      if ((lca.is_p(p1, p2) && (lca.is_p(p2, u1) || lca.is_p(p2, v1))) || (lca.is_p(p2, p1) && (lca.is_p(p1, u2) || lca.is_p(p1, v2)))) {
        g.add_edge(i, j + m1, INT_MAX);
      }
    }
  }
  cout << ans - g.flow(s, t) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin.exceptions(cin.failbit);
  int t = 1;
  // cin >> t;
  while (t--) solve();
  return 0;
}
