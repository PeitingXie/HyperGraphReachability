#include "graph.h"




class SL
{
private:
	
	// the number of vertices and the number of edges
	int max_v, max_e; // set them in "graph.cpp"
	int n, m;

	bool directed; // directed graph or undirected graph

	// graph and reversed graph
	

	// in-degree and out-degree
	int *d_in, *d_out;

	int *idx; // order --> ID
	int *order; // ID --> order

	vector<int> *E;
	HyperEdge *graph_edge;
	map<int, int> *vertex_map;
	vector<pair<int, int>> *neighbour;

	// TILL-Index
	

	// int *visited;
	// int *inVisited;
	// int *outVisited;
	// int *biVisited;
	
	// int *cycleNum;
	// int *branchVisited;


	//map<pair<int, int>, vector<int>> inAncestor[10000001];
	vector<int> importantNode;

	// most important node in negative cycle
	int *special;

	

public:
	SL(Graph *graph);
	~SL();


	void construct();
	bool span_reach(int u, int v, int sign, bool original_id = false);

	void insert(int sign);
	void erase(int ts);

	bool isCovered(int sign1, int sign2);
	// use for calculating the sign of u->v from u->w to w->v 
	int signCal(int sign1, int sign2);
	// update sign when go to the next vertex
	int signUpdate(int sign1, int sign2);
	bool isEqual(const std::pair<int, int>& element, const int val);

	bool baseLine(int src, int dst, int overlap, bool original_id);
	
	void freeBaseline(int *visited);
	bool baseIsCovered(int sign1, int sign2);
	


	void estimate();
	//bool compareByFirstElement(const Pair_advanced& lhs, const Pair_advanced& rhs);
	//void SL::updateMustVisit(vector<mustVisit> *label_advanced_construct, int u, int v, int sign, vector<int> path, map<pair<int, int>, vector<int>> *visitedNode, vector<pair<int, set<levelRecord>>> *levelRecord);
};
