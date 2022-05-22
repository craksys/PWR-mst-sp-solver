#include <iostream>
#include <limits>
#include <windows.h>
#include <iomanip>

#include "Graph.h"
#include "Bellman_Ford.h"
#include "Prim.h"
#include "Kruskal.h"


using namespace std;

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
void MST()
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	Graph graph;
	int action;
	int value;
	int min_weight, max_weight;
	float density;
	bool directed = false;
	do
	{
		cout << endl << "Wybierz typ operacji:" << endl;
		cout << "1. Wyswietl graf " << endl;
		cout << "2. Wygeneruj losowy graf " << endl;
		cout << "3. Algorytm Prima " << endl;
		cout << "4. Algorytm Kruskala " << endl;
		cout << "5. Wyjscie " << endl;
		cin.clear();
		cin >> action;
		cout << endl;
		switch (action)
		{
		case 1: // wypisanie
			graph.print();
			break;
		case 2: // utworzenie losowego
			cout << "Wybierz liczbe wezlow: ";
			cin >> value;
			if (value <= 0)
			{
				cout << "Bledna liczba wezlow" << endl;
				break;
			}
			cout << "Wybierz gestosc z zakresu <0,1> po kropce " << endl;
			cout << "Wybierz gestosc: ";
			cin >> density;
			if (density < 0 || density > 1)
			{
				cout << "Bledna gestosc" << endl;
				break;
			}
			//cout << "Wybierz wage minimalna: ";
			//cin >> min_weight;
			//cout << "Wybierz wage maksymalna: ";
			//cin >> max_weight;
			min_weight = 1;
			max_weight = 50;
			cout << endl;

			/*
			if (min_weight < 0 || max_weight < 0)
			{
				cout << "Waga musi byc liczba dodatnia" << endl;
				break;
			}*/

			graph.randomStructure(value, density, min_weight, max_weight, directed);
			break;

		case 3: // Prim
				primMatrix(graph);
				primList(graph);
				break;
		case 4: // Kruskal
				kruskalMatrix(graph);
				kruskalList(graph);
			
			break;
		case 5: // wyjście
			break;
		default:
			cout << "Bledny wybor" << endl;
			break;
		}
	} while (action != 6);
}

void menuPath()
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	Graph graph;
	int action;
	int value;
	int starts;
	int min_weight, max_weight;
	char filename[50];
	float density;
	bool directed = true;
	do
	{
		cout << endl
			 << "Wybierz typ operacji: " << endl;
		cout << "1. Wyswietl graf " << endl;
		cout << "2. Wygeneruj losowy graf " << endl;
		cout << "3. Algorytm Bellman-Ford " << endl;
		cout << "4. Wyjscie " << endl;
		cin.clear();
		cin >> action;
		cout << endl;
		switch (action)
		{
		case 1: // wypisanie
			graph.print();
			break;
		case 2: // utworzenie losowego
			cout << "Wybierz liczbe wezlow: ";
			cin >> value;
			if (value <= 0)
			{
				cout << "Bledna liczba wezlow" << endl;
				break;
			}
			cout << "Wybierz gestosc z zakresu <0,1> po kropce " << endl;
			cout << "Wybierz gestosc: ";
			cin >> density;
			if (density < 0 || density > 1)
			{
				cout << "Bledna gestosc" << endl;
				break;
			}
			//cout << "Wybierz wage minimalna: ";
			//cin >> min_weight;
			//cout << "Wybierz wage maksymalna: ";
			//cin >> max_weight;
			min_weight = 1;
			max_weight = 50;
			cout << endl;
			graph.randomStructure(value, density, min_weight, max_weight, directed);
			break;
		case 3: // Bellman - Ford
			//cout << "Wybierz wezel startowy: ";
			//cin >> start;
			starts = 1;
			if (starts > graph.size_nodes - 1)
			{
				cout << "Nie istnieje taki wezel" << endl;
				break;
			}
			graph.start_node = starts;

				bellmanFordMatrix(graph);
				bellmanFordList(graph);

				bellmanFordMatrix(graph);
				bellmanFordList(graph);
	
			
			break;
		case 4: // wyjście
			break;
		default:
			cout << "Bledy wybor" << endl;
			break;
		}
	} while (action != 6);
}

void menu()
{
	int choice;
	do
	{
		cout << endl
			 << "Wybierz algorytm: " << endl;
		cout << "1. Minimalne drzewo rozpinajace (MST) " << endl;
		cout << "2. Znajdowanie najkrotszej sciezki w grafie " << endl;
		cout << "3. END " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			MST();
			break;
		case 2:
			menuPath();
			break;
		case 3:
			break;
		default:
			cout << "Bledy wybor" << endl;
			break;
		}
	} while (choice != 'e');
}

int main()
{
	menu();

	return 0;
}
