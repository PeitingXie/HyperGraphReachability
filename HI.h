#include "graph.h"


struct Pair // triplet in TILL-Index
{
	int hID;
	int overlap;
	Pair(int _hID, int _overlap): hID(_hID), overlap(_overlap) {};
	bool operator< (const Pair &x) const
	{
		return hID < x.hID;
	}
};



struct Pair_in_queue {
	int hID;
	int overlap;
	Pair_in_queue(int _hID, int _overlap): hID(_hID), overlap(_overlap) {};
	bool operator< (const Pair_in_queue &x) const
	{
		return overlap < x.overlap;
	}
};


struct CompareSecond {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        // 主要比较第二个元素
        if (a.second != b.second) return a.second < b.second;
        // 如果第二个元素相同，则比较第一个元素，以保证排序的唯一性
        return a.first < b.first;
    }
};


struct nbr_struct {
	bool init;
	int max;
	vector<pair<int, int>> left; // 重要性更大(order 更小)
	vector<pair<int, int>> right; // 重要性更小 
};






class SL
{
private:
	
	// the number of vertices and the number of edges
	int max_v, max_e; // set them in "graph.cpp"
	int n, m;

	bool directed; // directed graph or undirected graph

	// graph and reversed graph
	
	vector<Pair> *label, *tmpLabel, *ete_label;
	




	int *idx; // order --> ID
	int *order; // ID --> order
	priority_queue<Pair_in_queue> Q;
	vector<int> *E;
	HyperEdge *graph_edge;
	map<int, int> *vertex_map;
	long long neighbour[10000000];
	int *visited;
	int *visited_h;

	int *global_visited_h;


	int *temp, *rank, *penalty, *idx2;

	vector<int> *tmpE;

	long long total_memory;


	struct nbr_struct* nbr; 
	
	// vector<pair<int, int>> *nbr;
	
	vector<pair<int, int>> *allNbr;



	

public:
	SL(Graph *graph);
	~SL();


	void construct(string scalePath);
	void construct_for_a_vertex(HyperEdge * head, int u, bool update);
	void add_triplet(vector<Pair> *currLabel, int u, int h, int overlap, bool update);
	
	
	int span_reach(int u, int v, int k,  bool original_id = false);
	int reach(int src, int dst, bool original_id);
	int ete_reach(int src, int dst, bool original_id = false);
	int ete_edge_reach(int src, int dst);
	void insert(int sign);
	void erase(int ts);

	bool isCovered(int sign1, int sign2);
	bool veCover(int h, int u, int overlap);
	std::set<int> intersectAllSets(const std::vector<std::set<int>>& sets);
	// use for calculating the sign of u->v from u->w to w->v 
	int signCal(int sign1, int sign2);
	// update sign when go to the next vertex
	int signUpdate(int sign1, int sign2);
	bool isEqual(const std::pair<int, int>& element, const int val);

	int baseLine(int src, int dst,  bool original_id);
	
	void freeBaseline(int *visited);
	bool baseIsCovered(int sign1, int sign2);
	


	void estimate();
	//bool compareByFirstElement(const Pair_advanced& lhs, const Pair_advanced& rhs);
	//void SL::updateMustVisit(vector<mustVisit> *label_advanced_construct, int u, int v, int sign, vector<int> path, map<pair<int, int>, vector<int>> *visitedNode, vector<pair<int, set<levelRecord>>> *levelRecord);


	long getMemoryUsage();

};