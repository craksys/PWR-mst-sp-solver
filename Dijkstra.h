#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "Graph.h"

class NodeDijkstra
{
public:
    int distance_to_node; // odległość do wierzchołka z wierzchołka początkowego
    int index;            // index wierzchołka
};

class NodeDijkstraComparator
{
public:
    bool operator()(NodeDijkstra node1, NodeDijkstra node2)
    {
        return node1.distance_to_node > node2.distance_to_node;
    }
};

void dijkstraMatrix(Graph &graph);

void dijkstraList(Graph &graph);

#endif /* DIJKSTRA_H_ */
