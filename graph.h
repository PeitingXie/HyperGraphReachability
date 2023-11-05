#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
#include <cfloat>
#include <numeric>
#include <climits>
#include <functional>
#include <chrono>
#include <time.h>
using namespace std;

struct HyperEdge
{
	vector<int> node;
    int length;
	HyperEdge *last, *next;
};


class Graph
{
public:
	// the number of vertices and the number of edges
	int max_v, max_e; // set them in "graph.cpp"
	int n, m;

	bool directed; // directed graph or undirected graph

	// graph and reversed graph
	HyperEdge **graph_head;
	HyperEdge *graph_edge;

	

    // E[i] 指的是node i 在哪些hyperedge 里
    vector<int> E[10000000];

	// in-degree and out-degree
	int *d_in, *d_out;

	int *vertex_id; // new ID --> original ID
	map<int, int> vertex_map; // original ID --> new ID


	Graph(char *graph_file, bool directed);
	~Graph();

	void insert_edge(vector<int> nodes);
	//void insert_edge(GraphEdge **head, GraphEdge *edge, int i, int j, int sign, int edge_id);
	void delete_edge(int u, int v, int edge_id);
	//void delete_edge(GraphEdge **head, GraphEdge *edge, int i, int edge_id);

	int get_vertex_id(int v); // return new ID
};
