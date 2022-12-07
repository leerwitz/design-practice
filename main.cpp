#include <iostream>
#include "Graph.hpp"
#include <vector>

int main() {
    int N;
    int M;
    std:: cin >> N; //Вввод количества вершин графа
    std:: cin >> M; // Ввод количества ребер графа
    auto edges =  std::vector<Edge>(M);
   for (int i = 0; i < M; ++i) {
        std:: cin >> edges[i].src; // Начало ребра
        std:: cin >> edges[i].dest; // Конец ребра
        //edges[i].src = i;
        //edges[i].dest = i + 1;
    }


    Graph graph = Graph(edges, M, N);
    graph.TopologicalSort();

    return 0;
}
