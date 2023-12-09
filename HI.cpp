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
	visited = new int [n + 1];
	visited_h = new int [m + 1];
	fill(visited_h, visited_h + m + 1, 0);
	
	
	
	for (auto i = 1; i <= m; i++) {
		for (auto v: graph_edge[i].node) {
			neighbour[i] += pow(E[v].size(), 2);
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
	
	
	// if (v == 64450 && u == order[178758] && overlap == 4) {
	// 	cout << "overlap 4 construct success\n";
	// 	while (true) {

	// 	}
	// }

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

		// myfile << "current hID is " << h << ", with o = " << overlap << "\n";
		// myfile << "span_reach check for hyperedge " << u << " and " <<  h  << "\n";
		// if (span_reach(idx[u] + n, idx[h] + n, overlap)) {
		// 	continue;
		// }

		visited_h[h] = u;
		int max_cover = span_reach(h + n, u + n);
		if (max_cover >= overlap) {
			for (auto v : graph_edge[idx[h]].node) {
				if (v > n) continue;
				if ((visited[v] > 0 && max_cover > visited[v]) || visited[v] == 0) {
					visited[v] = -max_cover;
				}	
			}
			continue;
		}


		// bool needBFS = false;

		for (auto v : graph_edge[idx[h]].node) {
			// if (span_reach(idx[u] + n, v, overlap)) {
			// 	continue;
			// }
			// count++;
			// myfile << "add Label(" << v << ") = (" << h << ", " << overlap << ")\n";
			if (v > n) {
				add_triplet(tmpLabel, order[v - n], u, overlap, update);

			} else {
				if (visited[v] == 0) visited[v] = overlap;
				// add_triplet(label, v, u, overlap, update);
			}
			
		}

		map<int, int> m;

		for (auto v : graph_edge[idx[h]].node) {
			if (v > n) continue;
			for (auto nextH : E[v]) {
				if (order[nextH] <= u || order[nextH] == h) continue;
				if (visited_h[order[nextH]] == u) continue;
				if (m.find(order[nextH]) != m.end()) {
					m[order[nextH]]++;
				} else {
					m.insert(make_pair(order[nextH], 1));
				}
			}
		}

		for (auto it = m.begin(); it != m.end(); it++) {
			
			// visited_h[it->first] = u;
			Q.push(Pair_in_queue(it->first, min(overlap, it->second)));
		}
		// cout << "next BFS to :\n";
		m.clear();
	}


	for (auto i = 1; i <= n; i++) {   
		if (visited[i] > 0) {
			add_triplet(label, i, u, visited[i], update);
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


	cout << "ready to construct\n";

	int singleNode = 0;




	
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
		fill(visited, visited + n + 1, 0);
		
		construct_for_a_vertex(graph_edge, i, false);
		auto end_time = std::chrono::high_resolution_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		if (i % 1000 == 1) {
		cout << "Edge  " << i << " has ben constructed " << "\n";
		}
		std::priority_queue<Pair_in_queue>().swap(Q);
		
	}
	
	
	myConstructionfile.close();
	



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
	for (auto i = 1; i<=m; i++) {
		graph_edge[i].node.pop_back();
		graph_edge[i].node.shrink_to_fit();
	}
	cout << "construction finished\n";
	// int c;
	// cin >> c;
	// while (true) {

	// }

	// cout << "n = " << n << "\n";
	// for (auto i = 1; i <= n; i++) {
	// 	cout << i << "->" << (*vertex_map)[i] << "\n"; 
	// }

	// cout << "order:\n";
	// for (auto i = 1; i <= m; i++) {
	// 	cout << idx[i] << " ";
	// }
	// cout << "\n";


	// cout << "current Index is :\n";
	// for (auto i = 1; i <= n; i++) {
	// 	cout << "for L(" << i << "):\n";
	// 	for (auto pair : label[i]) {
	// 		cout << "(" << idx[pair.hID] << ", " << pair.overlap << ")\n";
	// 	}
	// }



	delete[] visited;
	delete[] visited_h;
	
	
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




int SL::span_reach(int u, int v, bool original_id) {
	// cout << "span reach checking " << u << " and " << v << " with o = " << overlap << "\n";
	int init_u = u;
	int init_v = v;
	if (original_id)
	{
		u = (*vertex_map)[u];
		v = (*vertex_map)[v];		
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
	
	
	int overlap = 0;


	auto srcIt = label_u[tmp_u].begin();
	auto dstIt = label_v[tmp_v].begin();
	while (srcIt != label_u[tmp_u].end() && dstIt != label_v[tmp_v].end()) {
		if (srcIt->hID > dstIt->hID ) {
			dstIt++;
		} else if (srcIt->hID < dstIt->hID) {
			srcIt++;
		} else {
			if (srcIt->overlap > overlap && dstIt->overlap > overlap) {
				overlap = min(srcIt->overlap, dstIt->overlap);
			}
			srcIt++;
			dstIt++;
		}

	}
	
	// srcIt = label_u[u].begin();
	// dstIt = label_v[v].begin();
	
	// ofstream myfile;
  	// myfile.open ("log.txt");

	// myfile << "for Label[u]:\n";
	// if (init_u == 64450 && init_v == 99974 && overlap == 4) {
	
	// 	while (srcIt != label_u[u].end()) {
	// 		myfile << srcIt->hID << ", " << srcIt->overlap << "\n";
	// 		srcIt++;
	// 	}
	// }

	// myfile << "for Label[v]:\n";

	// if (init_u == 64450 && init_v == 99974 && overlap == 4) {
	
	// 	while (dstIt != label_v[v].end()) {
	// 		myfile << dstIt->hID << ", " << dstIt->overlap << "\n";
	// 		dstIt++;
	// 	}
	// 	myfile << "v is " << v << ", tmp_v is " << tmp_v << "\n";
	// 	return true;
	// }
	return overlap;
}



int SL::baseLine(int src, int dst, bool original_id) {
	
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
	priority_queue<Pair_in_queue> Q_in, Q_out;
	// cout << "try to query for " << src << " and " << dst << " with t = " << overlap << "\n";
	// cout << "for dst:\n";
	for (auto h : E[dst]) {
		// cout << "insert " << h << " with o = " << graph_edge[h].length << "\n";
		Q_in.push(Pair_in_queue(h, graph_edge[h].length));
	}

	// cout << "for src:\n";
	for (auto h : E[src]) {
		// cout << "insert " << h << " with o = " << graph_edge[h].length << "\n";
		Q_out.push(Pair_in_queue(h, graph_edge[h].length));
	}
	int result = 0;
	int token = 0;
	while (!Q_in.empty() || !Q_out.empty()) {
		if (!token) {
			int size = Q_in.size();
			for (auto i = 0; i < size; i++) {
				auto pair = Q_in.top();
				auto h = pair.hID;
				auto o = pair.overlap;
				// cout << "from in: get h = " << h << ", o = " << o << "\n";
				Q_in.pop();

				if (out_visit[h]) {
					result = max(result, min(o, out_visit[h]));
				}
				if (in_visit[h] >= o) continue;
				in_visit[h] = o;
				
				// for (auto nextPair : neighbour[h]) {
				// 	if (nextPair.second < overlap) continue;
				// 	// cout << "push " << nextPair.first << " " << nextPair.second << "\n";
				// 	if (in_visit[nextPair.first]) continue;
				// 	Q_in.push(nextPair);
				// }

				map<int, int> m;
	
				for (auto v : graph_edge[h].node) {
					if (v > n) continue;
					for (auto nextH : E[v]) {
						// if (h <= i) continue;
						// if (in_visit[nextH]) continue;
						if (m.find(nextH) != m.end()) {
							m[nextH]++;
						} else {
							m.insert(make_pair(nextH, 1));
						}
					}
				}

				for (auto it = m.begin(); it != m.end(); it++) {
					

					if (it->second <= result) continue;
					if (in_visit[it->first] >= min(it->second, o)) continue;
					Q_in.push(Pair_in_queue(it->first, min(it->second, o)));
				}
				m.clear();
			}
			token = 1;
		} else {
			int size = Q_out.size();

			// cout << "now switch to out neighbour\n";
			// cout << "size = " << size << "\n";
			for (auto i = 0; i < size; i++) {
				auto pair = Q_out.top();
				auto h = pair.hID;
				auto o = pair.overlap;
				// cout << "from out: get h = " << h << ", o = " << o << "\n";
				// cout << "get edge h = " << h << " with overlap = " << o << "\n";
				// if (h == 2578) cout << "2 detect 2578 with" << o << "\n";
				Q_out.pop();
				
				if (in_visit[h]) {
					result = max(result, min(o, in_visit[h]));
				}
				
				if (out_visit[h] >= o) continue;
				out_visit[h] = o;
				// for (auto nextPair : neighbour[h]) {
				// 	if (nextPair.second < overlap) continue;
				// 	if (out_visit[nextPair.first]) continue;
				// 	// cout << "push " << nextPair.first << " " << nextPair.second << "\n";
				// 	Q_out.push(nextPair);
				// }


				map<int, int> m;
	
				for (auto v : graph_edge[h].node) {
					if (v > n) continue;
					for (auto nextH : E[v]) {
						// if (h <= i) continue;
						// if (out_visit[nextH]) continue;
						if (m.find(nextH) != m.end()) {
							m[nextH]++;
						} else {
							m.insert(make_pair(nextH, 1));
						}
					}
				}

				for (auto it = m.begin(); it != m.end(); it++) {

				
					if (it->second <= result) continue;
					if (out_visit[it->first] >= min(it->second, o)) continue;
					Q_out.push(Pair_in_queue(it->first, min(it->second, o)));
				}
				m.clear();	
			}
			token = 0;
		}

	}
	return result;
}	