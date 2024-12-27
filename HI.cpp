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
	tmpLabel = new vector<Pair> [n + 1];
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

	allNbr = new vector<pair<int, int>> [m + 1];


	D = new map<int, int>[n + 1];
	QPairs = new vector<QPair>[m + 1];
	C = new int [m + 1];
	// inverted = new set<int> [m + 1];
	W = new set<int> [n + 1];
	total_count = 0;
	// for (auto i = 0; i < m; i++) {
	// 	map<int, int> m;
	// 	for (auto j : graph_edge[i].node) {
	// 		for (auto k : E[j]) {

	// 			if (m.find(k) != m.end()) {
	// 				m[k]++;
	// 			} else {
	// 				m.insert(make_pair(k, 1));
	// 			}
	// 		}
	// 	}
	// 	for (auto it = m.begin(); it != m.end(); ++it) {
	// 		allNbr[i].push_back(*it);
	// 	}
	// }
	
	// temp = new int [n + 1];
	

	// rank = new int [m + 1];
	// penalty = new int [m + 1];
	
	// // penalty
	// for (auto shuffle = 0; shuffle < 9; shuffle++) {
	// 	iota(temp + 1, temp + n + 1, m);
	// 	for (auto i = 1; i < n; i++) {
	// 		for (auto j : E[i]) {
	// 			temp[i] = m + 1 - min(temp[i], order[j]);
	// 		}
	// 	}


	// 	long long pena = 0;
	// 	iota(rank + 1, rank + m + 1, 0);
	// 	iota(penalty + 1, penalty + m + 1, 1);
	// 	for (auto i = 1; i <= m; i++) {
	// 		long long num = 0;
	// 		for (auto j : graph_edge[idx[i]].node) {
	// 			// rank[i] += temp[j] - i;
	// 			num += temp[j];
	// 			pena += temp[j] - i;
	// 		}
	// 		rank[idx[i]] = num;
	// 		// cout << rank[i] << "\n";
	// 	}
	// 	// while (true) {};
	// 	sort(penalty + 1, penalty + m + 1, [&](int i, int j){return (long long)(rank[i] + 1) > (long long)(rank[j] + 1);});
	
	// 	// for (auto i = 1; i < 100; i++) {
	// 	// 	cout << "(" <<penalty[i] << " , " << order[i] << ") ";
	// 	// }
	// 	cout << "shuffle = " << shuffle << ", average penalty is : " << pena / m << "\n";
	// 	sort(idx + 1, idx + m + 1, [&](int i, int j){return (long long)(order[i] + penalty[i]) < (long long)(order[j] + penalty[j]);});
	// 	int swi = 0;
	// 	for (int i = 1; i <= m; i++) {
	// 		if (order[idx[i]] != i) swi++;
	// 		order[idx[i]] = i;
	// 	}
	// 	cout << "switch " << swi << "\n";
	// }
	// while (true) {}




	// temp = new int [n + 1];
	// iota(temp + 1, temp + n + 1, 1);
	// for (auto i = 1; i <= m; i++) {
	// 	for (auto v : graph_edge[idx[i]].node) {
	// 		temp[v] = m;
	// 	}
	// }

	// rank = new int [m + 1];
	// iota(rank + 1, rank + m + 1, 1);
	// for (auto i = 1; i <= m; i++) {
	// 	for (auto v : graph_edge[idx[i]].node) {
	// 		rank[i] += (m - temp[v] + i);
	// 	}
	// 	rank[i] /= graph_edge[i].length;
	// 	rank[i] *= neighbour[idx[i]];
	// }

	

	// iota(idx + 1, idx + m + 1, 1);
	// sort(idx + 1, idx + m + 1, [&](int i, int j){return (long long)(rank[i] + 1) > (long long)(rank[j] + 1);});

	// iota(order + 1, order + m + 1, 1);
	// for (int i = 1; i <= m; i++)
	// 	order[idx[i]] = i;
	
	// delete[] temp;
	// delete[] rank;



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
	if (nbr) delete[] nbr;
	if (visited_h) delete[] visited_h;
	if (global_visited_h) delete[] global_visited_h;
	if (visited) delete[] visited;
	// for baseline
	if (allNbr) delete[] allNbr;
	if (D) delete[] D;
	if (QPairs) delete[] QPairs;
	if (tmpLabel) delete[] tmpLabel;
	if (C) delete[] C;
	if (W) delete[] W;
	// for baseline
}



void SL::add_triplet(vector<Pair> *currLabel, int u, int h, int overlap, bool update)
{
	
	
	// if (v == 64450 && u == order[178758] && overlap == 4) {
	// 	cout << "overlap 4 construct success\n";
	// 	while (true) {

	// 	}
	// }
	// auto it = std::upper_bound(QPairs[h].begin(), QPairs[h].end(), QPair(u, overlap));

	auto it = std::upper_bound(
		QPairs[h].begin(),
		QPairs[h].end(),
		QPair(u, overlap),
		[](const QPair& a, const QPair& b) {
			return a.overlap > b.overlap; // 自定义从大到小的比较规则
		}
	);
	QPairs[h].insert(it, QPair(u, overlap));
	// QPairs[h].push_back(QPair(u, overlap));
	
	if (!currLabel[u].size()) {
		currLabel[u].push_back(Pair(h, overlap));
	} else {
		

		Pair temp(h, overlap);

		auto it = std::lower_bound(currLabel[u].begin(), currLabel[u].end(), temp,
        [](const Pair a, const Pair& b) {
            return a.hID < b.hID;
        });


		// auto it = std::upper_bound(currLabel[u].begin(), currLabel[u].end(), temp,
        // [](const Pair a, const Pair& b) {
        //     return a.overlap > b.overlap;
        // });

		// vector<Pair>::iterator it = lower_bound(label[u].begin(), label[u].end(), temp);
		// currLabel[u].insert(it, temp);

		if (it->hID != h || it == currLabel[u].end()) {
			// if (u == 71 && h == 32) {
			// 	cout << "insert 71 32\n";
			// }
			currLabel[u].insert(it, temp);
		} 
		

		// cout << "1\n";
		// D[h][u] = max(D[h][u], overlap);
		// cout << "2\n";
		
		// else {

		// 	it->overlap = max(it->overlap, overlap);
		// }
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
	// map <int, int> cover;



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
		int c_val = pair.cover;
		if (visited_h[h] == -1) continue;
		if (visited_h[h] > 0) {
			visited_h[h] = -1;
		}
		execute ++;
		// if (execute % 10 == 0) {
		// 	cout << "execute " << execute << " edges\n";
		// }



		// myfile << "current hID is " << h << ", with o = " << overlap << "\n";
		// if (u >= 13) {
		// 	cout << count <<"\n";
		// }
		// myfile << "span_reach check for hyperedge " << u << " and " <<  h  << "\n";
		// if (span_reach(idx[u] + n, idx[h] + n, overlap)) {
		// 	continue;
		// }

		
		
		// visited_h[h] = overlap;
		if (u != h) {
			global_visited_h[h] = max(global_visited_h[h], overlap);
		} else {
			if (overlap <= global_visited_h[u]) continue;
		}
		
		// if (c_val == 0) {
		// 	bool check = true;
		
		// 	for (auto v1 : graph_edge[idx[h]].node) {
		// 		if (!check) break;
		// 		for (auto v2 : graph_edge[idx[u]].node) {
		// 			if (v1 > n || v2 > n) continue;
		// 			if (!check) break;
		// 			if (span_reach(v1, v2, 0) < overlap) check = false;
		// 		}
		// 	}

		// 	if (u != 1) c_val = cover_check(u, h, overlap);
		// 	// cover[h] = cover_val;
		// 	if (check &&  c_val >= overlap) continue;
		// } else {
		// 	if (c_val >= overlap) continue;
		// }


		
		
		
		
		// int max_cover = ete_edge_reach(h, u);
		// int max_cover = span_reach(h + n, u + n, 0);
		// if (max_cover >= overlap) {
		// 	for (auto v : graph_edge[idx[h]].node) {
		// 		if (v > n) continue;
		// 		if ((visited[v] > 0 && max_cover > visited[v]) || visited[v] == 0) {
		// 			visited[v] = -max_cover;
		// 		}	
		// 	}
		// 	if (u != h) {
		// 		total_memory++;
		// 	}
		// 	continue;
		// }

		// add_triplet(ete_label, h, u, overlap, true);
		// max_h = max(max_h, overlap);
		
	
		for (auto v : graph_edge[idx[h]].node) {
			if (v > n) {
				continue;

			} else {
				
				if (visited[v] == 0) {
					visited[v] = overlap;
					add_triplet(tmpLabel, v, u, overlap, update);
					total_count += 1;
				}
			}
			
		}
	
		map<int, int> m;

		for (auto v : graph_edge[idx[h]].node) {
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
		}
			
		for (auto it = m.begin(); it != m.end(); it++) {
			
			
			if (min(overlap, it->second) <= global_visited_h[u]) {
				// total_memory++;
				continue;
			} 
			if (visited_h[it->first] >= min(overlap, it->second) || visited_h[it->first] == -1) continue;
			visited_h[it->first] = min(overlap, it->second);
			
			Q.push(Pair_in_queue(it->first, min(overlap, it->second), c_val));
		}
		// cout << "next BFS to :\n";
		m.clear();
		

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
	std::ofstream file(scalePath, std::ios::app);
	if (!file.is_open()) {
        std::cerr << "无法打开文件: " << scalePath << std::endl;
        return;
    }

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
		centrality.push_back(E[i].size());
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
	// 		tmpE[i].push_back(v);
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
	// 		nbr[i].push_back(make_pair(it->first, it->second));
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
		
	
		Q.push(Pair_in_queue(i, graph_edge[idx[i]].length, 0));
		// cout << "construct for hID = " << i << " is finished\n";
		
		fill(visited, visited + n + 1, 0);
		fill(visited_h, visited_h + m + 1, 0);
		construct_for_a_vertex(graph_edge, i, false);



		if (i % 1000 == 1) {
		cout << "Edge  " << i << " has ben constructed " << "\n";
		}
		std::priority_queue<Pair_in_queue>().swap(Q);
		
	}
	
	auto end_time = std::chrono::high_resolution_clock::now();
	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	myConstructionfile.close();
	
	// while (true) {}
	
	// file << "construct time is " << elapsed_time.count() << "\n";
	// // file << "VTE Container size is " << sizeof(vector<Pair>) * n /1024 << "kb\n"; 
	// file << "\n";
	

	// std::cout << "Total memory usage increase: " << total_memory << " kB" << std::endl;
		//  while (true) {

		//  }
	
	
	// std::ofstream file("DBLP_QPairs.txt", std::ios::app);
	
	// for (auto i = 1; i <= m; ++i) {
	// 	file << QPairs[i].size() << '\n';
	// }
	// while (true) {}




	
	for (auto i = 1; i<=m; i++) {
		graph_edge[i].node.pop_back();
		graph_edge[i].node.shrink_to_fit();
	}
	cout << "construction finished\n";

	cout << "construct time is " << elapsed_time.count() << "\n";
	file << "construct time is " << elapsed_time.count() << "\n";
	// label = tmpLabel;
	// return;

	// delete[] visited;
	// delete[] visited_h;
	
	cout << "here\n";
	double vte = 0;
	double ete = 0;
	
	for (auto i = 1; i <=n; i++) {
		vte += tmpLabel[i].size();
	}
	cout << "tmp total vte = " << vte << "\n";
	file << "tmp total vte = " << vte << "\n";
	vte /= n;

	for (auto i = 1; i <= m; i++) {
		ete += ete_label[i].size();
	}
	// ete /= m;
	cout << "tmp average vte = " << vte << "\n";


	long nonMinimaltotalBytes = 0;
	for (int i = 1; i < n + 1; ++i) {
		nonMinimaltotalBytes += sizeof(Pair) * tmpLabel[i].size();
	}

	// return;
	// for (auto i = 1; i <= n; i++) {
	// 	cout << "for vertex " << i - 1 << ":\n";
	// 	for (auto p : tmpLabel[(*vertex_map)[i - 1]]) {
	// 		cout << "eID = " << p.hID << ", overlap = " << p.overlap << "\n";
	// 	}
	// }
	
	// return;

	// for (auto it = QPairs[1].begin(); it != QPairs[1].end(); ++it) {
	// 	cout << "vID = " << it->vID << ", overlap = " << it->overlap << "\n";
	// }
	// while (true){}


	int sumNum = 0;
	int vis[n + 1];
	fill(vis, vis + n + 1, 0);
	start_time = std::chrono::high_resolution_clock::now();
	for (auto i = 1; i <= m; ++i) {
		// cout << "1\n";

		// vector<pair<int, int>> inverted[m + 1];
		if (QPairs[i].size() == 0) continue;
		if (QPairs[i].size() == 1) {
			bool re = false;
			for (auto it = tmpLabel[QPairs[i][0].vID].begin(); it != tmpLabel[QPairs[i][0].vID].end(); ++it) {
				if (it->hID != i && it->overlap >= QPairs[i][0].overlap) {
					re = true;
					break;
				}
				if (re) {
					auto it2 = std::lower_bound(tmpLabel[QPairs[i][0].vID].begin(), tmpLabel[QPairs[i][0].vID].end(), Pair(i, 1),
					[](const Pair a, const Pair& b) {
						return a.hID < b.hID;
					});
					if (it2->hID == i) {
						tmpLabel[QPairs[i][0].vID].erase(it2);
					}
				} else {
					auto temp = Pair(i, QPairs[i][0].overlap);
					auto it_1 = std::lower_bound(label[QPairs[i][0].vID].begin(), label[QPairs[i][0].vID].end(), temp,
					[](const Pair a, const Pair& b) {
						return a.hID < b.hID;
					});
					label[QPairs[i][0].vID].insert(it_1, temp);
				}
			}
			continue;
		}
		unordered_set<int> nonDup;
		// auto* inverted = new vector<pair<int, int>>[m + 1];
		std::map<int, std::vector<std::pair<int, int>>> inverted;
		// vector<vector<pair<int, int>>> inverted(m + 1);
		// for (auto& vec : inverted) {
		// 	vec.reserve(100); // 为每个内层 vector 预留容量为 10
		// }
		
		// cout << "2\n";
		for (auto it = QPairs[i].begin(); it != QPairs[i].end(); ++it) {	 // 每个it 为 vID, overlap
			for (auto p = tmpLabel[it->vID].begin(); p != tmpLabel[it->vID].end(); ++p) {
				if (p->overlap >= it->overlap  && p->hID != i) {
					inverted[p->hID].push_back(make_pair(it->vID, it->overlap));
				}
			}
		}

		// cout << "3\n";
		for (auto it = QPairs[i].begin(); it != QPairs[i].end();) {
			// cout << "4\n";
			unordered_set<int> candidates; // S
			bool redundant = false;
			for (auto p = tmpLabel[it->vID].begin(); p != tmpLabel[it->vID].end(); ++p) {
				if (redundant) break;
				if (p->hID == i) continue;
				// cout << "4\n";
				for (auto p_1 = inverted[p->hID].begin(); p_1 != inverted[p->hID].end(); ++p_1) {
					if (redundant) break;

					if (p->overlap >= p_1->second && vis[p_1->first] != i) {
						candidates.insert(p_1->first);
					}

					if (candidates.size() == QPairs[i].size()) redundant = true;
				}
			}
			// cout << "5\n";
			
			auto found = nonDup.find(it->vID);

			if (!redundant || found != nonDup.end()) {
				// cout << "6\n";
				auto temp = Pair(i, it->overlap);
				auto it_1 = std::lower_bound(label[it->vID].begin(), label[it->vID].end(), temp,
				[](const Pair a, const Pair& b) {
				    return a.hID < b.hID;
				});
	
				label[it->vID].insert(it_1, temp);
				for (auto it2 = QPairs[i].begin(); it2 != QPairs[i].end(); ++it2) {
					if (candidates.find(it2->vID) == candidates.end()) {
						nonDup.insert(it2->vID);
					}
				}
				// cout << "7\n";
			} else {
				// cout << "8\n";

				auto it2 = std::lower_bound(tmpLabel[it->vID].begin(), tmpLabel[it->vID].end(), Pair(i, 1),
				[](const Pair a, const Pair& b) {
				    return a.hID < b.hID;
				});
				if (it2->hID == i) {
					tmpLabel[it->vID].erase(it2);
				}

				// for (auto it2 = tmpLabel[it->vID].begin(); it2 != tmpLabel[it->vID].end();++it2) {
				// 	if (it2->hID == i) {
				// 		tmpLabel[it->vID].erase(it2);
				// 		break;
				// 	}
				// }
				// cout << "9\n";
			}
			// cout << "10\n";
			nonDup.erase(it->vID);
			// cout << "5\n";
			vis[it->vID] = i;
			it = QPairs[i].erase(it);
			if (nonDup.size() == QPairs[i].size()) {
				// cout << "11\n";
				for(; it != QPairs[i].end(); ++it) {
					auto temp = Pair(i, it->overlap);
					auto it_1 = std::lower_bound(label[it->vID].begin(), label[it->vID].end(), temp,
					[](const Pair a, const Pair& b) {
						return a.hID < b.hID;
					});
					label[it->vID].insert(it_1, temp);
				}
				// cout << "12\n";
				break;
			}
		}
		// delete[] inverted;

		// if (i % 1000 == 1) {
		// cout << "minimal Edge  " << i << " has ben constructed " << "\n";
		// }


	}

	
	end_time = std::chrono::high_resolution_clock::now();
	elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	cout << "minimal time is " << elapsed_time.count() << "\n";
	file << "minimal time is " << elapsed_time.count() << "\n";
	cout << "sumNum = " << sumNum << "\n";


	


	vte = 0;
	ete = 0;

	for (auto i = 0; i <= n; i++) {
		// cout << "for vertex " << i << "=============================\n";
		// for (auto p : label[i]) {
		// 	cout << "hID = " << p.hID << ", overlap = " << p.overlap << "\n";
		// }
		vte += label[i].size();
	}
	// while (true) {}
	cout << "total minimal vte = " << vte << "\n";
	file << "total minimal vte = " << vte << "\n";
	file.close();
	return;

	vte /= n;

	for (auto i = 1; i <= m; i++) {
		ete += ete_label[i].size();
	}
	ete /= m;
	cout << "average vte = " << vte << "\n";


	// cout << "construct time is " << elapsed_time.count() << "\n";


	// for (auto i = 1; i <= m; ++i) {
	// 	cout << "hyperedge " << idx[i] << " has importance " << i << "\n"; 
	// }


	// for (auto i = 1; i <= n; i++) {
	// 	cout << "for vertex " << i - 1 << ":\n";
	// 	for (auto p : label[(*vertex_map)[i - 1]]) {
	// 		cout << "eID = " << p.hID << ", overlap = " << p.overlap << "\n";
	// 	}
	// }













	long totalBytes = 0;
	for (int i = 1; i < n + 1; ++i) {
		totalBytes += sizeof(Pair) * label[i].size();
	}

	
	

	// file << "VTE index size is " << totalBytes / 1024 << "kb\n";
	// file << "VTE Container size is " << sizeof(vector<Pair>) * n /1024 << "kb\n"; 
	// file << "\n";
	// file.close();

	cout << "Minimal/non Minimal VTE index size is " << totalBytes / 1024 << ", "<< nonMinimaltotalBytes / 1024 << "kb\n";
	// cout << "VTE Container size is " << sizeof(vector<Pair>) * n /1024 << "kb\n"; 
	
	while (true){

	}

	long eteBytes = 0;
	for (int i = 1; i < m + 1; ++i) {
		eteBytes += sizeof(Pair) * ete_label[i].size();
	}
	cout << "ETE index size is " << eteBytes / 1024 << "kb\n";
	cout << "ETE Container size is " << sizeof(vector<Pair>) * m /1024 << "kb\n"; 
	// long memoryBefore = getMemoryUsage();

	long graphSize = 0;

	for (auto i = 1; i <= n; i++) {
		graphSize += E[i].size() * sizeof(int);
	}
	cout << "Graph size is " << graphSize /1024 << "kb\n"; 
	// delete[] label;
	// cout << "VTE index size is " << label->size() * sizeof(Pair) / 1024 / 1024 << "\n";
	// while (true){}


	// int c;
	// cin >> c;
	// tmpE = new vector<int> [n+1];
	// for (int i = 1; i <= n; i++) {
	// 	for (auto v : E[i]) {
	// 		tmpE[i].push_back(v);
	// 	}
	// }
	
	// delete[] label;
	// delete[] tmpE;
	// tmpE = nullptr;
	// while (true) {

	// }
	cout << "construction finished\n";
	
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



int SL::threshold_ete_reach(int src, int dst, bool original_id, int k) {
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];
	}
	// int overlap = 0;
	// if (src == dst) {
	// 	overlap = 1;
	// }

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
	auto srcIt = srcSet.begin();
	auto dstIt = dstSet.begin();
	while (srcIt != srcSet.end() && dstIt != dstSet.end()) {
		if (srcIt->hID > dstIt->hID || dstIt->overlap < k) {
			dstIt++;
		} else if (srcIt->hID < dstIt->hID || srcIt->overlap < k) {
			srcIt++;
		} else {
			return 1;
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
	return 0;
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


int SL::reach1(int src, int dst, bool original_id) {
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];		
	}

	int overlap = 0;
	if (src == dst) {
		overlap = 1;
	}
	auto srcIt = tmpLabel[src].begin();
	auto dstIt = tmpLabel[dst].begin();
	while (srcIt != tmpLabel[src].end() && dstIt != tmpLabel[dst].end()) {
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




int SL::threshold_reach(int src, int dst, bool original_id, int k) {
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];		
	}

	// int overlap = 0;
	// if (src == dst) {
	// 	overlap = 1;
	// }
	auto srcIt = label[src].begin();
	auto dstIt = label[dst].begin();
	while (srcIt != label[src].end() && dstIt != label[dst].end()) {
		if (srcIt->hID > dstIt->hID || dstIt->overlap < k) {
			dstIt++;
		} else if (srcIt->hID < dstIt->hID || srcIt->overlap < k) {
			srcIt++;
		} else {
			return 1;
		}

	}
	return 0;
}





int SL::baseLine(int src, int dst, bool original_id) {
	auto start_time = std::chrono::high_resolution_clock::now();
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];
	}


	vector<int> in_visit, out_visit;
	for (auto i = 0; i <= m; i++) {
		in_visit.push_back(0);
		out_visit.push_back(0);
	}
	priority_queue<Pair_in_queue> Q_in, Q_out;

	for (auto h : E[dst]) {
		// cout << "insert " << h << " with o = " << graph_edge[h].length << "\n";
		Q_in.push(Pair_in_queue(h, graph_edge[h].length, 0));
	}

	// cout << "for src:\n";
	for (auto h : E[src]) {
		// cout << "insert " << h << " with o = " << graph_edge[h].length << "\n";
		Q_out.push(Pair_in_queue(h, graph_edge[h].length, 0));
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
				auto end = std::chrono::high_resolution_clock::now();
				auto time_spent = std::chrono::duration_cast<std::chrono::seconds>(end - start_time);
				if (time_spent.count() > 100) return result;
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
					Q_in.push(Pair_in_queue(it->first, min(it->second, o), 0));
				}
				m.clear();
			}
			token = 1;
		} else {
			int size = Q_out.size();

			// cout << "now switch to out neighbour\n";
			// cout << "size = " << size << "\n";
			for (auto i = 0; i < size; i++) {
				auto end = std::chrono::high_resolution_clock::now();
				auto time_spent = std::chrono::duration_cast<std::chrono::seconds>(end - start_time);
				if (time_spent.count() > 100) return result;
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
					Q_out.push(Pair_in_queue(it->first, min(it->second, o), 0));
				}
				m.clear();	
			}
			token = 0;
		}

	}
	return result;
}	


int SL::threshold_baseLine(int src, int dst, bool original_id, int k) {
	auto start_time = std::chrono::high_resolution_clock::now();
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];
	}


	vector<int> in_visit, out_visit;
	for (auto i = 0; i <= m; i++) {
		in_visit.push_back(0);
		out_visit.push_back(0);
	}
	priority_queue<Pair_in_queue> Q_in, Q_out;

	for (auto h : E[dst]) {
		// cout << "insert " << h << " with o = " << graph_edge[h].length << "\n";
		Q_in.push(Pair_in_queue(h, graph_edge[h].length, 0));
	}

	// cout << "for src:\n";
	for (auto h : E[src]) {
		// cout << "insert " << h << " with o = " << graph_edge[h].length << "\n";
		Q_out.push(Pair_in_queue(h, graph_edge[h].length, 0));
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
				auto end = std::chrono::high_resolution_clock::now();
				auto time_spent = std::chrono::duration_cast<std::chrono::seconds>(end - start_time);
				if (time_spent.count() > 100) return -1;
				auto pair = Q_in.top();
				auto h = pair.hID;
				auto o = pair.overlap;
				
				// cout << "from in: get h = " << h << ", o = " << o << "\n";
				Q_in.pop();
				if (o < k) continue;
				if (out_visit[h]) {
					return 1;
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
					Q_in.push(Pair_in_queue(it->first, min(it->second, o), 0));
				}
				m.clear();
			}
			token = 1;
		} else {
			int size = Q_out.size();

			// cout << "now switch to out neighbour\n";
			// cout << "size = " << size << "\n";
			for (auto i = 0; i < size; i++) {
				auto end = std::chrono::high_resolution_clock::now();
				auto time_spent = std::chrono::duration_cast<std::chrono::seconds>(end - start_time);
				if (time_spent.count() > 100) return result;
				auto pair = Q_out.top();
				auto h = pair.hID;
				auto o = pair.overlap;
				// cout << "from out: get h = " << h << ", o = " << o << "\n";
				// cout << "get edge h = " << h << " with overlap = " << o << "\n";
				// if (h == 2578) cout << "2 detect 2578 with" << o << "\n";
				Q_out.pop();
				if (o < k) continue;
				
				if (in_visit[h]) {
					return 1;
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
					Q_out.push(Pair_in_queue(it->first, min(it->second, o), 0));
				}
				m.clear();	
			}
			token = 0;
		}

	}
	return 0;
}	



int SL::cover_check(int src, int dst, int k) {
	vector<int> in_visit, out_visit;
	for (auto i = 0; i <= m; i++) {
		in_visit.push_back(0);
		out_visit.push_back(0);
	}
	priority_queue<Pair_in_queue> Q_in, Q_out;
	Q_in.push(Pair_in_queue(src, graph_edge[idx[src]].length, 0));
	Q_out.push(Pair_in_queue(dst, graph_edge[idx[dst]].length, 0));
	int token = 0;
	int result = 0;
	while (!Q_in.empty() || !Q_out.empty()) {
		
		if (!token) {
			int size = Q_in.size();
			for (auto i = 0; i < size; i++) {
				auto pair = Q_in.top();
				auto h = pair.hID;
				auto o = pair.overlap;
				
				// cout << "from in: get h = " << h << ", o = " << o << "\n";
				Q_in.pop();
				if (out_visit[h] && h < src) {
					result = max(result, min(out_visit[h], o));
				}
				if (in_visit[h] >= o) continue;
				in_visit[h] = o;
				
				map<int, int> m;
	
				for (auto v : graph_edge[idx[h]].node) {
					if (v > n) continue;
					for (auto nextH : E[v]) {
						// if (h <= i) continue;
						// if (in_visit[nextH]) continue;
						if (m.find(order[nextH]) != m.end()) {
							m[order[nextH]]++;
						} else {
							m.insert(make_pair(order[nextH], 1));
						}
					}
				}

				for (auto it = m.begin(); it != m.end(); it++) {
					

					if (it->second <= result) continue;
					if (in_visit[it->first] >= min(it->second, o)) continue;
					Q_in.push(Pair_in_queue(it->first, min(it->second, o), 0));
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
				
				if (in_visit[h] && h < src) {
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
	
				for (auto v : graph_edge[idx[h]].node) {
					if (v > n) continue;
					for (auto nextH : E[v]) {
						// if (h <= i) continue;
						// if (out_visit[nextH]) continue;
						if (m.find(order[nextH]) != m.end()) {
							m[order[nextH]]++;
						} else {
							m.insert(make_pair(order[nextH], 1));
						}
					}
				}

				for (auto it = m.begin(); it != m.end(); it++) {

				
					if (it->second <= result) continue;
					if (out_visit[it->first] >= min(it->second, o)) continue;
					Q_out.push(Pair_in_queue(it->first, min(it->second, o), 0));
				}
				m.clear();	
			}
			token = 0;
		}
	}
	return result;
}



int SL::baseLine_with_nbr(int src, int dst, bool original_id) {
	auto start_time = std::chrono::high_resolution_clock::now();
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
		Q_in.push(Pair_in_queue(h, graph_edge[h].length, 0));
	}

	// cout << "for src:\n";
	for (auto h : E[src]) {
		// cout << "insert " << h << " with o = " << graph_edge[h].length << "\n";
		Q_out.push(Pair_in_queue(h, graph_edge[h].length, 0));
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
				auto end = std::chrono::high_resolution_clock::now();
				auto time_spent = std::chrono::duration_cast<std::chrono::seconds>(end - start_time);
				if (time_spent.count() > 100) return result;
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
				
				// map<int, int> m;


				
				// for (auto v : graph_edge[h].node) {
				// 	if (v > n) continue;
				// 	for (auto nextH : E[v]) {
				// 		// if (h <= i) continue;
				// 		// if (in_visit[nextH]) continue;
				// 		if (m.find(nextH) != m.end()) {
				// 			m[nextH]++;
				// 		} else {
				// 			m.insert(make_pair(nextH, 1));
				// 		}
				// 	}
				// }
				/*
				for (auto it = m.begin(); it != m.end(); it++) {
					

					if (it->second <= result) continue;
					if (in_visit[it->first] >= min(it->second, o)) continue;
					Q_in.push(Pair_in_queue(it->first, min(it->second, o)));
				}
				m.clear();
				*/
				for (auto it = allNbr[h].begin(); it != allNbr[h].end(); ++it) {
					if (it->second <= result) continue;
					if (in_visit[it->first] >= min(it->second, o)) continue;
					Q_in.push(Pair_in_queue(it->first, min(it->second, o), 0));
				}
			}
			token = 1;
		} else {
			int size = Q_out.size();

			// cout << "now switch to out neighbour\n";
			// cout << "size = " << size << "\n";
			for (auto i = 0; i < size; i++) {
				auto end = std::chrono::high_resolution_clock::now();
				auto time_spent = std::chrono::duration_cast<std::chrono::seconds>(end - start_time);
				if (time_spent.count() > 100) return result;
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

				
				// map<int, int> m;
	
				// for (auto v : graph_edge[h].node) {
				// 	if (v > n) continue;
				// 	for (auto nextH : E[v]) {
				// 		// if (h <= i) continue;
				// 		// if (out_visit[nextH]) continue;
				// 		if (m.find(nextH) != m.end()) {
				// 			m[nextH]++;
				// 		} else {
				// 			m.insert(make_pair(nextH, 1));
				// 		}
				// 	}
				// }
				/*
				for (auto it = m.begin(); it != m.end(); it++) {

				
					if (it->second <= result) continue;
					if (out_visit[it->first] >= min(it->second, o)) continue;
					Q_out.push(Pair_in_queue(it->first, min(it->second, o)));
				}
				m.clear();	
				*/
				for (auto it = allNbr[h].begin(); it != allNbr[h].end(); ++it) {
					if (it->second <= result) continue;
					if (out_visit[it->first] >= min(it->second, o)) continue;
					Q_out.push(Pair_in_queue(it->first, min(it->second, o), 0));
				}
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