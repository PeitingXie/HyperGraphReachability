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

	label = new vector<Pair> [n + m + 1];
	idx = new int [m + 1];
	iota(idx + 1, idx + m + 1, 1);

	sort(idx + 1, idx + m + 1, [&](int i, int j){return (long long)(neighbour[i].size() + 1) > (long long)(neighbour[j].size() + 1);});

	order = new int [m + 1];
	iota(order + 1, order + m + 1, 1);
	for (int i = 1; i <= m; i++)
		order[idx[i]] = i;


	for (auto i = 1; i <= m; i++) {
		graph_edge[i].node.push_back(n + i);
	}

}


SL::~SL()
{
	
	if (idx) delete[] idx;
	if (order) delete[] order;
	// for baseline
}



void SL::add_triplet(vector<Pair> *label, int u, int h, int overlap, bool update)
{
	if (!label[u].size())
		label[u].push_back(Pair(h, overlap));
	else
	{
		Pair temp(h, overlap);
		vector<Pair>::iterator it = lower_bound(label[u].begin(), label[u].end(), temp);
		if (it->hID != h) {
			// cout << "find " << it->hID << "\n";
			label[u].insert(it, temp);
		} else {
			// cout << "123\n";
			it->overlap = max(it->overlap, overlap);
		}
	}
}


void SL::construct_for_a_vertex(HyperEdge * head, vector<Pair> *label, int u, bool update) {
	int count = 0;
	
	ofstream myfile;
  	myfile.open ("out.txt");
	
	while (!Q.empty()) {
		count++;
		// if (count > 10) break;
		Pair_in_queue pair = Q.top();
		Q.pop();
		int h = pair.hID;
		int overlap = pair.overlap;
		// cout << "current hID is " << idx[h] << ", with o = " << overlap << "\n";
		if (span_reach(idx[u] + n, idx[h] + n, overlap)) {
			// cout << "this has been covered\n";
			continue;
		}
		for (auto v : graph_edge[idx[h]].node) {
			// count++;
			// myfile << "add Label(" << v << ") = (" << h << ", " << overlap << ")\n";
			add_triplet(label, v, u, overlap, update);
			
		}
		for (auto nextPair : neighbour[idx[h]]) {
			if (order[nextPair.first] <= u || order[nextPair.first] == h) continue;
			// count++;
			// if (count >= 100000) {
			// 	myfile.close();
			// 	return;
			
			// }
			// myfile << "push (" << nextPair.first << ", " << min(overlap, nextPair.second) << ")\n";
			Q.push(Pair_in_queue(order[nextPair.first], min(overlap, nextPair.second)));
		}
	}
	 myfile.close();
}

void SL::construct() {
	// cout << "Importance rank for edge is:\n";
	// for (auto i = 1; i <= m; i++) {
	// 	cout << order[i] << " ";
	// }
	// cout << "\n";

	// cout << "neighbour relationship:\n";
	// for (auto i = 1; i <= m; i++) {
	// 	cout << "for edge " << i << "\n";
	// 	for (auto p : neighbour[i]) {
	// 		cout << "reach " << p.first << " with o = " << p.second << "\n"; 
	// 	}
	// }



	ofstream myConstructionfile;
	myConstructionfile.open ("construction.txt");
	cout << "start construction\n";
	for (auto i = 1; i <= m; i++) {
		// cout << "\n------------------------------construct for hID = " << i << " with overlap = " << graph_edge[idx[i]].node.size() - 1 << "-----------------------------\n";
		Q.push(Pair_in_queue(i, graph_edge[idx[i]].node.size() - 1));
		// cout << "construct for hID = " << i << " is finished\n";
		
		auto start_time = std::chrono::high_resolution_clock::now();
		construct_for_a_vertex(graph_edge, label, i, false);
		auto end_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

		myConstructionfile << "Construction time for edge " << i << " is " <<elapsed_time.count() << "\n";
		
	}
	myConstructionfile.close();
	


	for (auto i = n + 1; i <= n + m; i++) {
		label[i].clear();
	}
	std::vector<Pair>* newLabel = new std::vector<Pair>[n + 1];
	for (int j = 1; j <= n; j++) {
		newLabel[j] = label[j];
	}
	delete[] label;
	label = newLabel;



	// cout << "after construction:\n";
	// cout << "Index is Label :\n";
	// for (auto i = 1; i <= n; i++) {
	// 	cout << "Vertex ID = " << i << ":\n";
	// 	for (auto pair : label[i]) {
	// 		cout << "hID = " << idx[pair.hID] << ", " << " with overlap = " << pair.overlap << "\n";  
	// 	}
	// }

}




bool SL::span_reach(int u, int v, int overlap, bool original_id) {
	// cout << "span reach checking " << u << " and " << v << " with o = " << overlap << "\n";
	if (original_id)
	{
		if (u <= n) u = (*vertex_map)[u];
		if (v <= n) v = (*vertex_map)[v];
	}
	
	vector<Pair> *label_u, *label_v;
	label_u =  label;
	label_v = label;
	
	
	set<int> s;
	for (auto h : E[v]) {
		s.insert(order[h]);
	}

	for (auto pair : label_u[u]) {
		if (pair.overlap < overlap) continue;
		if (s.find(pair.hID) != s.end()) return true; 
		//if (binary_search(s.begin(), s.end(), pair.hID)) return true;
	}
	s.clear();
	for (auto h : E[u]) {
		s.insert(order[h]);
	}


	for (auto pair : label_v[v]) {
		if (pair.overlap < overlap) continue;
		if (s.find(pair.hID) != s.end()) return true; 
		//if (binary_search(s.begin(), s.end(), pair.hID)) return true;
	}

	auto srcIt = label_u[u].begin();
	auto dstIt = label_v[v].begin();
	while (srcIt != label_u[u].end() && dstIt != label_v[v].end()) {
		if (srcIt->hID > dstIt->hID) {
			dstIt++;
		} else if (srcIt->hID < dstIt->hID) {
			srcIt++;
		} else {
			if (min(srcIt->overlap, dstIt->overlap) >= overlap) return true;
			srcIt++;
			dstIt++;
		}
	}
	return false;
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
					if (in_visit[nextPair.first]) continue;
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
					if (out_visit[nextPair.first]) continue;
					// cout << "push " << nextPair.first << " " << nextPair.second << "\n";
					Q_out.push(nextPair);
				}
				
			}
			token = 0;
		}

	}
	return false;
}	