#include <iostream>
#include <queue>
#include <vector>

#include "Prim.h"
#include "Graph.h"

using namespace std;

void primMatrix(Graph &graph)
{
    Graph graph_mst; // graf na wynik
    graph_mst.makeGraph(graph.size_nodes);
    // kolejka priorytetowa z typem Edge z vectorem jako typem sekwencji bazowej, EdgeComparator jako funkcja do porównywania
    priority_queue<Edge, vector<Edge>, EdgeComparator> Q;

    int minimum_cost = 0;
    int weight;
    Edge e;
    vector<bool> visited(graph.size_nodes, false); // vector, w którym ustawimy true jeśli wierzchołek jest już w mst
    int current_node = 0;
    visited[current_node] = true; // od tego zaczynamy

    for (int i = 1; i < graph.size_nodes; i++) // pętla tworząca drzewo
    {
        for (int j = 0; j < graph.size_nodes; j++) // wrzuć do kolejki każdą krawędź która tam jeszcze nie jest
        {
            weight = graph.matrix[current_node][j];
            if (weight != 0 && !visited[j])        // jeżeli istnieje i jeszcze nie jest w kolejce
                Q.push({weight, current_node, j}); // to wrzuć krawędź do kolejki
        }
        do
        {
            e = Q.top();
            Q.pop();             // pobieraj nową krawędź z kolejki
        } while (visited[e.to]); // dopóki nie będzie ona prowadziła do wierzchołka nie będącego w drzewie

        minimum_cost += e.weight;                  // sumuj koszt utworzenia drzewa
        graph_mst.matrix[e.from][e.to] = e.weight; // utwórz krawędź nieskierowaną w grafie na wynik
        graph_mst.matrix[e.to][e.from] = e.weight;
        visited[e.to] = true; // zaznacz że wierzchołek jest już odwiedzony
        current_node = e.to;  // zmień obecny wierzchołek
        graph_mst.size_edges++;
        if (graph_mst.size_edges >= graph.size_nodes - 1)
            break;
    }
    graph_mst.printMSTMatrix();
    cout << endl
         << "Suma wag (Prim): " << minimum_cost << endl;
}

void primList(Graph &graph)
{
    Node *node;
    Node *p;
    Graph graph_mst; // graf na wynik
    graph_mst.makeGraph(graph.size_nodes);
    // kolejka priorytetowa z typem Edge z vectorem jako typem sekwencji bazowej, EdgeComparator jako funkcja do porównywania
    priority_queue<Edge, vector<Edge>, EdgeComparator> Q;

    int minimum_cost = 0;
    Edge e;
    vector<bool> visited(graph.size_nodes, false); // vector, w którym ustawimy true jeśli wierzchołek jest już w mst
    int current_node = 0;
    visited[current_node] = true; // od tego zaczynamy

    for (int i = 1; i < graph.size_nodes; i++) // pętla tworząca drzewo
    {
        for (p = graph.list[current_node]; p != NULL; p = p->next) // wrzuć do kolejki każdą krawędź która tam jeszcze nie jest
        {
            if (!visited[p->value])                          // jeżeli jeszcze nie jest w kolejce
                Q.push({p->weight, current_node, p->value}); // to wrzuć krawędź do kolejki
        }
        do
        {
            e = Q.top();
            Q.pop();             // pobieraj nową krawędź z kolejki
        } while (visited[e.to]); // dopóki nie będzie ona prowadziła do wierzchołka nie będącego w drzewie

        minimum_cost += e.weight; // sumuj koszt utworzenia drzewa
        // utwórz wierzchołek i dodaj do listy
        node = new Node();
        node->weight = e.weight;
        node->value = e.to;
        node->next = graph_mst.list[e.from];
        graph_mst.list[e.from] = node;
        // nie jest skierowana więc dwa razy
        node = new Node();
        node->weight = e.weight;
        node->value = e.from;
        node->next = graph_mst.list[e.to];
        graph_mst.list[e.to] = node;

        visited[e.to] = true; // zaznacz że wierzchołek jest już odwiedzony
        current_node = e.to;  // zmień obecny wierzchołek
        graph_mst.size_edges++;
        if (graph_mst.size_edges >= graph.size_nodes - 1)
            break;
    }
    graph_mst.printMSTList();
    cout << endl
         << "Suma wag (Prim): " << minimum_cost << endl;
}
