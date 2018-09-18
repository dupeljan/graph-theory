// Deigstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <set>
#include <vector>
#include <fstream>

#define INPUT_FILE_PATCH  "input.txt"
using namespace std;

///
void deikstra(int v);
void output_weight();
void min_vert_len(vector < vector < int > > ); // Алгоритм Флойда - Уоршелла
void drop_vector(vector < vector <int> > a);
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
vector < vector < int > > w_matr; //Матрица кратчайших путей

int main()
{
	fstream file;

	file.open(INPUT_FILE_PATCH);
	int n;  //кол-во вершин
	int m;  //кол-во ребер
	file >> n >> m;
	

	//Рисуем ребра и присваиваем им вес
	graph.resize(n);
	
	
	//Иницмалтзируем матрицу
	w_matr.resize(n);
	for (int i = 0; i < n; i++) {
		w_matr[i].resize(n);
		w_matr[i][i] = 0;
	}

	// Находим максимум веса
	int max_w = 0;

	for (int i = 0; i < m; i++) {
		
		int a, b, w;				//Соединияем вершины a,b ребром веса w
		file >> a >> b >> w;
		//
		a--;
		b--;
		//
		graph[a].neigbors.push_back(make_pair(w , b)); 
		graph[b].neigbors.push_back(make_pair(w, a ));
		w_matr[a][b] = w_matr[b][a] = w;

		max_w += abs(w);
	}

	//Помечаем все вершины как непросмотренные
	for (int i = 0; i < n; i++)
		graph[i].color = not_visited;

	//Заполняем матрицу бесконечностями
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!w_matr[i][j] && (i != j))
				w_matr[i][j] = max_w + 1;

	//Кидаем матрицу в алгоритм
	
	min_vert_len(w_matr);
	//deikstra(0);

	// output_weight();
	
	cout << "success!" << '\n';

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

		//Получаем указатель на текущую вершину
		vertex *cur_vert = &graph[it->second];

		//Удаляем элемент из множества
		search.erase(it);

		
		//Блокируем текущую вершину
		cur_vert->color = blocked;
		
		//Для каждого соседа
		for (int i = 0; i < cur_vert->neigbors.size(); i++) {
			
			//Получаем указатель на соседа
			vertex *cur_neig = & graph[cur_vert->neigbors[i].second];
			
			if (cur_neig->color != blocked) {
				
				
				//Вычисляем длинну
				if (cur_neig->color == not_visited)								//Если не посещена
					cur_neig->weight = cur_vert->weight + cur_vert->neigbors[i].first; //Вес равен сумме веса текущей вершины и соед. ребра
				else                                                           //Вес сохраняется, если новый больше
					cur_neig->weight = min(cur_neig->weight, cur_vert->weight + cur_vert->neigbors[i].first);
				
				//Посещаем вершину
				cur_neig->color = visited;

				//Вставляем в множество
				search.insert(make_pair(cur_neig->weight, cur_vert->neigbors[i].second ));// Записываем вес и номер вершины
			}
		}
	}
	//return 0;
}

// Алгоритм заполняет матрицу, (w[i][j]) i,j=1..n 
// где (w[i][j]) - минимальное расстояние между вершиной i и j
void min_vert_len(vector < vector <int> > w) {
	for (int i = 0; i < w.size(); i++)
		for (int j = 0; j < w.size(); j++)
			for (int k = 0; k < w.size(); k++)
				w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
	drop_vector(w);
}

void output_weight() {

	fstream out;
	out.open("output.txt", fstream::out);
	out << "vertex weight \n";
	for (int i = 0; i < graph.size(); i++)
		out << i + 1<< ' ' << graph[i].weight << '\n';
	out.close();
}

int digit_count(int a){
	int res = 0;
	do {
		res++;
		a /= 10;
	} while (a);
	
	return res;
}
void drop_vector(vector < vector <int> > a) {
	fstream out;
	out.open("output.txt",fstream::out);
	int max_dig = 3;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			out << a[i][j];
			for (int k = 0; k < max_dig - digit_count(a[i][j]); k++)
				out << ' ';
		}
		out << '\n';
	}
	
	out.close();
}