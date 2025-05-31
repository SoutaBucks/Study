/*
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

struct Ingredient {
    int p, f, s, v, c;
};

int n, mp, mf, ms, mv;
vector<Ingredient> ingredients;

int best_cost = INT_MAX;
int best_sum = -1;
vector<int> best_comb;

void dfs(int idx, int tp, int tf, int ts, int tv, int cost, vector<int>& selected) {
  // 가지치기
  if (cost > best_cost) return;
  if (idx == n) {
    if (tp >= mp && tf >= mf && ts >= ms && tv >= mv) {
      int total = tp + tf + ts + tv;
      if (
              cost < best_cost ||
              (cost == best_cost && total > best_sum) ||
              (cost == best_cost && total == best_sum && selected < best_comb)
              ) {
        best_cost = cost;
        best_sum = total;
        best_comb = selected;
      }
    }
    return;
  }

  // 1. 현재 재료 선택 안함
  dfs(idx + 1, tp, tf, ts, tv, cost, selected);

  // 2. 현재 재료 선택
  selected.push_back(idx + 1); // 1-based
  Ingredient& ing = ingredients[idx];
  dfs(idx + 1, tp + ing.p, tf + ing.f, ts + ing.s, tv + ing.v, cost + ing.c, selected);
  selected.pop_back();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  cin >> mp >> mf >> ms >> mv;

  ingredients.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> ingredients[i].p >> ingredients[i].f >> ingredients[i].s >> ingredients[i].v >> ingredients[i].c;
  }

  vector<int> path;
  dfs(0, 0, 0, 0, 0, 0, path);

  if (best_comb.empty()) cout << "0\n";
  else {
    for (int i = 0; i < best_comb.size(); ++i) {
      if (i) cout << " ";
      cout << best_comb[i];
    }
    cout << "\n";
  }
  return 0;
}
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Ingredient {
    int p, f, s, v, c;
};

struct Subset {
    int p, f, s, v, cost;
    vector<int> indices;

    bool dominates(const Subset& other) const {
      return p >= other.p && f >= other.f && s >= other.s && v >= other.v && cost <= other.cost &&
             (p > other.p || f > other.f || s > other.s || v > other.v || cost < other.cost);
    }

    bool satisfies(int mp, int mf, int ms, int mv) const {
      return p >= mp && f >= mf && s >= ms && v >= mv;
    }

    int nutrition_sum() const {
      return p + f + s + v;
    }

    bool operator<(const Subset &other) const {
      if (cost != other.cost) return cost < other.cost;
      if (nutrition_sum() != other.nutrition_sum()) return nutrition_sum() > other.nutrition_sum();
      return indices < other.indices;
    }
};

vector<Subset> generate_subsets(const vector<Ingredient>& items, int offset) {
  int n = items.size();
  vector<Subset> subsets;

  for (int mask = 0; mask < (1 << n); ++mask) {
    int tp = 0, tf = 0, ts = 0, tv = 0, tc = 0;
    vector<int> idx;
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        tp += items[i].p;
        tf += items[i].f;
        ts += items[i].s;
        tv += items[i].v;
        tc += items[i].c;
        idx.push_back(offset + i + 1);  // 1-based
      }
    }
    subsets.push_back({tp, tf, ts, tv, tc, idx});
  }
  return subsets;
}

vector<Subset> pareto_filter(vector<Subset>& sets) {
  sort(sets.begin(), sets.end(), [](const Subset& a, const Subset& b) {
      return make_tuple(a.p, a.f, a.s, a.v, -a.cost) > make_tuple(b.p, b.f, b.s, b.v, -b.cost);
  });

  vector<Subset> result;
  for (const auto& s : sets) {
    bool dominated = false;
    for (const auto& r : result) {
      if (r.dominates(s)) {
        dominated = true;
        break;
      }
    }
    if (!dominated) result.push_back(s);
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  int mp, mf, ms, mv;
  cin >> n >> mp >> mf >> ms >> mv;

  vector<Ingredient> ingredients(n);
  for (int i = 0; i < n; ++i) {
    cin >> ingredients[i].p >> ingredients[i].f >> ingredients[i].s >> ingredients[i].v >> ingredients[i].c;
  }

  int mid = n / 2;
  vector<Ingredient> left(ingredients.begin(), ingredients.begin() + mid);
  vector<Ingredient> right(ingredients.begin() + mid, ingredients.end());

  vector<Subset> left_subs = pareto_filter(generate_subsets(left, 0));
  vector<Subset> right_subs = pareto_filter(generate_subsets(right, mid));

  Subset best = {0, 0, 0, 0, INT_MAX, {}};

  for (const auto& l : left_subs) {
    for (const auto& r : right_subs) {
      Subset total = {
              l.p + r.p, l.f + r.f, l.s + r.s, l.v + r.v,
              l.cost + r.cost,
              l.indices
      };
      total.indices.insert(total.indices.end(), r.indices.begin(), r.indices.end());
      sort(total.indices.begin(), total.indices.end());

      if (total.satisfies(mp, mf, ms, mv) && total < best)
        best = total;
    }
  }

  if (best.cost == INT_MAX) cout << "0\n";
  else {
    for (int i = 0; i < best.indices.size(); ++i) {
      if (i) cout << " ";
      cout << best.indices[i];
    }
    cout << "\n";
  }

  return 0;
}
