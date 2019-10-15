#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
        opt[i][w] = std::max(Vn[i - 1] + opt[i - 1][w - Wn[i - 1]], opt[i - 1][w]);
    }
  }

  int res = opt[n][W];
  int items = 0;
  int w = W;
  for (int i = n; i > 0 && res > 0; i--)
  {
    if (res == opt[i - 1][w])
      continue;
    else
    {
      items++;
      res = res - Vn[i - 1];
      w = w - Wn[i - 1];
    }
  }

  return std::make_pair(opt[n][W], items);
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

  int weights[qtd_islands];
  int points[qtd_islands];
  for (int i = 0; i < qtd_islands; i++)
    file >> weights[i] >> points[i];

  file.close();

  std::pair<int, int> res_dp = solve_dp(qtd_islands, available_cash, points, weights);
  std::cout << res_dp.first << " " << res_dp.second << std::endl;

  return 0;
}
