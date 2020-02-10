// Algorytm Dijkstry.cpp : This fcount contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int dijkstra(int** mapa, int s, int d, int count);

int main()
{
	int test, count, paths, start=0, dest=0, w, k;
	vector<pair<int, string>> cities;
	string name, name2;
	ofstream outFile;
	outFile.open("outFile.txt");

	cout << "Iloœæ testów: ";
	cin >> test;
	for (int t = 0; t < test; t++)
	{
		cout << "Iloœæ miast: ";
		cin >> count;
		int** mapa = new int* [count];

		for (int i = 0; i < count; i++)
			mapa[i] = new int[count];

		for (int i = 0; i < count; i++)
			for (int j = 0; j < count; j++)
				mapa[i][j] = -1;

	
		for (int i = 0; i < count; i++)
		{
			cout << "Nazwa miasta: ";
			cin >> name;
			cities.push_back(make_pair(i, name));
			cout << "Iloœæ œcie¿ek z miasta: ";
			cin >> k;
			for (int j = 0; j < k; j++)
			{
				cin >> dest >> w;
				dest--;
				mapa[i][dest] = w;
			}
		}

		cout << "Iloœæ badanych œcie¿ek: ";
		cin >> paths;

		for (int i = 0; i < paths; i++)
		{
			cin >> name >> name2;

			for (pair<int, string> city : cities)
			{
				if (name == city.second)
					start = city.first;
				if (name2 == city.second)
					dest = city.first;
			}
			w = dijkstra(mapa,start, dest, count);
			if (w == -1)
				cout << "nie ma\n";
			else
				outFile << w << "\n";
		}

		cities.clear();
		for (int i = 0; i < count; i++)
			delete[] mapa[i];
		delete[] mapa;
	}
	outFile.close();
	return 0;
}

int dijkstra(int** mapa, int s, int d, int count) {
	int v, path = -1, actual;
	int* E = new int[count];
	bool* close = new bool[count], test = true;

	for (int i = 0; i < count; i++)
	{
		E[i] = INT_MAX;
		close[i] = false;
	}

	E[s] = 0;
	while (close[d] == false && test)
	{
		test = false;
		actual = INT_MAX;
		for (int i = 0; i < count; i++)
			if (close[i] == false && E[i] < actual)
			{
				v = i;
				actual = E[i];
				test = true;
			}

		close[v] = true;

		for (int u = 0; u < count; u++)
			if (mapa[v][u] != -1 && close[u] == false)
				if (E[v] + mapa[v][u] < E[u])
					E[u] = E[v] + mapa[v][u];


		//przy grafie skierowanym
		//for (int u = v + 1; u < count; u++)
		//	if (mapa[u][v] != -1 && close[u] == false)
		//		if (E[v] + mapa[u][v] < E[u])
		//			E[u] = E[v] + mapa[u][v];

	}

	if (E[d] != INT_MAX)
		path = E[d];

	delete[] E;
	delete[] close;

	return path;
}