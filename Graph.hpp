#pragma once

#include <iostream>
#include <stack>
#include <vector>

// Структура данных для хранения узлов списка смежности
struct Node{
    int val;
    Node* next;
};


// Структура данных для хранения ребра Graph
struct Edge {
    int src, dest;
};
// Структура данных для определения посещенных вершин
struct Visited {
    bool atAll = false, InCycle = false;
};

class Graph
{
    // Функция выделения нового узла для списка смежности
    Node* getAdjListNode(int dest, Node* head)
    {
        Node* newNode = new Node;
        newNode->val = dest;

        // указываем новый узел на текущую голову
        newNode->next = head;

        return newNode;
    }

    int V;    // общее количество вершин в Graph

public:

    // Массив указателей на Node для представления
    // список смежности
    Node **head;

    // Конструктор
    Graph(std::vector<Edge> edges, int M, int V)
    {
        // выделить память
        head = new Node*[V]();
        this->V = V;

        // инициализируем головной указатель для всех вершин
        for (unsigned i = 0; i < V; ++i) {
            head[i] = nullptr;
        }

        // добавляем ребра в ориентированный graph
        for (unsigned i = 0; i < M; ++i)
        {
            int& src = edges[i].src;
            int& dest = edges[i].dest;

            // вставляем в начало
            Node* newNode = getAdjListNode(dest, head[src]);

            // указываем головной указатель на новый узел
            head[src] = newNode;


        }
    }
    // деструктор
    ~Graph() {
        for (unsigned i = 0; i < V; i++) {
            delete[] head[i];
        }

        delete[] head;
    }
    // реалезация поиска в глубину
    void TopologicalSortUtil(int v, Visited *vis,  std::stack<int> & Stack){
        vis[v].atAll = true;
        vis[v].InCycle = true;
        // пока смежные вершины не кончатся
        while (head[v] != nullptr){
            // если в графе имеется цикл немедленная остановка сортировки
            if (vis[head[v]->val].InCycle){
                this->V = -1;
                break;
            }
            // если смежная вершина никогда не посещалась применяем к ней DFS
            else if (!vis[head[v]->val].atAll)
                TopologicalSortUtil(head[v]->val, vis,Stack);
            head[v] = head[v]->next;
        }
        Stack.push(v);
        vis[v].InCycle = false;
    }

    // топологическая сортировка
    void TopologicalSort(){
        std::stack<int> Stack;

        //auto visited = std::vector<bool>(V, false);
        //auto VisitedInCycle = std::vector<bool>(V, false);
        //bool *visited = new bool [V];
        //bool *VisitedInCycle = new bool [V];
        /*for (unsigned i = 0; i < V; ++i) {
            visited[i] = false;
            VisitedInCycle[i] = false;
        }*/
        auto vis = new Visited[V];
        // применяем метод DFS к каждое вершине графа
        for (unsigned i = 0; i < V; ++i) {
            if (!vis[i].atAll)
                TopologicalSortUtil(i, vis, Stack);
            if (this->V == -1)
                break;
        }
        //если граф циклический выводим -1
        if (this->V == -1)
            std::cout << V;
        else
            //иначе выводим  отсортированные вершины
            while (Stack.empty() == false)
            {
                std::cout << Stack.top() << " ";
                Stack.pop();
            }
    }

};