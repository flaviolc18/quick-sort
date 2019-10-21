#include <iostream>
#include <fstream>
#include <algorithm>

std::pair<int, int> solve_dp(int n, int W, int Vn[], int Wn[])
{
  // OBS: a posição 0 das duas dimensões é usada para o caso base
  // ou seja, os arranjos de soluções de fato começam na posição 1
  // para compensar, ao acessar os arranjos Vn e Wn (os quais começam em 0) usamos (i - 1)
  int opt[n + 1][W + 1];

  for (int i = 0; i <= n; i++)
  {
    for (int w = 0; w <= W; w++)
    {
      // casos base
      if (i == 0 || w == 0)
        opt[i][w] = 0;
      // se o peso for maior que o total permitido não o incluimos
      else if (Wn[i - 1] > w)
        opt[i][w] = opt[i - 1][w];
      else
        // caso contrário pegamos o máximo entre a solução q inclui e a q não inclui Vn[i]
        // descontando Wn[i] do máximo permitido
        opt[i][w] = std::max(opt[i - 1][w], Vn[i - 1] + opt[i - 1][w - Wn[i - 1]]);
    }
  }

  int items = 0;
  int res = opt[n][W];
  // para achar a quantidade de itens começamos avaliando o topo da matriz solução
  for (int i = n, w = W; i > 0 && res > 0; i--)
  {
    // se Vn[i-1] está presente na solução ótima, então a relação abaixo é verdadeira
    if (res == Vn[i - 1] + opt[i - 1][w - Wn[i - 1]])
    {
      items++;
      res = res - Vn[i - 1];
      w = w - Wn[i - 1];
    }
  }

  return std::make_pair(opt[n][W], items);
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
