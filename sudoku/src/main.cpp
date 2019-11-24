#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#define MAX 9

using namespace std;

void print(int colors[], int N)
{
  for (int i = 0; i < N * N; i++)
  {
    if (i > 0 && i % N == 0)
      cout << endl;
    cout << colors[i] << " ";
  }
  cout << endl;
}

int vertex(int i, int j, int N)
{
  return i * N + j;
}

void transform(int matrix[][MAX], int graph[][MAX * MAX], int N, int C, int R)
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
      // position of the vertex (i, j) on the adj matrix
      int v1 = vertex(i, j, N);

      // for each same row vertex
      for (int k = j + 1; k < N; k++)
      {
        int v2 = vertex(i, k, N);
        graph[v1][v2] = 1;
        graph[v2][v1] = 1;
      }

      // for each same column vertex
      for (int k = i + 1; k < N; k++)
      {
        int v2 = vertex(k, j, N);
        graph[v1][v2] = 1;
        graph[v2][v1] = 1;
      }

      // for each same quadrant vertex
      for (int k = i + 1; k < N && ceil((float)(i + 1) / R) == ceil((float)(k + 1) / R); k++)
      {
        for (int l = 0; l < N; l++)
        {
          if (ceil((float)(j + 1) / C) != ceil((float)(l + 1) / C))
            continue;

          int v2 = vertex(k, l, N);
          graph[v1][v2] = 1;
          graph[v2][v1] = 1;
        }
      }
    }
}

void setup_colors(int colors[], int matrix[][MAX], int N)
{
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (matrix[i][j] != 0)
        colors[vertex(i, j, N)] = matrix[i][j];
}

vector<int> find_adj_colors(int v, int colors[], int graph[][MAX * MAX], int N)
{
  std::vector<int> adj_colors(N, 0);

  for (int v1 = 0; v1 < N * N; v1++)
  {
    if (graph[v][v1])
      if (colors[v1])
        adj_colors[colors[v1] - 1] = 1;
  }

  return adj_colors;
}

int find_available_color(int v, int colors[], int graph[][MAX * MAX], int N)
{
  auto adj_colors = find_adj_colors(v, colors, graph, N);

  for (int i = 0; i < N; i++)
    if (!adj_colors[i])
      return i + 1;

  return -1;
}

int sat_degree(int v, int colors[], int graph[][MAX * MAX], int N)
{
  auto adj_colors = find_adj_colors(v, colors, graph, N);

  int s = 0;
  for (int i = 0; i < N; i++)
    s += adj_colors[i];
  return s;
}

int find_max_degree_vertex(int graph[][MAX * MAX], int colors[], int N)
{
  int max = -1;
  int index = -1;

  for (int v = 0; v < N * N; v++)
  {
    if (colors[v])
      continue;

    int d = sat_degree(v, colors, graph, N);
    if (d > max)
    {
      max = d;
      index = v;
    }
  }

  return index;
}

bool color_graph(int graph[][MAX * MAX], int colors[], int N)
{
  int colored = 0;

  for (int v = 0; v < N * N; v++)
    if (colors[v])
      colored++;

  while (colored < N * N)
  {
    int max_degree_vertex = find_max_degree_vertex(graph, colors, N);

    int color = find_available_color(max_degree_vertex, colors, graph, N);

    if (color == -1)
      return false;

    colors[max_degree_vertex] = color;
    colored++;
  }
  return true;
}

int main(int argc, char **argv)
{
  if (argc < 2)
    return 0;

  std::ifstream file;
  file.open(argv[1]);

  int N, I, J;

  file >> N >> I >> J;

  int matrix[MAX][MAX] = {0};
  int graph[MAX * MAX][MAX * MAX] = {0};

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      file >> matrix[i][j];

  int colors[MAX * MAX] = {0};

  setup_colors(colors, matrix, N);

  transform(matrix, graph, N, I, J);

  if (color_graph(graph, colors, N))
    cout << "solução" << endl;
  else
    cout << "sem solução" << endl;

  print(colors, N);

  return 0;
}
