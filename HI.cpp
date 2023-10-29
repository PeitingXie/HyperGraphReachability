#include "HI.h"


SL::SL(Graph *graph)
{
	max_v = graph -> max_v;
	max_e = graph -> max_e;
	n = graph -> n;
	m = graph -> m;
	directed = graph -> directed;

	E = graph->E;
	graph_edge = graph->graph_edge;
	neighbour = graph->neighbour;

	d_in = graph -> d_in;
	d_out = graph -> d_out;

	vertex_map = &(graph -> vertex_map);

	//theta = 2000000000;

	
}


SL::~SL()
{
	
	if (idx) delete[] idx;
	if (order) delete[] order;
	// for baseline
}



bool SL::baseLine(int src, int dst, int overlap, bool original_id) {
	
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];
	}

	// for (int i = 1; i <= m; i++) {
    //     cout << "edge " << i << " is overlaped with :\n";
    //     for (auto e : neighbour[i]) {
    //         cout << e.first << ", " << e.second << "\n";
    //     } 
    // }


	vector<int> in_visit, out_visit;
	for (auto i = 0; i <= m; i++) {
		in_visit.push_back(0);
		out_visit.push_back(0);
	}
	queue<pair<int, int>> Q_in, Q_out;
	// cout << "try to query for " << src << " and " << dst << " with t = " << overlap << "\n";
	for (auto h : E[dst]) {
		// cout << "insert " << h << " to Q_in\n";
		if (graph_edge[h].length < overlap) continue;
		Q_in.push(make_pair(h, graph_edge[h].length));
	}
	for (auto h : E[src]) {
		// cout << "insert " << h << " to Q_out\n";
		if (graph_edge[h].length < overlap) continue;
		Q_out.push(make_pair(h, graph_edge[h].length));
	}
	
	int token = 0;
	while (!Q_in.empty() || !Q_out.empty()) {
		if (!token) {
			// cout << "now switch to in neighbour\n";
			int size = Q_in.size();
			// cout << "size = " << size << "\n";
			for (auto i = 0; i < size; i++) {
				auto pair = Q_in.front();
				auto h = pair.first;
				auto o = pair.second;
				// cout << "get edge h = " << h << " with overlap = " << o << "\n";
				Q_in.pop();
				
				
				if (out_visit[h]) return true;
				if (in_visit[h]) continue;
				in_visit[h] = 1;
				
				for (auto nextPair : neighbour[h]) {
					if (nextPair.second < overlap) continue;
					// cout << "push " << nextPair.first << " " << nextPair.second << "\n";
					Q_in.push(nextPair);
				}
				
				
				
			}
			token = 1;
		} else {
			int size = Q_out.size();

			// cout << "now switch to out neighbour\n";
			// cout << "size = " << size << "\n";
			for (auto i = 0; i < size; i++) {
				auto pair = Q_out.front();
				auto h = pair.first;
				auto o = pair.second;
				// cout << "get edge h = " << h << " with overlap = " << o << "\n";
				Q_out.pop();
				
				if (in_visit[h]) return true;
				if (out_visit[h]) continue;
				out_visit[h] = 1;
				for (auto nextPair : neighbour[h]) {
					if (nextPair.second < overlap) continue;
					// cout << "push " << nextPair.first << " " << nextPair.second << "\n";
					Q_out.push(nextPair);
				}
				
			}
			token = 0;
		}

	}
	return false;
}	