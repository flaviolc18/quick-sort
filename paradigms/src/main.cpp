#include <iostream>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>

std::pair<int, int> solve_dp(int n, int W, int Vn[], int Wn[])
{

  std::pair<int, int> opt[W + 1] = {std::make_pair(0, 0)};

  for (int i = 0; i < n; i++)
    for (int j = W; j >= Wn[i]; j--)
      if (Vn[i] + opt[j - Wn[i]].first >= opt[j].first)
        opt[j] = std::make_pair(Vn[i] + opt[j - Wn[i]].first, opt[j - Wn[i]].second + 1);
      else
        opt[j] = std::make_pair(opt[j].first, opt[j].second);

  return opt[W];
}

bool compare(std::pair<int, int> const &i1, std::pair<int, int> const &i2)
{
  return ((double)i1.first / i1.second > (double)i2.first / i2.second);
}

std::pair<int, int> solve_greedy(int n, int W, int Vn[], int Wn[])
{
  std::pair<int, int> sorted[n];
  for (int i = 0; i < n; i++)
    sorted[i] = std::make_pair(Vn[i], Wn[i]);

  std::sort(sorted, sorted + n, compare);

  int days = 0, pts = 0, cash = W;
  for (int i = 0; i < n && cash > 0; i++)
  {
    int val = sorted[i].first, cost = sorted[i].second;

    if (cost <= cash)
    {
      days += cash / cost;
      pts += val * (cash / cost);
      cash %= cost;
    }
  }

  return std::make_pair(pts, days);
}

int main(int argc, char **argv)
{
  if (argc < 2)
    return 0;

  int available_cash;
  int qtd_islands;

  std::ifstream file;
  file.open(argv[1]);

  file >> available_cash >> qtd_islands;

  int costs[qtd_islands];
  int points[qtd_islands];
  for (int i = 0; i < qtd_islands; i++)
    file >> costs[i] >> points[i];

  file.close();

  std::pair<int, int> res_greedy = solve_greedy(qtd_islands, available_cash, points, costs);
  std::cout << res_greedy.first << " " << res_greedy.second << std::endl;

  std::pair<int, int> res_dp = solve_dp(qtd_islands, available_cash, points, costs);
  std::cout << res_dp.first << " " << res_dp.second << std::endl;

  return 0;
}
