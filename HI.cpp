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


	vertex_map = &(graph -> vertex_map);

	//theta = 2000000000;

	label = new vector<Pair> [n + 1];
	tmpLabel = new vector<Pair> [m + 1];


	for (auto i = 1; i <= m; i++) {
		for (auto v: graph_edge[i].node) {
			neighbour[i] += E[v].size();
		}
	}


	idx = new int [m + 1];
	iota(idx + 1, idx + m + 1, 1);

	sort(idx + 1, idx + m + 1, [&](int i, int j){return (long long)(neighbour[i] + 1) > (long long)(neighbour[j] + 1);});

	order = new int [m + 1];
	iota(order + 1, order + m + 1, 1);
	for (int i = 1; i <= m; i++)
		order[idx[i]] = i;





	// for (int i = 1; i <= m; i++) {
	// 	map<int, int> m;
	// 	for (auto v : graph_edge[i].node) {
	// 		for (auto h : E[v]) {
	// 			if (h <= i) continue;
	// 			if (m.find(h) != m.end()) {
	// 				m[h]++;
	// 			} else {
	// 				m.insert(make_pair(h, 1));
	// 			}
	// 		}
	// 	}

	// 	for (auto pair : m) {
	// 		neighbour[pair.first].push_back(make_pair(i, pair.second));
	// 		neighbour[i].push_back(make_pair(pair.first, pair.second));
	// 	}


	// 	if (i % 100 == 0) {
	// 		cout << "preComputing for hyperedge " << i << "is finished\n";
	// 	}
		
	// }

	// cout << "precompute finished\n";



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



void SL::add_triplet(vector<Pair> *currLabel, int u, int h, int overlap, bool update)
{
	
	


	if (!currLabel[u].size()) {
		currLabel[u].push_back(Pair(h, overlap));
		if (u == 71 && h == 32) {
			cout << "insert empty 71 32\n";
		}
	} else {
		

		Pair temp(h, overlap);

		auto it = std::lower_bound(currLabel[u].begin(), currLabel[u].end(), temp,
        [](const Pair a, const Pair& b) {
            return a.hID < b.hID;
        });


		// vector<Pair>::iterator it = lower_bound(label[u].begin(), label[u].end(), temp);
		if (it->hID != h || it == currLabel[u].end()) {
			// if (u == 71 && h == 32) {
			// 	cout << "insert 71 32\n";
			// }
			currLabel[u].insert(it, temp);
		} else {
			// if (u == 71 && h == 32) {
			// 	// cout << "insert 71 32\n";
			// 	cout << "find " << it->hID << "\n";
			// 	for (auto p : currLabel[u]) {
			// 		cout << "h = " << p.hID << ", with overlap = " << p.overlap << "\n";
			// 	}
			// 	if (it == currLabel[u].end()) {
			// 		"equal = end\n";
			// 	}
			// }
			// cout << "123\n";
			it->overlap = max(it->overlap, overlap);
		}
	}
}


void SL::construct_for_a_vertex(HyperEdge * head,  int u, bool update) {
	int count = 0;
	int num = 0;
	ofstream myfile;
  	myfile.open ("out.txt");
	
	while (!Q.empty()) {
		count++;
		// if (count > 10) break;
		Pair_in_queue pair = Q.top();
		Q.pop();
		int h = pair.hID;
		int overlap = pair.overlap;

		myfile << "current hID is " << h << ", with o = " << overlap << "\n";
		myfile << "span_reach check for hyperedge " << u << " and " <<  h  << "\n";
		// if (span_reach(idx[u] + n, idx[h] + n, overlap)) {
		// 	continue;
		// }

		if (span_reach(h + n, u + n, overlap)) {
			continue;
		}
		myfile << "and not covered\n";

		int needBFS = false;
		for (auto v : graph_edge[idx[h]].node) {
			// if (span_reach(idx[u] + n, v, overlap)) {
			// 	continue;
			// }
			// count++;
			// myfile << "add Label(" << v << ") = (" << h << ", " << overlap << ")\n";
			if (v > n) {
				add_triplet(tmpLabel, order[v - n], u, overlap, update);
				// if (order[v - n] == 71 && u == 32) {
				// 	// cout << "pair.hID = " << pair.hID << " overlap = " << pair.overlap <<"\n";
				// 	cout << "size = " << tmpLabel[u].size() <<"\n";
				
				// }
			} else {
				// needBFS = true;
				add_triplet(label, v, u, overlap, update);
			}
			
		}

		// if (!needBFS) continue;
		map<int, int> m;

		for (auto v : graph_edge[idx[h]].node) {
			for (auto h : E[v]) {
				if (order[h] <= u) continue;
				if (m.find(order[h]) != m.end()) {
					m[order[h]]++;
				} else {
					m.insert(make_pair(order[h], 1));
				}
			}
		}

		for (auto it = m.begin(); it != m.end(); it++) {
			
			Q.push(Pair_in_queue(it->first, min(overlap, it->second)));
		}
		// cout << "next BFS to :\n";
		m.clear();
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


	cout << "ready to construct\n";
	
	
	int singleNode = 0;

	// for (auto i = 0; i <= n; i++) {
	// 	mapTo.push_back(i);
	// }


	// for (auto i = 1; i <= m; i++) {
	// 	// cout << "i = " << i << "\n";
	// 	int head = -1;
	// 	for (auto v : graph_edge[i].node) {
	// 		if (E[v].size() == 1) {
	// 			head = v;
	// 			break;
	// 		}
	// 	}
	// 	if (head == -1) continue;
	// 	// if (head == -1) head = graph_edge[i].node[0];
	// 	for (auto it = graph_edge[i].node.begin(); it != graph_edge[i].node.end();) {
	// 		if (E[*it].size() == 1 && *it != head) {
	// 			// cout << "1\n";
				
	// 			(*vertex_map)[*it] = (*vertex_map)[head];
	// 			it = graph_edge[i].node.erase(it);
	// 			singleNode++;
	// 		} else {
	// 			++it;
	// 		}
			
	// 	}
	// 	graph_edge[i].node.shrink_to_fit();

	// }
	cout << "total n = " << n << ", single node = " << singleNode << "\n";

	

	ofstream myConstructionfile;
	myConstructionfile.open ("construction.txt");
	cout << "start construction\n";
	// int c;
	// cin >> c;
	for (auto i = 1; i <= m; i++) {
		// cout << "\n------------------------------construct for hID = " << i << " with overlap = " << graph_edge[idx[i]].node.size() - 1 << "-----------------------------\n";
		Q.push(Pair_in_queue(i, graph_edge[idx[i]].length));
		// cout << "construct for hID = " << i << " is finished\n";
		
		auto start_time = std::chrono::high_resolution_clock::now();
		construct_for_a_vertex(graph_edge, i, false);
		auto end_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		// if (i % 1000 == 1) {
		cout << "Edge  " << i << " has ben constructed " << "\n";
		// }
		
	}
	
	
	myConstructionfile.close();
	
	cout << "construction finished\n";


	// cout << "order is :\n";
	// for (auto i = 1; i <= 5; i++) {
	// 	cout << i << ": " << order[i] << "\n";
	// }

	// cout << "label is :\n";
	// for (auto i = 1; i <= 8; i++) {
	// 	cout << "Label[" << i << "] :\n";
	// 	for (auto pair : label[i]) {
	// 		cout << "(" << pair.hID << ", " << pair.overlap << ")\n";
	// 	}
	// }

	delete[] tmpLabel;
	// while (true) {

	// }


	



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
	int init_u = u;
	int init_v = v;
	if (original_id)
	{
		if (u <= n) u = (*vertex_map)[u];
		if (v <= n) v = (*vertex_map)[v];
		
		
	}
	
	vector<Pair> *label_u, *label_v;

	int tmp_u = u;
	int tmp_v = v;

	if (u > n) {
		label_u = tmpLabel;
		tmp_u -= n;
	} else {
		label_u =  label;
	}

	if (v > n) {
		label_v = tmpLabel;
		tmp_v -= n;
	} else {
		label_v = label;
	}
	
	// cout << "index of 38225 is : " << idx[38225] << "\n";
	// cout << "order of 2578 is : " << order[2578] << "\n";
	
	
	set<int> s;
	if (v > n) {
		s.insert(v - n);
		// if (tmp_u == 71 && tmp_v == 32) {
		// 	cout << "insert " << v-n <<"\n";
		// }
	} else {
		for (auto h : E[v]) {
			s.insert(order[h]);
		}
	}

	// if (tmp_u == 71 && tmp_v == 32) {
	// 	cout << "label_u[tmp_u].size() = " << label_u[tmp_u].size() <<"\n";
	// 	for (int i = 0; i < label_u[tmp_u].size(); i++) {
	// 		// if (label_u[tmp_u][i].hID == 32) {
	// 		cout << "ID = " << label_u[tmp_u][i].hID << ", overlap = " << label_u[tmp_u][i].overlap << ", required " << overlap << "\n";
	// 		// }
	// 		// cout << "label_u[tmp_u]["  << i << "]" << label_u[tmp_u][i].hID <<"\n";
	// 	}
	// 	// for (auto pair : label_u[tmp_u]) {
	// 	// 	cout << "pair.hID = " << pair.hID << " overlap = " << pair.overlap <<"\n";
	// 	// }
	// }
	// if (tmp_u == 71 && tmp_v == 32) {
	// 	cout << "next\n";
	// }
	for (auto pair : label_u[tmp_u]) {
		// if (tmp_u == 71 && tmp_v == 32) {
		// 	cout << "pair.hID = " << pair.hID << " overlap = " << pair.overlap <<"\n";
		// }


		if (pair.overlap < overlap) continue;
		// if (s.find(pair.hID) != s.end()) return true; 
		
		if (binary_search(s.begin(), s.end(), pair.hID)) {
			// cout << "return true with h = " << pair.hID << ", overlap = " << pair.overlap << "\n";
			return true;
		}
	}

	s.clear();

	if (u > n) {
		s.insert(u - n);
	} else {
		for (auto h : E[u]) {
			s.insert(order[h]);
		}
	}


	for (auto pair : label_v[tmp_v]) {
		if (pair.overlap < overlap) continue;
		// if (s.find(pair.hID) != s.end()) return true; 
		if (binary_search(s.begin(), s.end(), pair.hID)) {
			// cout << "return true with h = " << pair.hID << ", overlap = " << pair.overlap << "\n";
			return true;
		}
	}
	
	auto srcIt = label_u[tmp_u].begin();
	auto dstIt = label_v[tmp_v].begin();
	while (srcIt != label_u[tmp_u].end() && dstIt != label_v[tmp_v].end()) {
		if (srcIt->hID > dstIt->hID ) {
			dstIt++;
		} else if (srcIt->hID < dstIt->hID) {
			srcIt++;
		} else {
			if (srcIt->overlap < overlap || dstIt->overlap < overlap) {
				srcIt++;
				dstIt++;
				continue;
			}
			// cout << "return true with h = " << srcIt->hID << ", overlap = " << srcIt->overlap << "\n";
			return true;
		}

		// if (init_u == 246 && init_v == 717 && srcIt->hID < 700 && dstIt->hID < 700) {
		// 	cout << "current comparison : u = " << srcIt->hID << ", v = " << dstIt->hID << "\n";
		// }
	}
	
	// srcIt = label_u[u].begin();
	// dstIt = label_v[v].begin();
	
	// if (init_u == 246) {
	// 	cout << "in label[246]:\n";
	// 	while (srcIt != label_u[u].end() && srcIt->hID < 1000) {
	// 		cout << srcIt->hID << ", " << srcIt->overlap << "\n";
	// 		if (srcIt->hID == 620 && srcIt->overlap >= 125) cout << "111111111111111111111111\n";
	// 		srcIt++;
	// 	}
	// }
	// if (init_v == 717) {
	// 	cout << "in label[717]:\n";
	// 	while (dstIt != label_v[v].end() && dstIt->hID < 1000) {
	// 		cout << dstIt->hID << ", " << dstIt->overlap << "\n";
	// 		if (dstIt->hID == 620 && dstIt->overlap >= 125) cout << "222222222222222222222222\n";
	// 		dstIt++;
	// 	}
	// }
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
				// if (h == 2578) cout << "1 detect 2578 with" << o << "\n";
				
				if (out_visit[h]) return true;
				if (in_visit[h]) continue;
				in_visit[h] = 1;
				
				// for (auto nextPair : neighbour[h]) {
				// 	if (nextPair.second < overlap) continue;
				// 	// cout << "push " << nextPair.first << " " << nextPair.second << "\n";
				// 	if (in_visit[nextPair.first]) continue;
				// 	Q_in.push(nextPair);
				// }

				map<int, int> m;
	
				for (auto v : graph_edge[h].node) {
					if (v > n) continue;
					for (auto h : E[v]) {
						// if (h <= i) continue;
						if (in_visit[h]) continue;
						if (m.find(h) != m.end()) {
							m[h]++;
						} else {
							m.insert(make_pair(h, 1));
						}
					}
				}

				for (auto it = m.begin(); it != m.end(); it++) {
					if (it->second < overlap) continue;
					if (in_visit[it->first]) continue;
					Q_in.push(make_pair(it->first, it->second));
				}
				m.clear();
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
				// if (h == 2578) cout << "2 detect 2578 with" << o << "\n";
				Q_out.pop();
				
				if (in_visit[h]) return true;
				if (out_visit[h]) continue;
				out_visit[h] = 1;
				// for (auto nextPair : neighbour[h]) {
				// 	if (nextPair.second < overlap) continue;
				// 	if (out_visit[nextPair.first]) continue;
				// 	// cout << "push " << nextPair.first << " " << nextPair.second << "\n";
				// 	Q_out.push(nextPair);
				// }


				map<int, int> m;
	
				for (auto v : graph_edge[h].node) {
					if (v > n) continue;
					for (auto h : E[v]) {
						// if (h <= i) continue;
						if (out_visit[h]) continue;
						if (m.find(h) != m.end()) {
							m[h]++;
						} else {
							m.insert(make_pair(h, 1));
						}
					}
				}

				for (auto it = m.begin(); it != m.end(); it++) {
					if (it->second < overlap) continue;
					if (out_visit[it->first]) continue;
					Q_out.push(make_pair(it->first, it->second));
				}
				m.clear();


				
			}
			token = 0;
		}

	}
	return false;
}	