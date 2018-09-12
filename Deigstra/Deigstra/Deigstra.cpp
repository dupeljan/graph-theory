// Deigstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <set>
#include <vector>

using namespace std;

enum colors {
	not_visited,
	visited,
	blocked,
};

struct vertex //Вершина
{
	colors color;
	int  weight;  //Вес вершины
	vector < pair < int, int > > neigbors;  // Список соседей, вес ребра,  номер
};
vector < vertex > graph;
int main()
{
	int n;  //кол-во вершин
	int m;  //кол-во ребер
	cin >> n, m;

	//Рисуем ребра и присваиваем им вес
	graph.resize(n);
	for (int i = 0; i < m; i++) {
		int a, b, w;					//Соединияем вершины a,b ребром веса w
		graph[a - 1].neigbors.push_back(make_pair(w , b - 1)); 
		graph[b - 1].neigbors.push_back(make_pair(w, a - 1));
		
	}

	//Помечаем все вершины как непросмотренные
	for (int i = 0; i < n; i++)
		graph[i].color = not_visited;

	
	
}

int deikstra( int v ){
	set < pair < int, int > > search; // Вес, номер
	search.insert(make_pair(0, v));
	graph[v].color = visited; // Посещаем первую вершину
	graph[v].weight = 0;		
	
	while (!search.empty()) {
		
	}
}