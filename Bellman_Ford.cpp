#include <iostream>
#include <climits> // do INT_MAX

#include "Bellman_Ford.h"
#include "Graph.h"

using namespace std;

void bellmanFordMatrix(Graph &graph)
{
    int *distance = new int[graph.size_nodes]; // tablica na koszt dojścia do elementu
    int *prev = new int[graph.size_nodes];     // tablica na poprzedniki

    for (int i = 0; i < graph.size_nodes; i++)
    {
        distance[i] = INT_MAX; // maksymalne wartości
        prev[i] = -1;          // -1 oznacza brak poprzednika
    }
    distance[graph.start_node] = 0; //koszt dojścia do wierzchołka startowego
    bool change = false;            // zmienna przechowująca informacje o zmianach
    // pętla główna
    for (int i = 1; i < graph.size_nodes; i++)
    {
        change = true;
        for (int j = 0; j < graph.size_nodes; j++)
        {
            for (int k = 0; k < graph.size_nodes; k++) // dla każdego sąsiada wierzchołka j
            {
                if (graph.matrix[j][k] != 0 && distance[j] != INT_MAX) // czy istnieje krawędź i czy znamy koszt dojścia do obecnego elementu
                {
                    if (distance[k] > distance[j] + graph.matrix[j][k]) // warunek relaksacji krawędzi, jeżeli znaleziona droga do wierzchołka jest krótsza
                    {
                        change = false;                                 // zapamiętanie zmiany
                        distance[k] = distance[j] + graph.matrix[j][k]; // relaksacja
                        prev[k] = j;                                    // zmiana poprzednika
                    }
                }
            }
        }
        if (change) // jeśli w tym obiegu nie było żadnej zmiany to kończymy algorytm
            break;
    }
    // sprawdzenie czy nie wystąpił cykl ujemny
    for (int i = 0; i < graph.size_nodes; i++)
    {
        for (int j = 0; j < graph.size_nodes; j++)
        {
            if (graph.matrix[i][j] != 0)
            {
                if (distance[j] > distance[i] + graph.matrix[i][j])
                    change = false;
            }
        }
    }
    if (!change)
    {
        cout << "Cykl ujemny" << endl;
        delete[] distance;
        delete[] prev;
        return;
    }
    // wyświetlenie macierzy
    graph.printMatrix();
    // wyświetlany jest numer węzła, długość drogi do niego oraz droga w postaci sekwencji wierzchołków
    cout << endl
         << "Macierz Bellmana Forda: " << endl
         << "Start = " << graph.start_node << endl;
    cout << "Numer wezla : dystans -> sciezka" << endl;
    
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

void bellmanFordList(Graph &graph)
{
    Node *node;
    int *distance = new int[graph.size_nodes]; // tablica na koszt dojścia do elementu
    int *prev = new int[graph.size_nodes];     // tablica na poprzedniki

    for (int i = 0; i < graph.size_nodes; i++)
    {
        distance[i] = INT_MAX; // maksymalne wartości
        prev[i] = -1;          // -1 oznacza brak poprzednika
    }
    distance[graph.start_node] = 0; //koszt dojścia do wierzchołka startowego
    bool change = false;            // zmienna przechowująca informacje o zmianach
    // pętla główna
    for (int i = 1; i < graph.size_nodes; i++)
    {
        change = true;
        for (int j = 0; j < graph.size_nodes; j++)
        {
            for (node = graph.list[j]; node != NULL; node = node->next) // dla każdego sąsiada wierzchołka j
            {
                if (distance[node->value] > distance[j] + node->weight && distance[j] != INT_MAX) // czy istnieje krawędź i czy znamy koszt dojścia do obecnego elementu
                {
                    // warunek relaksacji krawędzi, jeżeli znaleziona droga do wierzchołka jest krótsza
                    change = false;                                     // zapamiętanie zmiany
                    distance[node->value] = distance[j] + node->weight; // relaksacja
                    prev[node->value] = j;                              // zmiana poprzednika
                }
            }
        }
        if (change) // jeśli w tym obiegu nie było żadnej zmiany to kończymy algorytm
            break;
    }
    // sprawdzenie czy nie wystąpił cykl ujemny
    for (int i = 0; i < graph.size_nodes; i++)
    {
        for (node = graph.list[i]; node != NULL; node = node->next)
        {
            if (distance[node->value] > distance[i] + node->weight)
                change = false;
        }
    }
    if (!change)
    {
        cout << "Cykl ujemny" << endl;
        delete[] distance;
        delete[] prev;
        return;
    }
    // wyświetlenie listy
    
    graph.printList();
    // wyświetlany jest numer węzła, długość drogi do niego oraz droga w postaci sekwencji wierzchołków
    cout << endl
         << "Lista Bellman Ford: " << endl
         << "Start = " << graph.start_node << endl;
    cout << "Numer wezla : dystans -> sciezka" << endl;
    
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
