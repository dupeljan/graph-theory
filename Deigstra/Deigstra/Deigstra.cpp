// Deigstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <set>
#include <vector>

using namespace std;

///
void deikstra(int v);
///

enum colors {
	not_visited,
	visited,
	blocked,
};

struct vertex //Вершина
{
	colors color;
	int  weight;  //Вес вершины
	vector < pair < int, int > > neigbors;  // Список соседей: вес ребра,  номер
};
vector < vertex > graph;
int main()
{
	int n;  //кол-во вершин
	int m;  //кол-во ребер
	cout << "Vertex count " ;
	cin >> n;
	cout << "Edge count ";
	cin >> m;

	//Рисуем ребра и присваиваем им вес
	graph.resize(n);
	for (int i = 0; i < m; i++) {
		std::cout << i + 1 << ")Connect vertex " << '\n';
		int a, b, w;				//Соединияем вершины a,b ребром веса w
		cin >> a >> b >> w;
		graph[a - 1].neigbors.push_back(make_pair(w , b - 1)); 
		graph[b - 1].neigbors.push_back(make_pair(w, a - 1));
		
	}

	//Помечаем все вершины как непросмотренные
	for (int i = 0; i < n; i++)
		graph[i].color = not_visited;

	deikstra(0);

	system("pause");
}
int min(int a, int b) {
	return (a <= b) ? a : b;
}

void deikstra( int v ){
	set < pair < int, int > > search; // Вес, номер
	search.insert(make_pair(0, v));
	//graph[v].color = visited; // Посещаем первую вершину
	graph[v].weight = 0;		
	set < pair < int, int > >::iterator it; // Итератор 
	while (!search.empty()) {
		
		//Извлекаем первый элемент множества
		it = search.begin();
		search.erase(it);
		
		//Получаем указатель на текущую вершину
		vertex *cur_vert = &graph[it->second];
		
		//Блокируем вершину
		cur_vert->color = blocked;
		
		//Для каждого соседа
		for (int i = 0; cur_vert->neigbors.size(); i++) {
			
			//Получаем указатель на соседа
			vertex *cur_neig = & graph[cur_vert->neigbors[i].second];
			
			if (cur_neig->color != blocked) {
			
				//Вычисляем длинну
				if (cur_neig->color == not_visited)								//Если не посещена
					cur_neig->weight = cur_vert->weight + cur_vert->neigbors[i].first; //Вес равен сумме веса текущей вершины и соед. ребра
				else                                                           //Вес сохраняется, если новый больше
					cur_neig->weight = min(cur_neig->weight, cur_vert->weight + cur_vert->neigbors[i].first);
				
				//Вставляем в множество
				search.insert(make_pair(cur_neig->weight, cur_vert->neigbors[i].second ));// Записываем вес и номер вершины
			}
		}
	}
	//return 0;
}