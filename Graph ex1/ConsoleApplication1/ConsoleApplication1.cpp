// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

//
int dfs(int v);
int dfs(int v, int color);

vector<int> dws(int v);

void graph_input(int vertex, int edge);
void count_components(int n);
bool is_connect(int n);
void vect_out(vector<int> v);
void zero(int n);
//
struct vertex{
	//smth info;
	//smth weihgt;
	int color;
	int parent;
	vector<int> neigbors;
};

vector<vertex> graph;



int main(){
	int n, m;// кол-во вершин и ребер
	
	std::cout << "n=";
	std::cin >> n;
	std::cout << "m=";
	std::cin >> m;

	graph_input(n, m);
	dfs(0);

	cout << "connect " << is_connect(n) << '\n';

	zero(n);

	count_components(n);
	
	zero(n);
	
	//Обход в ширину
	vect_out(dws(0));

	system("pause");

	
}

//Обход графа в глубину DFS
int dfs(int v) {
	if (graph[v].color)								//Если вершина посещена
		return 1;

	graph[v].color = 1;									//Посещаем вершину
	std::cout << v + 1 << '\n';
	for (int i = 0; i < graph[v].neigbors.size(); i++)  //Обходим соседей
		if (!graph[graph[v].neigbors[i]].color) {		//Если сосед не посещен
			dfs(graph[v].neigbors[i]);
		}

	return 0;

}

int dfs(int v, int color) {
	if (!graph[v].color) { // Если вершина не посещена
		graph[v].color = color;
		//std::cout << v + 1 << '\n';
		for (int i = 0; i < graph[v].neigbors.size(); i++) {
			if (!graph[graph[v].neigbors[i]].color) {
				dfs(graph[v].neigbors[i], color);
			}
		}
		return 0;
	}
}

// Алгоритм обхода графа в ширину dws
vector<int> dws(int v) {
	if (graph[v].color)
		return { 0 };

	vector<int> result = { v + 1 };
	graph[v].color = 1;			//Просмотрим верхушку

	for (int pointer = 0; pointer < result.size(); pointer++) {			//Пока pointer не дошел до конца
		int actual_vert = result[pointer] - 1;							//Номер текущей вершины
		for (int i = 0; i < graph[actual_vert].neigbors.size(); i++)  //Перебор всех соседей текущей вершины
			if (!graph[graph[actual_vert].neigbors[i]].color) {         //Если выбранный сосед не просмотрен
				graph[graph[actual_vert].neigbors[i]].color = 1;        //Просматриваем его
				result.push_back(graph[actual_vert].neigbors[i] + 1);	//Записываем номер в результат
			}
	}
	return result;
}

void graph_input(int vertex, int edge) {

	graph.resize(vertex);
	//Ввод Вершин
	zero(vertex);

	//Ввод ребер
	for (int i = 0; i < edge; ++i) {
		std::cout << i + 1 << ")Connect vertex " << '\n';
		int a, b;
		std::cin >> a >> b;
		graph[a - 1].neigbors.push_back(b - 1);
		graph[b - 1].neigbors.push_back(a - 1);

	}

	cout << '\n';
}

void count_components(int n) {										//Находим кол-во компонент связности
	int count = 0;
	for (int i = 0; i < n; i++)
		if (!graph[i].color) {
			++count;
			dfs(i, count);
		}
	cout << "Count sviaznosti components " << count << '\n';
}

bool is_connect(int n) {					//проверка на связность 
	bool full = true;
	for (int i = 0; i < n && full; i++)
		full = graph[i].color;
	return full;
}

void zero(int n) {                                                    //Обнулить вершины графа
	for (int i = 0; i < n; i++) {
		//std::cout << "vertex #" << i + 1;
		graph[i].color = 0;
	}
}

void vect_out(vector<int> v) {
	for (int n : v)
		cout << n << '\n';
}

