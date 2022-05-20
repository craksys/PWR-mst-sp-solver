#include <iostream>
#include <climits> // do INT_MAX
#include <queue>
#include <vector>

#include "Dijkstra.h"
#include "Graph.h"

using namespace std;

void dijkstraMatrix(Graph &graph)
{
    NodeDijkstra node_dijkstra; // wskaźnik na obiek z odległością do wierzchołka i jego indeksem, używany w kolejce
    int weight;
    bool check_if_negative = false; // jeśli wystąpią krawędzie ujemne

    int *distance = new int[graph.size_nodes]; // tablica na koszt dojścia do elementu
    int *prev = new int[graph.size_nodes];     // tablica na poprzedniki

    for (int i = 0; i < graph.size_nodes; i++)
    {
        distance[i] = INT_MAX; // maksymalne wartości
        prev[i] = -1;          // -1 oznacza brak poprzednika
    }
    distance[graph.start_node] = 0; //koszt dojścia do wierzchołka startowego

    // kolejka Q na wierzchołki
    priority_queue<NodeDijkstra, vector<NodeDijkstra>, NodeDijkstraComparator> Q;
    Q.push({distance[graph.start_node], graph.start_node}); // pierwszy wierzchołek do kolejki

    while (!Q.empty())
    {
        node_dijkstra = Q.top(); // wierzchołek o najniższym koszcie
        Q.pop();

        for (int j = 0; j < graph.size_nodes; j++) // dla każdego sąsiada wierzchołka node_dijkstra.index
        {
            weight = graph.matrix[node_dijkstra.index][j];
            if (weight != 0 && distance[j] > distance[node_dijkstra.index] + weight) // jezeli wierzchołek istnieje i jeśli niższy koszt
            {
                distance[j] = distance[node_dijkstra.index] + weight;
                prev[j] = node_dijkstra.index;
                Q.push({distance[j], j}); // wierzchołek do którego znaleziono drogę do kolejki
                if (weight < 0)           // jeśli wystąpi negatywna waga krawędzi
                {
                    check_if_negative = true;
                    break;
                }
            }
        }
        if (check_if_negative)
            break;
    }

    if (check_if_negative)
    {
        cout << "Negative weight" << endl;
        delete[] distance;
        delete[] prev;
        return;
    }
    // wyświetlenie macierzy
    graph.printMatrix();
    // wyświetlany jest numer węzła, długość drogi do niego oraz droga w postaci sekwencji wierzchołków
    cout << endl
         << "Dijkstra matrix: " << endl
         << "Start = " << graph.start_node << endl;
    cout << "Node number : distance -> path" << endl;

    for (int i = 0; i < graph.size_nodes; i++)
    {
        cout << i << ": " << distance[i] << " -> ";
        for (int j = i; j != -1; j = prev[j])
        {
            cout << j << " ";
        }
        cout << endl;
    }
    delete[] distance;
    delete[] prev;
}

void dijkstraList(Graph &graph)
{
    NodeDijkstra node_dijkstra; // wskaźnik na obiek z odległością do wierzchołka i jego indeksem, używany w kolejce
    Node *node;
    bool check_if_negative = false; // jeśli wystąpią krawędzie ujemne

    int *distance = new int[graph.size_nodes]; // tablica na koszt dojścia do elementu
    int *prev = new int[graph.size_nodes];     // tablica na poprzedniki

    for (int i = 0; i < graph.size_nodes; i++)
    {
        distance[i] = INT_MAX; // maksymalne wartości
        prev[i] = -1;          // -1 oznacza brak poprzednika
    }
    distance[graph.start_node] = 0; //koszt dojścia do wierzchołka startowego

    // kolejka Q na wierzchołki
    priority_queue<NodeDijkstra, vector<NodeDijkstra>, NodeDijkstraComparator> Q;
    Q.push({distance[graph.start_node], graph.start_node}); // pierwszy wierzchołek do kolejki

    while (!Q.empty())
    {
        node_dijkstra = Q.top(); // wierzchołek o najniższym koszcie
        Q.pop();

        for (node = graph.list[node_dijkstra.index]; node != NULL; node = node->next) // dla każdego sąsiada wierzchołka node
        {
            if (distance[node->value] > distance[node_dijkstra.index] + node->weight) // jeśli niższy koszt
            {
                distance[node->value] = distance[node_dijkstra.index] + node->weight;
                prev[node->value] = node_dijkstra.index;
                Q.push({distance[node->value], node->value}); // wierzchołek do którego znaleziono drogę do kolejki
                if (node->weight < 0)                         // jeśli wystąpi negatywna waga krawędzi
                {
                    check_if_negative = true;
                    check_if_negative = true;
                    break;
                }
            }
        }
        if (check_if_negative)
            break;
    }

    if (check_if_negative)
    {
        cout << "Negative weight" << endl;
        delete[] distance;
        delete[] prev;
        return;
    }
    // wyświetlenie listy
    graph.printList();
    // wyświetlany jest numer węzła, długość drogi do niego oraz droga w postaci sekwencji wierzchołków
    cout << endl
         << "Dijkstra list: " << endl
         << "Start = " << graph.start_node << endl;
    cout << "Node number : distance -> path" << endl;

    for (int i = 0; i < graph.size_nodes; i++)
    {
        cout << i << ": " << distance[i] << " -> ";
        for (int j = i; j != -1; j = prev[j])
        {
            cout << j << " ";
        }
        cout << endl;
    }
    delete[] distance;
    delete[] prev;
}
