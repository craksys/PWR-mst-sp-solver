#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include "Graph.h"

using namespace std;

Graph::Graph()
{
    this->matrix = NULL;
    this->list = NULL;
    this->size_edges = 0;
    this->size_nodes = 0;
    this->start_node = 0;
}

Graph::~Graph()
{
    deleteStructure();
}

void Graph::deleteStructure()
{
    Node *to_delete;
    Node *temp;
    for (int i = 0; i < this->size_nodes; i++)
    {
        delete[] this->matrix[i];
        temp = this->list[i];
        while (temp != NULL)
        {
            to_delete = temp;
            temp = temp->next;
            delete to_delete;
        }
    }
    delete[] this->matrix;
    delete[] this->list;
    this->size_edges = 0;
    this->size_nodes = 0;
}

void Graph::makeGraph(int size) // utworzenie macierzy i wypełnienie jej zerami
{
    this->size_nodes = size;
    this->matrix = new int *[size];

    for (int i = 0; i < size; i++) // utworzenie wierszy
        this->matrix[i] = new int[size];
    // utworzenie listy
    this->list = new Node *[size_nodes];       // utworzenie listy wierzchołków
    for (int i = 0; i < this->size_nodes; i++) // wypełnienie jej nullami
        this->list[i] = NULL;
    fillZeros();
}

void Graph::fillZeros() // wypełnia macierz zerami - brak krawędzi
{
    for (int i = 0; i < size_nodes; i++)
        for (int j = 0; j < size_nodes; j++)
            this->matrix[i][j] = 0;
}

void Graph::print()
{
    if (size_nodes == 0)
    {
        cout << "Graf nie istnieje" << endl;
        return;
    }
    printMatrix();
    printList();
}

void Graph::printMatrix()
{
    // printowanie macierzy
    cout << endl
         << "Macierz" << endl
         << " ";
    for (int i = 0; i < this->size_nodes; i++)
        cout << "   " << i;
        cout<< endl; // kolumny
    for (int i = 0; i < this->size_nodes; i++)
    {
        cout << i << "   "; // wiersze
        for (int j = 0; j < this->size_nodes; j++)
        {
            if (this->matrix[i][j] == 0) // nie wypisuj 0 czyli braku krawędzi
            {
                cout << this->matrix[i][j] << "   ";
            }
            else
            {
                cout << this->matrix[i][j] << "   ";
            }
        }
        cout << endl;
    }
}

void Graph::printList()
{
    // Printowanie listy sąsiedztwa
    cout << endl
         << "Lista" << endl;
    Node *p;
    for (int i = 0; i < size_nodes; i++)
    {
        cout
            << i <<  ":"; // numer wierzchołka
        p = this->list[i];
        while (p)
        {
            cout << "  " << p->value << "[" << p->weight << "]"; // jego sąsiedzi i wagi
            p = p->next;
        }
        cout << endl;
    }
}

void Graph::printMSTMatrix()
{
    int weight;
    cout << endl << "Krawedz     Waga\n";
    for (int i = 0; i < size_nodes; i++)
    {
        for (int j = 0; j < i; j++)
        {
            weight = this->matrix[i][j]; // dla każdej krawędzi
            if (weight != 0)             // jeśli istnieje to dodaj do listy
            {
                cout << "(" << i << ", " << j << ")   " << weight << endl;
            }
        }
    }
}

void Graph::printMSTList()
{
    int weight, j;
    cout << endl
         << "Krawedz     Waga\n";
    Node *p;
    for (int i = 0; i < size_nodes; i++)
    {
        p = this->list[i];
        while (p)
        {
            weight = p->weight;
            j = p->value;
            if (j < i)
            {
                cout << "(" << i << ", " << j << ")   " << weight << endl;
            }
            p = p->next;
        }
    }
}

void Graph::randomStructure(int size, float density, int min, int max, bool directed)
{
    int max_index = size - 1;
    if (this->size_nodes != 0)
        deleteStructure();
    srand(time(NULL));
    int edges_amount = (size * (size - 1)) / 2 * density; // wyliczamy ilość krawędzi
    if (edges_amount < max_index)                         // jeśli krawędzi jest mniej niż wierzchołków
        edges_amount = max_index;                         // to zwiększamy tak aby połączyć wszystkie

    makeGraph(size);

    // tablica indeksów wierzchołków, wypełniona false, będzie true jeśli wierzchołek będzie już połączony
    bool *index_table = new bool[size];
    for (int i = 0; i < size; i++)
        index_table[i] = false;
    // Na początku trzeba utworzyć minimalne drzewo rozpinające
    int random_weight;
    int random_index = 0;
    int index = 0;
    for (int i = 0; i < max_index; i++)
    {
        index_table[index] = true; // wierzchołek do którego wcześniej doszliśmy jest odznaczony
        // wyszukiwanie wierzchołka który jeszcze nie jest podłączony
        do
        {
            random_index = rand() % size;    // losowy index
        } while (index_table[random_index]); // szukamy dopóki nie znajdziemy odpowiedniego
        // wagi krawędzi
        do
        {
            random_weight = rand() % (max - min + 1) + min; // od max to min
        } while (random_weight == 0);                       // waga nie może być równa 0

        //wypełnienie macierzy wagami
        this->matrix[index][random_index] = random_weight;
        if (!directed) // jeśli nieskierowana to dodać połączenie w drugą stronę
            this->matrix[random_index][index] = random_weight;

        index = random_index; // nowy indeks od którego wyjdziemy to ten wyżej wylosowany
    }
    // sprawdzenie czy należy dodać więcej krawędzi
    if (edges_amount != max_index)
    {
        int line, column;
        int if_directed = 2;
        if (!directed)
            if_directed = 1;

        // dodanie reszty krawędzi
        for (int i = max_index; i < edges_amount * if_directed; i++)
        {
            do
            {
                random_weight = rand() % (max - min + 1) + min; // od max to min
            } while (random_weight == 0);                       // waga nie może być równa 0
            while (true)                                        // dopóki nie znajdziemy miejsca w którym nie ma krawędzi
            {
                line = rand() % size;
                column = rand() % size;
                if (this->matrix[line][column] == 0 && line != column)
                    break;
            }
            this->matrix[line][column] = random_weight;
            if (!directed)
                this->matrix[column][line] = random_weight;
        }
    }
    delete[] index_table;
    this->size_edges = edges_amount;
    matrixToList();
    print();
}



void Graph::matrixToList() // przepisanie wartości z macierzy do listy
{
    Node *node;
    int weight;
    for (int i = 0; i < size_nodes; i++)
        for (int j = 0; j < size_nodes; j++)
        {
            weight = this->matrix[i][j]; // dla każdej krawędzi
            if (weight != 0)             // jeśli istnieje to dodaj do listy
            {
                node = new Node; // nowy wierzchołek
                node->value = j; // wierzchołek końcowy
                node->weight = weight;
                node->next = this->list[i]; // nextem jest obecnie najnowszy element listy
                this->list[i] = node;       // najnowszym elementem listy jest obecny element
            }
        }
}
