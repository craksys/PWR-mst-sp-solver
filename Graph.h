#ifndef GRAPH_H_
#define GRAPH_H_

struct Edge
{
    int weight;
    int from;
    int to;
};

class EdgeComparator
{
public:
    bool operator()(Edge edge1, Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

class Node
{
public:
    Node *next;
    int weight; // waga do nexta
    int value;  // wartość nexta
};

class Graph
{
public:
    int **matrix;
    Node **list;    // tablica dynamiczna dla listy sasiedztwa
    int size_edges; // ilość krawędzi
    int size_nodes; // ilość wierzchołków
    int start_node; // wierzchołek początkowy

public:
    Graph();
    ~Graph();
    void deleteStructure();
    void makeGraph(int size);
    void fillZeros();
    void print();
    void printMatrix();
    void printList();
    void printMSTMatrix();
    void printMSTList();
    void randomStructure(int size, float density, int min, int max, bool directed);
    void loadGraphFromFile(const char *filename, bool directed);
    void matrixToList();
};

#endif /* GRAPH_H_ */
