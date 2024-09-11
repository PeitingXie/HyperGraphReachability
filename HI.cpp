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

	total_memory = 0;


	label = new vector<Pair> [n + 1];
	ete_label = new vector<Pair> [m + 1];
	tmpLabel = new vector<Pair> [m + 1];
	visited = new int [n + 1];
	visited_h = new int [m + 1];
	fill(visited_h, visited_h + m + 1, 0);
	
	global_visited_h = new int [m+1];
	fill(global_visited_h, global_visited_h + m + 1, 0);

	for (auto i = 1; i <= m; i++) {
		for (auto v: graph_edge[i].node) {
			// neighbour[i] += pow(E[v].size(), 2);
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


	nbr = new (std::nothrow) nbr_struct[m+1];
	if (nbr == nullptr) {
        std::cerr << "Memory allocation failed." << std::endl;
        
    }
	for (int i = 0; i <= m; ++i) {
        nbr[i].init = false;
        nbr[i].max = 0;
        nbr[i].left.clear();
        nbr[i].right.clear();
    }


	for (auto i = 1; i <= m; i++) {
		graph_edge[i].node.emplace_back(n + i);
	}

	
	

}


SL::~SL()
{
	
	if (idx) delete[] idx;
	if (order) delete[] order;
	if (nbr) delete[] nbr;
	// for baseline
}



void SL::add_triplet(vector<Pair> *currLabel, int u, int h, int overlap, bool update)
{
	
	if (!currLabel[u].size()) {
		currLabel[u].emplace_back(Pair(h, overlap));
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
	int max_h = 0;
	long long total = 0;
	int execute = 0;
	// if (u != 1) {
	// 	cout << "init memory = " << memoryBefore << "\n";
	// 	// while (true) {

	// 	// }
	// }


	

	
	while (!Q.empty()) {
		// count++;
		// if (count % 10 == 0) {
		// 	total += getMemoryUsage() - memoryBefore;
		// }
		// if (count > 10) break;
		Pair_in_queue pair = Q.top();
		Q.pop();
		int h = pair.hID;
		int overlap = pair.overlap;
		execute ++;
		// if (execute % 10 == 0) {
			// cout << "execute " << execute << " edges\n";
		// }


		if (overlap > nbr[h].max) {

			add_triplet(ete_label, h, u, overlap, true);
			// max_h = max(max_h, overlap);
			
			for (auto v : graph_edge[idx[h]].node) {
				if (v > n) {
					continue;

				} else {
					
					if (visited[v] == 0) {
						visited[v] = overlap;
						add_triplet(label, v, u, overlap, update);
						
					}
				}
				
			}
		} else {
			continue;
		}

		// cout << "h = " << h << "\n";
		// if (h == 0) cout << "got 0???\n";
		if (!nbr[h].init) {
			// cout << "h is " << h << "\n";
			// cout << "2\n";
			nbr[h].init = 1;
			nbr[h].max = overlap;
			map<int, int> m;
			// cout << "a\n";
			for (auto v : graph_edge[idx[h]].node) {
				// cout << "c\n";
				if (v > n) continue;
				for (auto nextH : E[v]) {
					if (order[nextH] <= u || order[nextH] == h) continue;
					// if (visited_h[order[nextH]] >= overlap) {
					// 	continue;
					// }
					if (m.find(order[nextH]) != m.end()) {
						m[order[nextH]]++;
					} else {
						m.insert(make_pair(order[nextH], 1));
					}
				}
				
				// cout << "d\n";
			}
			// cout << "b\n";
			for (auto it = m.begin(); it != m.end(); it++) {
				if (nbr[it->first].max < min(overlap, it->second)) {
				// 	visited_h[it->first] = it->second;
					Q.push(Pair_in_queue(it->first, min(overlap, it->second)));
					// if (it->first == 0) {
					// 	cout << "insert 0???\n";
					// }
				}
				if (it->second > nbr[h].max && h > 1) {
					if (it->first < h) {
						nbr[h].left.emplace_back(make_pair(it->first, it->second));
					} else {
						nbr[h].right.emplace_back(make_pair(it->first, it->second));
					}
				}
			}
			m.clear();
			// cout << "3\n";
		} else if (overlap <= nbr[h].max) {
			// cout << "4\n";
		} else {
			// cout << "5\n";
			/*
			auto it = nbr[h].left.lower_bound({0, overlap});
			nbr[h].left.erase(nbr[h].left.begin(), it);
			it = nbr[h].right.lower_bound({0, overlap});
			nbr[h].right.erase(nbr[h].right.begin(), it);
			*/
			nbr[h].max = overlap;
			if (u != h) {
				for (auto it1 = nbr[h].left.begin(); it1 != nbr[h].left.end(); ) {
					if (it1->first > u) {
						Q.push(Pair_in_queue(it1->first, min(overlap, it1->second)));
						// if (it1->first == 0) {
						// 	cout << "insert 0???\n";
						// }
					}
					if (it1->second <= nbr[h].max) {
						it1 = nbr[h].left.erase(it1);
					} else {
						++it1;
					}
				}
			}
			nbr[h].left.shrink_to_fit();

			for (auto it1 = nbr[h].right.begin(); it1 != nbr[h].right.end(); ) {

				Q.push(Pair_in_queue(it1->first, min(overlap, it1->second)));
				
				if (it1->second <= nbr[h].max) {
					it1 = nbr[h].right.erase(it1);
				} else {
					++it1;
				}
			}
			nbr[h].right.shrink_to_fit();
			// cout << "6\n";
		}



		// visited_h[h] = overlap;
		// if (u != h) {
		// 	global_visited_h[h] = max(global_visited_h[h], overlap);
		// } else {
		// 	if (overlap <= global_visited_h[u]) continue;
		// }

		// cout << "7\n";


		
		// cout << "8\n";
		
		
		
		// cout << "next BFS to :\n";
		// m.clear();
		

		// for (auto it = nbr[h].begin(); it != nbr[h].end(); ++it) {
		// 	if (min(overlap, it->second) <= global_visited_h[u]) {
		// 		continue;
		// 	} 
		// 	if (visited_h[it->first] >= min(overlap, it->second)) continue;
		// 	visited_h[it->first] = it->second;
			
		// 	Q.push(Pair_in_queue(it->first, min(overlap, it->second)));
		// }

	}
	// global_visited_h[u] = max_h;

	// for (auto i = 1; i <= n; i++) {   
	// 	if (visited[i] > 0) {
	// 		add_triplet(label, i, u, visited[i], update);
	// 	}
	// }
	// if (u != 1) {
	// 	total_memory += total;
	// }

	myfile.close();
}

void SL::construct(string scalePath) {
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


	double avg = 0;
	for (auto i = 1; i <= n; i++) {
		avg += E[i].size();
	}
	avg /= n;
	cout << "average neighbour = " << avg << "\n";


	vector<vector<int>> hot;
	vector<int> centrality;
	for (auto i = 1; i <= n; i++) {
		centrality.emplace_back(E[i].size());
	}
	sort(centrality.begin(), centrality.end());
	double level = 0.85;
	int count = 0;
	double val = level + count * 0.03;
	while (val < 1) {
		cout << "at level " << val << " " << centrality[n * val] << "\n";
		count += 1;
		val = level + count * 0.03;

		// cout << "val is " << val << "\n";
	}

	// while (true) {

	// }



	// int c;
	// cin >> c;
	// tmpE = new vector<int> [n+1];
	// for (int i = 1; i <= n; i++) {
	// 	for (auto v : E[i]) {
	// 		tmpE[i].emplace_back(v);
	// 	}
	// }
	
	// // delete[] label;
	// // delete[] tmpE;
	// // tmpE = nullptr;
	// cout << "construction finished\n";
	// while (true) {

	// }


	int singleNode = 0;



	// while (true) {

	// }
	
	cout << "total n = " << n << ", single node = " << singleNode << "\n";


	// while (true){}

	// nbr = new vector<pair<int, int>>[m+1];
	// for (int i = 1; i<=m; i++) {
	// 	// if (i % 100 == 0) {
	// 		cout << "nbr " << i << " finished\n";
	// 	// }`
	// 	map<int, int> m;
	// 	for (auto v : graph_edge[idx[i]].node) {
	// 		if (v > n) continue;
	// 		for (auto nextH : E[v]) {
	// 			if (order[nextH] <= i) continue;
	// 			if (m.find(order[nextH]) != m.end()) {
	// 				m[order[nextH]]++;
	// 			} else {
	// 				m.insert(make_pair(order[nextH], 1));
	// 			}
	// 		}
	// 	}
	// 	for (auto it = m.begin(); it != m.end(); ++it) {
	// 		nbr[i].emplace_back(make_pair(it->first, it->second));
	// 	}
	// 	m.clear();

	// }




	ofstream myConstructionfile;
	myConstructionfile.open ("construction.txt");
	cout << "start construction\n";
	// int c;
	// cin >> c;


	
	auto start_time = std::chrono::high_resolution_clock::now();
	for (auto i = 1; i <= m; i++) {
		// cout << "\n------------------------------construct for hID = " << i << " with overlap = " << graph_edge[idx[i]].node.size() - 1 << "-----------------------------\n";
		
	
		Q.push(Pair_in_queue(i, graph_edge[idx[i]].length));
		// cout << "construct for hID = " << i << " is finished\n";
		
		fill(visited, visited + n + 1, 0);
		fill(visited_h, visited_h + m + 1, 0);
		construct_for_a_vertex(graph_edge, i, false);

		nbr[i].left.clear();
		nbr[i].left.shrink_to_fit();
		nbr[i].right.clear();
		nbr[i].right.shrink_to_fit();


		if (i % 1000 == 1) {
		cout << "Edge  " << i << " has ben constructed " << "\n";
		}
		std::priority_queue<Pair_in_queue>().swap(Q);
		
	}
	
	auto end_time = std::chrono::high_resolution_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	myConstructionfile.close();
	cout << "construct time is " << elapsed_time.count() << "\n";
	

	std::ofstream file(scalePath, std::ios::app);
	if (!file.is_open()) {
        std::cerr << "无法打开文件: " << scalePath << std::endl;
        return;
    }
	file << "---------------------------------------------\n";
	file << "---------------------------------------------\n";
	// file << "construct time is " << elapsed_time.count() << "\n";
	// file << "VTE Container size is " << sizeof(vector<Pair>) * n /1024 << "kb\n"; 
	file << "\n";
	

	// std::cout << "Total memory usage increase: " << total_memory << " kB" << std::endl;
		//  while (true) {

		//  }
	
	
 



	delete[] tmpLabel;
	for (auto i = 1; i<=m; i++) {
		graph_edge[i].node.pop_back();
		graph_edge[i].node.shrink_to_fit();
	}
	cout << "construction finished\n";


	


	delete[] visited;
	delete[] visited_h;
	
	double vte = 0;
	double ete = 0;

	for (auto i = 1; i <=n; i++) {
		vte += label[i].size();
	}
	vte /= n;

	for (auto i = 1; i <= m; i++) {
		ete += ete_label[i].size();
	}
	ete /= m;
	cout << "average vte = " << vte << "\n";
	cout << "average ete = " << ete << "\n";
	// while (true){

	// }
	// return;

	long totalBytes = 0;
	for (int i = 1; i < n + 1; ++i) {
		totalBytes += sizeof(Pair) * label[i].size();
	}

	// std::ofstream file(scalePath, std::ios::app);
	// if (!file.is_open()) {
    //     std::cerr << "无法打开文件: " << scalePath << std::endl;
    //     return;
    // }
	

	// file << "VTE index size is " << totalBytes / 1024 << "kb\n";
	// file << "VTE Container size is " << sizeof(vector<Pair>) * n /1024 << "kb\n"; 
	// file << "\n";
	// file.close();

	file << "VTE index size is " << totalBytes / 1024 << "kb\n";
	file << "VTE Container size is " << sizeof(vector<Pair>) * n /1024 << "kb\n"; 
	
	long eteBytes = 0;
	for (int i = 1; i < m + 1; ++i) {
		eteBytes += sizeof(Pair) * ete_label[i].size();
	}
	file << "ETE index size is " << eteBytes / 1024 << "kb\n";
	file << "ETE Container size is " << sizeof(vector<Pair>) * m /1024 << "kb\n"; 
	// long memoryBefore = getMemoryUsage();

	long graphSize = 0;

	for (auto i = 1; i <= n; i++) {
		graphSize += E[i].size() * sizeof(int);
	}
	file << "Graph size is " << graphSize /1024 << "kb\n"; 
	// delete[] label;
	// cout << "VTE index size is " << label->size() * sizeof(Pair) / 1024 / 1024 << "\n";
	// while (true){}


	// int c;
	// cin >> c;
	// tmpE = new vector<int> [n+1];
	// for (int i = 1; i <= n; i++) {
	// 	for (auto v : E[i]) {
	// 		tmpE[i].emplace_back(v);
	// 	}
	// }
	
	// delete[] label;
	// delete[] tmpE;
	// tmpE = nullptr;
	cout << "construction finished\n";
	// while (true) {

	// }
	
	// int e;
	// cin >> e;

}




int SL::span_reach(int u, int v, int k, bool original_id) {
	// cout << "span reach checking " << u << " and " << v << " with o = " << overlap << "\n";
	int init_u = u;
	int init_v = v;
	if (original_id)
	{
		u = (*vertex_map)[u];
		v = (*vertex_map)[v];		
	}
	/*	
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
	
	
	int overlap = k;


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
	*/

	int overlap = 0;


		auto srcIt = label[u].begin();
		auto dstIt = label[v].begin();
		while (srcIt != label[u].end() && dstIt != label[v].end()) {
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
	return overlap;
}



int SL::ete_reach(int src, int dst, bool original_id) {
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];
	}
	int overlap = 0;
	if (src == dst) {
		overlap = 1;
	}

	vector<Pair> srcSet;
	vector<Pair> dstSet;


	for (auto h_u : E[src]) {
		auto srcIt1 = srcSet.begin();
		h_u = order[h_u];
		auto srcIt2 = ete_label[h_u].begin();
		// cout << "1\n";
		while (srcIt1 != srcSet.end() && srcIt2 != ete_label[h_u].end()) {
			// cout << "2\n";
			if (srcIt1->hID < srcIt2->hID) {
				srcIt1++;
			} else {
				// cout << "?\n";
				auto dist = std::distance(srcSet.begin(), srcIt1);
				if (srcIt1->hID == srcIt2->hID) {
					srcIt1->overlap = max(srcIt1->overlap, srcIt2->overlap);
				} else {
					srcSet.insert(srcIt1, Pair(srcIt2->hID, srcIt2->overlap));
					srcIt1 = srcSet.begin() + dist + 1;
				}
				srcIt2++;
			}
		}	
		

		if (srcIt2 != ete_label[h_u].end()) {
			while (srcIt2 != ete_label[h_u].end()) {
				auto dist = std::distance(srcSet.begin(), srcIt1);
				if (srcIt1 == srcSet.end()) {
					srcSet.insert(srcIt1, Pair(srcIt2->hID, srcIt2->overlap));
					srcIt1 = srcSet.begin() + dist + 1;
				} else {
					if (srcIt1->hID == srcIt2->hID) {
						srcIt1->overlap = max(srcIt1->overlap, srcIt2->overlap);
					} else {
						srcSet.insert(srcIt1 + 1, Pair(srcIt2->hID, srcIt2->overlap));
						srcIt1 = srcSet.begin() + dist + 1;
					}
				}
				srcIt2++;
				// cout << "4\n";
			}
		}
		// cout << "123\n";

		
	}
	// cout << "11111\n";

	for (auto h_v : E[dst]) {
		auto dstIt1 = dstSet.begin();
		h_v = order[h_v];
		auto dstIt2 = ete_label[h_v].begin();
		
		while (dstIt1 != dstSet.end() && dstIt2 != ete_label[h_v].end()) {
			
			if (dstIt1->hID <= dstIt2->hID) {
				dstIt1++;
			} else {
				auto dist = std::distance(dstSet.begin(), dstIt1);
				dstSet.insert(dstIt1, Pair(dstIt2->hID, dstIt2->overlap));
				dstIt1 = dstSet.begin() + dist + 1;
				dstIt2++;
			}
				
		}
		if (dstIt2 != ete_label[h_v].end()) {
			while (dstIt2 != ete_label[h_v].end()) {
				auto dist = std::distance(dstSet.begin(), dstIt1);
				if (dstIt1 == dstSet.end()) {
					dstSet.insert(dstIt1, Pair(dstIt2->hID, dstIt2->overlap));
				} else {
					dstSet.insert(dstIt1 + 1, Pair(dstIt2->hID, dstIt2->overlap));
				}
				dstIt1 = dstSet.begin() + dist + 1;
				dstIt2++;
			}
		}

	}
	// cout << "22222\n";

	// cout << "for in set\n";
	// for (auto p : srcSet) {
	// 	cout << "hID = " << p.hID << ", overlap = " << p.overlap << "\n";
	// }
	// cout << "------------------------------------------for out set\n";
	// for (auto p : dstSet) {
	// 	cout << "hID = " << p.hID << ", overlap = " << p.overlap << "\n";
	// }
	auto srcIt = srcSet.begin();
	auto dstIt = dstSet.begin();
	while (srcIt != srcSet.end() && dstIt != dstSet.end()) {
		if (srcIt->hID > dstIt->hID ) {
			dstIt++;
		} else if (srcIt->hID < dstIt->hID) {
			srcIt++;
		} else {
			if (srcIt->overlap > overlap && dstIt->overlap > overlap) {
				overlap = min(srcIt->overlap, dstIt->overlap);
			}
			if ((srcIt + 1) != srcSet.end() && srcIt->hID == (srcIt + 1)->hID) {
				srcIt++;
			} else {
				dstIt++;
			}
		}

	}
	// for (auto h_u : E[src]) {
	// 	h_u = order[h_u];
	// 	for (auto h_v : E[dst]) {
	// 		h_v = order[h_v];
	// 		auto srcIt = ete_label[h_u].begin();
	// 		auto dstIt = ete_label[h_v].begin();
	// 		while (srcIt != ete_label[h_u].end() && dstIt != ete_label[h_v].end()) {
	// 			if (srcIt->hID > dstIt->hID ) {
	// 				dstIt++;
	// 			} else if (srcIt->hID < dstIt->hID) {
	// 				srcIt++;
	// 			} else {
	// 				if (srcIt->overlap > overlap && dstIt->overlap > overlap) {
	// 					overlap = min(srcIt->overlap, dstIt->overlap);
	// 				}
	// 				srcIt++;
	// 				dstIt++;
	// 			}

	// 		}
	// 	}
	// }
	return overlap;
}



int SL::ete_edge_reach(int src, int dst) {
	int overlap = 0;


	auto srcIt = ete_label[src].begin();
	auto dstIt = ete_label[dst].begin();
	while (srcIt != ete_label[src].end() && dstIt != ete_label[dst].end()) {
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
	return overlap;
}



int SL::reach(int src, int dst, bool original_id) {
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];		
	}

	int overlap = 0;
	if (src == dst) {
		overlap = 1;
	}
	auto srcIt = label[src].begin();
	auto dstIt = label[dst].begin();
	while (srcIt != label[src].end() && dstIt != label[dst].end()) {
		if (srcIt->hID > dstIt->hID) {
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
	return overlap;
}





int SL::baseLine(int src, int dst, bool original_id) {
	
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];
	}


	vector<int> in_visit, out_visit;
	for (auto i = 0; i <= m; i++) {
		in_visit.emplace_back(0);
		out_visit.emplace_back(0);
	}
	priority_queue<Pair_in_queue> Q_in, Q_out;

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

	if (src == dst) {
		result = 1;
	}

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





long SL::getMemoryUsage() {
    std::string line;
    std::ifstream stat_stream("/proc/self/status", std::ios_base::in);

    while (std::getline(stat_stream, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            std::string rss = line.substr(7);
            rss = rss.substr(0, rss.find(" kB"));
            return std::stol(rss);
        }
    }
    return -1; // 如果没有找到相关信息
}