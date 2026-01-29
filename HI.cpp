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
	old_vertex_map = &(graph -> old_vertex_map);
	vertex_id = graph->vertex_id;
	reverse_compact = &(graph->reverse_compact);
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

	// allNbr = new vector<pair<int, int>> [m + 1];
	nbr = new (std::nothrow) nbr_struct[m+1];

	D = new vector<QPair>[m + 1];
	D_e = new vector<QPair>[m + 1];
	QPairs = new vector<QPair>[m + 1];
	C = new int [m + 1];
	// inverted = new set<int> [m + 1];
	W = new set<int> [n + 1];
	total_count = 0;


	
	// while (true){}


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

	
	// while (true) {}

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
	if (D_e) delete[] D_e;
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
	
	if (currLabel != ete_label) {
		auto it = std::upper_bound(
			QPairs[h].begin(),
			QPairs[h].end(),
			QPair(u, overlap),
			[](const QPair& a, const QPair& b) {
				return a.overlap > b.overlap; // 自定义从大到小的比较规则
			}
		);
		QPairs[h].insert(it, QPair(u, overlap));
	} else {
		// cout << "insert(" << idx[u] << ", " << idx[h] << ", " << overlap << "\n";
		auto it = std::upper_bound(
			D_e[h].begin(),
			D_e[h].end(),
			QPair(u, overlap),
			[](const QPair& a, const QPair& b) {
				return a.overlap > b.overlap; // 自定义从大到小的比较规则
			}
		);
		D_e[h].insert(it, QPair(u, overlap));
	}
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




/*
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
			
		// for (auto it = m.begin(); it != m.end(); it++) {
			
			
		// 	if (min(overlap, it->second) <= global_visited_h[u]) {
		// 		// total_memory++;
		// 		continue;
		// 	} 
		// 	if (visited_h[it->first] >= min(overlap, it->second) || visited_h[it->first] == -1) continue;
		// 	visited_h[it->first] = min(overlap, it->second);
			
		// 	Q.push(Pair_in_queue(it->first, min(overlap, it->second), c_val));
		// }
		// // cout << "next BFS to :\n";
		// m.clear();
		

		for (auto it = nbr[h].begin(); it != nbr[h].end(); ++it) {
			if (min(overlap, it->second) <= global_visited_h[u]) {
				continue;
			} 
			if (visited_h[it->first] >= min(overlap, it->second)) continue;
			visited_h[it->first] = it->second;
			
			Q.push(Pair_in_queue(it->first, min(overlap, it->second)));
		}

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
*/



void SL::construct_for_a_vertex(HyperEdge * head,  int u, bool update) {
	int count = 0;
	int num = 0;
	ofstream myfile;
  	myfile.open ("out.txt");
	int max_h = 0;
	long long total = 0;
	int execute = 0;
	
	while (!Q.empty()) {
		Pair_in_queue pair = Q.top();
		Q.pop();
		int h = pair.hID;
		int overlap = pair.overlap;
		execute ++;
		// cout << "current h = " << idx[h] << "\n";
		// cout << "current MCD vlaue = " <<  nbr[h].max <<"\n";
		if (overlap > nbr[h].max) {

			add_triplet(ete_label, h, u, overlap, true);
			// max_h = max(max_h, overlap);
			
			for (auto v : graph_edge[idx[h]].node) {
				if (v > n) {
					continue;

				} else {
					if (visited[v] == 0) {
						visited[v] = overlap;
						add_triplet(tmpLabel, v, u, overlap, update);		
					}
				}
			}
		} else {
			continue;
		}
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
				

			}

			for (auto it = m.begin(); it != m.end(); it++) {
				// cout << "move to " << idx[it->first] << " with overlap " << it->second << "\n";
				Q.push(Pair_in_queue(it->first, min(overlap, it->second)));
				if (it->second > nbr[h].max && h > 1) {
	
					nbr[h].left.emplace_back(make_pair(it->first, it->second));
				}
			}
			m.clear();

		} else if (overlap <= nbr[h].max) {
		} else {
			nbr[h].max = overlap;
			for (auto it1 = nbr[h].left.begin(); it1 != nbr[h].left.end(); ) {
				if (it1->first > u) {
					Q.push(Pair_in_queue(it1->first, min(overlap, it1->second)));
				}
				if (it1->second <= nbr[h].max) {
					it1 = nbr[h].left.erase(it1);
				} else {
					++it1;
				}
			}
		}

	}
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
	// std::ofstream file(scalePath, std::ios::app);
	// if (!file.is_open()) {
    //     std::cerr << "无法打开文件: " << scalePath << std::endl;
    //     return;
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
		// cout << "\n------------------------------construct for hID = " << idx[i] << " with overlap = " << graph_edge[idx[i]].length << "-----------------------------\n";
		
	
		Q.push(Pair_in_queue(i, graph_edge[idx[i]].length));
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
	
	
	std::ofstream file(scalePath, std::ios::app);
	if (!file.is_open()) {
        std::cerr << "无法打开文件: " << scalePath << std::endl;
        return;
    }

	file << "construct time is " << elapsed_time.count() << "\n";
	
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
	int c;
	
	// while (cin >> c){
	// 	if (c == 1) break;
	// }
	// file << "construct time is " << elapsed_time.count() << "\n";
	// label = tmpLabel;
	// return;

	double vte = 0;

	// for (auto i = 0; i <= n; i++) {
	// 	cout << "for vertex " << i << "=============================\n";
	// 	for (auto p : label[i]) {
	// 		cout << "hID = " << p.hID << ", overlap = " << p.overlap << "\n";
	// 	}
	// 	vte += label[i].size();
	// }
	// cout << "tmp total vte = " << vte << "\n";
	// while (true){}
	// delete[] visited;
	// delete[] visited_h;
	
	cout << "here\n";
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

	// cout << "0\n";
	int sumNum = 0;
	int* vis = new int[n + 1]();
	// fill(vis, vis + n + 1, 0);
	start_time = std::chrono::high_resolution_clock::now();
	for (auto i = 1; i <= m; ++i) {
		// cout << "1\n";
		// if (i % 1000 == 1) {
			// cout << "Minimal for i = " << i << "\n";
		// }
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

	delete[] vis;
	


	vte = 0;
	ete = 0;

	// for (auto i = 1; i <= m; i++) {
	// 	cout << "eID = " << idx[i] << " map to " << i << "\n";  
	// }


	for (auto i = 0; i <= n; i++) {
		// cout << "for vertex " << i << "=============================\n";
		for (auto p : label[i]) {
			// cout << "hID = " << idx[p.hID] << ", overlap = " << p.overlap << "\n";
		}
		vte += label[i].size();
	}
	// while (true) {}
	cout << "total minimal vte = " << vte << "\n";
	file << "total minimal vte = " << vte << "\n";
	// file.close();
	// return;

	vte /= n;

	for (auto i = 1; i <= m; i++) {
		ete += ete_label[i].size();
	}
	ete /= m;
	cout << "average vte = " << vte << "\n";
	cout << "average ete = " << ete << "\n";



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

	
	

	file << "VTE index size is " << totalBytes / 1024 << "kb\n";
	file << "VTE Container size is " << sizeof(vector<Pair>) * n /1024 << "kb\n"; 
	// file << "\n";
	// file.close();

	cout << "Minimal/non Minimal VTE index size is " << totalBytes / 1024 << ", "<< nonMinimaltotalBytes / 1024 << "kb\n";
	file << "Minimal/non Minimal VTE index size is " << totalBytes / 1024 << ", "<< nonMinimaltotalBytes / 1024 << "kb\n";
	
	// cout << "VTE Container size is " << sizeof(vector<Pair>) * n /1024 << "kb\n"; 
	
	// while (true){

	// }

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
	file << "Graph size is " << graphSize /1024 << "kb\n"; 
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
	/*
	allNbr = new vector<pair<int, int>> [m + 1];
	
	for (auto i = 0; i <= m; i++) {
		map<int, int> m;
		
		for (auto j : graph_edge[i].node) {
			
			for (auto k : E[j]) {

				if (m.find(k) != m.end()) {
					m[k]++;
				} else {
					m.insert(make_pair(k, 1));
				}
			}
		}
	
		for (auto it = m.begin(); it != m.end(); ++it) {
			allNbr[i].push_back(*it);
		}
	}
	total_memory += sizeof(allNbr);
	total_memory += (m + 1) * sizeof(std::vector<std::pair<int, int>>);
	for (int i = 0; i <= m; ++i) {
        total_memory += allNbr[i].capacity() * sizeof(std::pair<int, int>);
    }

	std::cout << "Total memory used by allNbr: " << total_memory / 1024 / 1024<< " MB" << std::endl;
	file << "Total memory used by allNbr: " << total_memory / 1024 / 1024<< " MB" << std::endl;
	*/
	cout << "construction finished\n";


	// cout << "display vertex_map here\n";
	// for (auto it = (*vertex_map).begin(); it != (*vertex_map).end(); ++it) {
	// 	cout << it->first << " maps to " << it->second << "\n";
	// }

	// cout << "=====================\n";

	// cout << "display old vertex_map here\n";
	// for (auto it = (*old_vertex_map).begin(); it != (*old_vertex_map).end(); ++it) {
	// 	cout << it->first << " maps to " << it->second << "\n";
	// }

	// while (true){}


	// while (true){}
	// int e;
	// cin >> e;

	// for (auto i = 1; i <= m; i++) {
	// 	cout << "for e = " << i << "\n";
	// 	for (auto it1 = ete_label[i].begin(); it1 != ete_label[i].end(); ++it1) {
	// 		cout << (*it1).hID << " " << (*it1).overlap << ", ";
	// 	}
	// 	cout << "\n";
	// }
	// while (true){}

	// cout << "before insert size is " << graph_edge[2].length << "\n";
	// insert_node(2, 1);
	// cout << "after insert\n";
	// for (auto i = 1; i <= m; i++) {
	// 	cout << "for e = " << i << "\n";
	// 	cout << "ete_label details";
	// 	for (auto it1 = ete_label[i].begin(); it1 != ete_label[i].end(); ++it1) {
	// 		cout << (*it1).hID << " " << (*it1).overlap << ", ";
	// 	}
	// 	cout << "\n";
	// 	cout << "V[" << i << "] details: \n";
	// 	for (auto  v : graph_edge[i].node) { 
	// 		cout << v << " ";
	// 	}
	// 	cout << "\n";

	// }

	
	// while (true){}
}


// insert section

bool SL::insert_node(int selected_edge, int inserted_node) {
	
    BlockTimer t_all(prof.total);
	
	// return true;
	// cout << "E[" << (*vertex_map)[inserted_node] << "]= " <<E[(*vertex_map)[inserted_node]].size() << "\n";
    // [Block 1] check exist
    std::vector<int>::iterator it;
    {
        BlockTimer t(prof.check_exist);
		// cout << "try search node " << inserted_node << " (originally " << vertex_id[inserted_node] << ") in edge " << selected_edge << "\n";
		// cout << "node map to " << (*vertex_map)[vertex_id[inserted_node]] << "\n";
		// cout << "current edge exists nodes : ";
		// for (auto tmp = graph_edge[selected_edge].node.begin(); tmp != graph_edge[selected_edge].node.end(); ++tmp) {
		// 	cout << *tmp << " ";
		// }
		// cout << " (originally ";
		// for (auto tmp = graph_edge[selected_edge].node.begin(); tmp != graph_edge[selected_edge].node.end(); ++tmp) {
		// 	cout << vertex_id[*tmp] << " ";
		// }
		// cout << ")\n";
		// cout << "selected_edge = " << selected_edge << "\n";
		// cout << "for edge 7 before check --- with length: " << graph_edge[7].length << ": [";
		// for (auto v : graph_edge[7].node) {
		// 	cout << vertex_id[v] << " ";
		// }
		// cout << "\n";
		// cout << "map check to " << (*vertex_map)[vertex_id[inserted_node]] << " which is initially " << vertex_id[(*vertex_map)[vertex_id[inserted_node]]]  <<"\n";
		for (it = graph_edge[selected_edge].node.begin(); it != graph_edge[selected_edge].node.end(); ++it) {
			// cout << "currenly visited: " << vertex_id[*it] << "\n";
			if (*it == (*vertex_map)[vertex_id[inserted_node]]) return false;
		}

        // it = std::lower_bound(graph_edge[selected_edge].node.begin(),
        //                       graph_edge[selected_edge].node.end(),
        //                       (*vertex_map)[vertex_id[inserted_node]]);
		// cout << "binary search *it = " << *it << "\n";
        // if (it != graph_edge[selected_edge].node.end() &&
        //     *it == (*vertex_map)[vertex_id[inserted_node]]) return false;
    }

    // [Block 2] init + remap
	
	// cout << "]\n";
	// cout << "for D_e(9): [";
	// for (auto tmp = D_e[order[9]].begin(); tmp != D_e[order[9]].end(); ++tmp) {
	// 	cout << "("<< idx[tmp->vID] << ", "  << tmp->overlap << "), ";
	// }
	// cout << "]\n";

	// cout << "for D_e(1): [";
	// for (auto tmp = D_e[order[1]].begin(); tmp != D_e[order[1]].end(); ++tmp) {
	// 	cout << "("<< idx[tmp->vID] << ", "  << tmp->overlap << "), ";
	// }
	// cout << "]\n";
	// cout << "for ete(1): [";
	// for (auto tmp = ete_label[order[1]].begin(); tmp != ete_label[order[1]].end(); ++tmp) {
	// 	cout << "("<< idx[tmp->hID] << ", "  << tmp->overlap << "), ";
	// }
	// cout << "]\n";
	// cout << "for ete(7): [";
	// for (auto tmp = ete_label[order[7]].begin(); tmp != ete_label[order[7]].end(); ++tmp) {
	// 	cout << "("<< idx[tmp->hID] << ", "  << tmp->overlap << "), ";
	// }
	// cout << "]\n";
	

	// // cout << "rank for edge 1, 2 is " << order[1] << " " << order[2] << "\n";
	// cout << "start inserting\n";
	// cout << "id-> rank: " << 1 << "->" << order[1] << ", " << 12 << "->" << order[12] << ", " << 17 << "->" << order[17] << "\n";
    {
        BlockTimer t(prof.init_and_remap);

        fill(visited_h, visited_h + m + 1, 0);
        if (E[inserted_node].size() == 1) {
			// cout << "visit here123\n";
			// while (true){}
            // label[(*old_vertex_map)[inserted_node]] = label[(*vertex_map)[inserted_node]];
			if (inserted_node == (*vertex_map)[vertex_id[inserted_node]]) {
				// cout << "the first represented node detected 1\n";
				int head = -1;
				// cout << "check for edge " << *(E[inserted_node].begin()) << "\n"; 
				// cout << "current size = " << (*reverse_compact)[inserted_node].size() << "\n";
				for (auto it_r = (*reverse_compact)[inserted_node].begin(); it_r != (*reverse_compact)[inserted_node].end(); ) {
					if (head == -1) {
						head = *it_r;
						// cout << "new head = " << vertex_id[head] << "\n";
						(*vertex_map)[vertex_id[*it_r]] = *it_r;
						
						label[*it_r] = label[(*vertex_map)[vertex_id[inserted_node]]];
						graph_edge[*(E[inserted_node].begin())].node.push_back(head);
						// cout << "head set to " << vertex_id[*it_r] << "\n";
						// cout << "now 1254 map to " << vertex_id[(*vertex_map)[vertex_id[*it_r]]] << "\n";
						it_r = (*reverse_compact)[inserted_node].erase(it_r);
						
					} else {
					
						(*vertex_map)[vertex_id[*it_r]] = (*vertex_map)[vertex_id[head]];
						++it_r;
					}	
				}
				(*reverse_compact)[head] = (*reverse_compact)[inserted_node];
			} else {
				label[inserted_node] = label[(*vertex_map)[vertex_id[inserted_node]]];
				// cout << "old " << (*old_vertex_map)[inserted_node] << " maps to " << (*vertex_map)[inserted_node] << "\n";
				// cout << "old id: " << vertex_id[(*old_vertex_map)[inserted_node]] << " maps to " << vertex_id[(*vertex_map)[inserted_node]] << "\n";
				// cout << "current inserted_label contains\n";
				// for (auto it = label[inserted_node].begin(); it != label[inserted_node].end(); ++it) {
				// 	cout << "(" << it->hID << ", " << it->overlap << ")\n";
				// } 
				// cout << "=============\n";
				// cout << "originally map to " << (*vertex_map)[vertex_id[inserted_node]] << " and currently map to " << (*old_vertex_map)[vertex_id[inserted_node]] << "\n";
				// cout << "originally vertex id to " << vertex_id[(*vertex_map)[vertex_id[inserted_node]]] << " and currently vertex id to " << vertex_id[(*old_vertex_map)[vertex_id[inserted_node]]] << "\n";
				
				for (auto it_r = (*reverse_compact)[(*vertex_map)[vertex_id[inserted_node]]].begin(); it_r != (*reverse_compact)[(*vertex_map)[vertex_id[inserted_node]]].end();) {
					if (*it_r == inserted_node) {
						it_r = (*reverse_compact)[(*vertex_map)[vertex_id[inserted_node]]].erase(it_r);
					} else {
						it_r++;
					}
				}


				(*vertex_map)[vertex_id[inserted_node]] = (*old_vertex_map)[vertex_id[inserted_node]];
				

				bool exist = false;
				for (auto in_it = graph_edge[*(E[inserted_node].begin())].node.begin(); in_it != graph_edge[*(E[inserted_node].begin())].node.end(); ++in_it) {
					if (*in_it == inserted_node) exist = true;
				}
				if (!exist) {
					graph_edge[*(E[inserted_node].begin())].node.push_back(inserted_node);
				}

			}
			
        }
        // inserted_node = (*vertex_map)[inserted_node];
    }
	
	

	// cout << "for edge 1 before with length: " << graph_edge[1].length << ": [";
	// for (auto v : graph_edge[1].node) {
	// 	cout << vertex_id[v] << " ";
	// }
	// cout << "]\n";
	// cout << "for edge 2 before with length: " << graph_edge[2].length << ": [";
	// for (auto v : graph_edge[2].node) {
	// 	cout << vertex_id[v] << " ";
	// }
	// cout << "]\n";

    auto original_size = graph_edge[selected_edge].length;
	graph_edge[selected_edge].length++;
	// cout << "original size for edge " << selected_edge << " is " << original_size << "\n";
	// cout << "current label = ";
	// for (auto it = ete_label[order[selected_edge]].begin(); it != ete_label[order[selected_edge]].end(); ++it) {
	// 	cout << "(" << idx[it->hID] << ", " << it->overlap << ") ";
	// }
	// cout << "\n";

	// 
	// cout << "before for current node " << vertex_id[(*vertex_map)[222]] << " its E :";
	// for (auto e : E[(*vertex_map)[222]]) {
	// 	cout << e << " ";
	// }
	// cout << "\n";

    // [Block 3] update core structures: V[e] and E[v]
    {
        BlockTimer t(prof.update_struct);
		bool exist1 = false;
		// for (auto in_it = graph_edge[inserted_node].node.begin(); in_it != graph_edge[inserted_node].node.end(); ++in_it) {
		// 	if (*in_it == inserted_node) exist1 = true;
		// }
		// if (!exist1) {
		graph_edge[selected_edge].node.push_back(inserted_node);
		// }
        // graph_edge[selected_edge].node.push_back(inserted_node);
		
        it = std::lower_bound(E[inserted_node].begin(), E[inserted_node].end(), selected_edge);
        E[inserted_node].insert(it, selected_edge);
    }
	
	// cout << "for edge 1 after with length: " << graph_edge[1].length << ": [";
	// for (auto v : graph_edge[1].node) {
	// 	cout << vertex_id[v] << " ";
	// }
	// cout << "]\n";
	// cout << "for edge 2 after with length: " << graph_edge[2].length << ": [";
	// for (auto v : graph_edge[2].node) {
	// 	cout << vertex_id[v] << " ";
	// }
	// cout << "]\n";


	for (auto it = ete_label[order[selected_edge]].begin(); it != ete_label[order[selected_edge]].end(); ++it) {
		auto it2 = std::lower_bound(
			label[inserted_node].begin(), label[inserted_node].end(), it->hID,
			[](const Pair& p, int id){ return p.hID < id; }
		);
		if (it2 == label[inserted_node].end() ||  it2->hID != it->hID) {
			label[inserted_node].insert(it2, Pair(it->hID, it->overlap));
		} else {
			it2->overlap = max(it2->overlap, it->overlap);
		}
	}
	
    // [Block 4] build isCand + cnt
    auto cand = E[inserted_node];
    std::vector<unsigned char> isCand(m + 1, 0);
    std::vector<int> cnt(m + 1, 0);
	priority_queue<Pair_in_queue> pq;
    {
        BlockTimer t(prof.build_cnt);

        for (int eid : cand) isCand[order[eid]] = 1;
        // isCand[order[selected_edge]] = 0;

        for (int v : graph_edge[selected_edge].node) {
			// cout << "for vertex " << vertex_id[v] << "\n";
            for (int eid : E[v]) {
                if (isCand[order[eid]]) {
					// cout << "find " << eid << "\n";
					++cnt[order[eid]];
				}
            }
        }
    }
		// cout << "cnt[2] = " << cnt[order[2]] << "\n";
	cnt[order[selected_edge]] = graph_edge[selected_edge].length;
	//triplets -> order id
	vector<pair<int,Pair>> triplets;
	vector<pair<int,Pair>> De_triplets;
	map<int,int> mayUpdate, De_mayUpdate;
	// 将所有select_Edge 的label/value 全部存进important edges里
	// importance -> order id
	// needIncrement -> order id
	std::vector<int> important(m+1);
	for (auto p : ete_label[order[selected_edge]]) {
		important[p.hID] = p.overlap;
	}

	// for (auto p :D_e[order[selected_edge]]) {
	// 	important[p.vID] = p.overlap;
	// }
	

	vector<int> needIncrement(m+1);
	vector<bool> label_h_update(m+1);
	map<int, int> Dh;
	
	// cout << "erasing cands\n";
	for (auto it = cand.begin(); it != cand.end();) {
		auto cur = ete_edge_reach(order[*it], order[selected_edge]);

		if (cnt[order[*it]] <= cur) {
			// cout << "erase " << *it << " since it already covered " << cur << "\n";
			cand.erase(it);
		} else {
			Dh[order[*it]] = cur;
			++it;
 		}
	}

	// cout << "update importants\n";
	int max_cover_itself = 0;
	for (auto eid : cand) {
		// if (eid == selected_edge) continue;
		int ov = cnt[order[eid]];
		// Dh[order[eid]] = max(ov, Dh[order[eid]]);
		if (ov > 1) {
			// cout << "check for nbr " << eid << " with overlap " << ov << "\n";
			for (auto p : ete_label[order[eid]]) {
				// cout << "further explore etelabel: (" << idx[p.hID] << ", " << p.overlap << ")\n";
				if (p.overlap < ov) continue; 
				// cout << "processed\n";
				Dh[p.hID] = max(Dh[p.hID], min(ov, p.overlap));
				if (p.overlap > important[p.hID] && ov > important[p.hID]) {
					if (important[p.hID] == 0) {
						// cout << "added to mayUpate\n";
						mayUpdate[p.hID] = max(mayUpdate[p.hID], min(ov, p.overlap));
					} else {
						needIncrement[p.hID] = 1;
					}
				}
			}

			for (auto p : D_e[order[eid]]) {
				if (p.overlap < ov) continue;
				Dh[p.vID] = max(Dh[p.vID], min(ov, p.overlap));
				// if (p.overlap > important[p.vID] && ov > important[p.vID]) {

					// if (important[p.hID] == 0) {
					// 	De_mayUpdate[it->hID] = max(De_mayUpdate[it->hID], min(ov, p.overlap));
					// } else {
					// 	needIncrement[p.hID] = 1;
					// }
				// }
			}
		}
	}
	// cout << "update ete_label[h]\n";
	for (auto it = ete_label[order[selected_edge]].begin(); it != ete_label[order[selected_edge]].end(); ++it) {
		// cout << "for existing entry " << idx[it->hID] << ", " << it->overlap << "\n";
		if (needIncrement[it->hID] == 1) {
			(it->overlap)++;
			triplets.push_back(make_pair(order[selected_edge], Pair(it->hID, it->overlap)));
			label_h_update[it->hID] = 1;
			// if (selected_edge == 3 && idx[it->hID] == 5 && it->overlap == 2) {
			// 	cout << "1\n";
			// 	while (true){}
			// }  
			
			// cout << "add (" << selected_edge << ", " << idx[it->hID] << ", " << it->overlap << ") via update existing ete label\n";   
		
			

		}
		





		max_cover_itself = max(max_cover_itself, it->overlap);
		
	}
	// cout << "update itself\n";
	if (max_cover_itself < original_size + 1) {
		// cout << "try insert itself into ete_label\n";
		auto itself_it = std::lower_bound(
			ete_label[order[selected_edge]].begin(), ete_label[order[selected_edge]].end(), order[selected_edge],
			[](const Pair& p, int id){ return p.hID < id; }
		);
		// cout << "2\n";
		// cout << "try printing current ete_label:";
		// for (auto tmp = ete_label[order[selected_edge]].begin(); tmp != ete_label[order[selected_edge]].end(); ++tmp) {
		// 	cout << "(" << tmp->hID << ", " << tmp->overlap << ") ";
		// }
		// cout << "\n";
		if (itself_it == ete_label[order[selected_edge]].end() || itself_it->hID != order[selected_edge]) {
			ete_label[order[selected_edge]].insert(itself_it, Pair(order[selected_edge], original_size + 1));
		} else {
			// cout << "add itself ++++++++++++++++++++++\n";
			itself_it->overlap = original_size + 1;      
		}
		triplets.push_back(make_pair(order[selected_edge], Pair(order[selected_edge], original_size + 1)));   
		label_h_update[order[selected_edge]] = 1;
		important[order[selected_edge]] = max(important[order[selected_edge]], original_size + 1);		 
	}


	// for (auto it = D_e[order[selected_edge]].begin(); it != D_e[order[selected_edge]].end(); ++it) {
	// 	cout << "for existing entry (D_e) " << idx[it->hID] << ", " << it->overlap << "\n";
	// 	if (needIncrement[it->hID] == 1) {
	// 		(it->overlap)++;
	// 		De_triplets.push_back(make_pair(it->hID, Pair(order[selected_edge], it->overlap)));
	// 		cout << "add (" << idx[it->hID] << ", " << selected_edge << ", " << it->overlap << ") via update existing D_e label\n";   
	// 	}
	// }


	// cout << "2\n";
	// for (auto eid : cand) {
	// 	if (cnt[order[eid]] == 1) continue;
	// 	for (auto it = ete_label[order[eid]].begin(); it != ete_label[order[eid]].end(); ++it) {
	// 		if (it->hID < order[selected_edge]) {
	// 			mayUpdate[it->hID] = max(mayUpdate[it->hID], min(cnt[order[eid]], it->overlap));
	// 		}
	// 	}
	// 	// 这个好像暂时不用考虑
	// 	// for (auto it = D_e[order[eid]].begin(); it != D_e[order[eid]].end(); ++it) {
	// 	// 	mayUpdate[it->hID] = max(mayUpdate[it->hID], min(cnt[order[eid]], it->overlap));
	// 	// } 
	// }
	// cout << "update mayUpdate\n";
	for (auto it = mayUpdate.begin(); it != mayUpdate.end(); ++it) {	
		auto it2 = std::lower_bound(
			ete_label[order[selected_edge]].begin(), ete_label[order[selected_edge]].end(), it->first,
			[](const Pair& p, int id){ return p.hID < id; }
		);

		if (it2 != ete_label[order[selected_edge]].end() && it2->hID == it->first) {
			// cout << "should not here123\n";
			// while (true){}
			if (it2->hID != it->first) {
				ete_label[order[selected_edge]].insert(it2, Pair(it->first, it->second));    
				triplets.push_back(make_pair(order[selected_edge], Pair(it->first, it->second))); 
				label_h_update[it->first] = 1;
			} else if (it2->overlap < it->second) {
				it2->overlap = it->second;
				triplets.push_back(make_pair(order[selected_edge], Pair(it->first, it->second)));    
				label_h_update[it->first] = 1;
			} else {
				// cout << "should not be here\n";
				// while (true){}
			}
		} else {
			ete_label[order[selected_edge]].insert(it2, Pair(it->first, it->second));  
			triplets.push_back(make_pair(order[selected_edge], Pair(it->first, it->second)));     
			label_h_update[it->first] = 1;
		}
	}

	
	// cout << "updateDirect\n";
	vector<pair<int, int>> updateDirect(Dh.begin(), Dh.end());
	sort(updateDirect.begin(), updateDirect.end(),
          [](const auto& x, const auto& y){
              if (x.second != y.second) return x.second < y.second;
              return x.first < y.first;   // 次关键字
          });

	// cout << "Update Direct info here:============================================\n";
	// for (auto it = updateDirect.begin(); it!= updateDirect.end(); ++it) {
	// 	cout << "(" << it->first << ", " << it->second << ")\n";
	// }

	bool maxCover = 0;
	// cout << "Using h as the intermediate !!\n";
	for (auto it = ete_label[order[selected_edge]].begin(); it != ete_label[order[selected_edge]].end(); ++it) {
		// cout << "for important edge " << idx[it->hID] << " with overlap " << it->overlap << "\n";
		// cout << "update 1\n";
		if (it->overlap > maxCover) {
			maxCover = it->overlap;
		} else {
			continue;
		}

		if (label_h_update[it->hID]) {
			// migrate
			// cout << "1\n";
			auto migrate_it = ete_label[it->hID].begin();
			for (; migrate_it != ete_label[it->hID].end(); ++migrate_it) {
				if (migrate_it->overlap < it->overlap) break;
			}
			// cout << "2\n";
			if (migrate_it != ete_label[it->hID].end() && migrate_it->hID != it->hID) {
				// cout << "migrate " << "D(" << idx[migrate_it->hID] << ") to " << idx[it->hID] << "\n";
				for (auto it2 = D_e[migrate_it->hID].begin(); it2 != D_e[migrate_it->hID].end(); ++it2) {
					// cout << "received (" << idx[it2->vID] << ", " << it2->overlap << ")\n";
					if (it2->vID < it->hID) continue;
					// cout << "4\n";
					auto it3  = std::lower_bound(
						D_e[it->hID].begin(), D_e[it->hID].end(), it2->vID,
						[](const QPair& p, int id){ return p.vID < id; }
					);
					// cout << "5\n";
					// auto currOv = it3->overlap;
					if (it3 == D_e[it->hID].end() || it3->vID != it2->vID) {
						// cout << "add (" << idx[it2->vID] << ", " << min(migrate_it->overlap, it2->overlap) << ") into D(" << idx[migrate_it->hID] << ")\n";
						// cout << "5.1\n";
						D_e[it->hID].insert(it3, QPair(it2->vID, min(migrate_it->overlap, it2->overlap)));
					} else {
						// cout << "5.2\n";
						// cout << "insert \n";

						it3->overlap = max(it3->overlap, min(it2->overlap, migrate_it->overlap));
						// cout << "now overlap of " << idx[it3->vID] << " is " << it3->overlap << "\n";
					}
					// cout << "6\n";
					auto it4 = std::lower_bound(
						ete_label[it2->vID].begin(), ete_label[it2->vID].end(), it->hID,
						[](const Pair& p, int id){ return p.hID < id; }
					);
					// cout << "7\n";
					if (it4 == ete_label[it2->vID].end() || it4->hID != it->hID) {
						// cout << "8\n";
						ete_label[it2->vID].insert(it4, Pair(it->hID, min(migrate_it->overlap, it2->overlap)));
						triplets.push_back(make_pair(it2->vID, Pair(it->hID, min(migrate_it->overlap, it2->overlap))));   
					} else {
						// cout << "9\n";
						// cout << migrate_it->overlap << " 10\n";
						// cout << it2->overlap << " 11\n";
				
						if (it4->overlap < min(migrate_it->overlap, it2->overlap)) {
							// cout << "10\n";
							it4->overlap = min(migrate_it->overlap, it2->overlap);
							triplets.push_back(make_pair(it2->vID, Pair(it->hID, min(migrate_it->overlap, it2->overlap))));   
						}
					}
				}
			}
			
		}
		

		// auto it2 = std::lower_bound(
		// 	updateDirect.begin(), updateDirect.end(), it->overlap,
		// 	[](const auto& p, int key){
		// 		return p.second < key;   // 找第一个 second >= k
		// 	}
		// );

		// cout << "check for overlap value >= " << it->overlap << "\n";
		// for (; it2 != updateDirect.end(); ++it2) {
		// 	cout << "found " << it2->first << "\n";
		// 	if (it2->first <= it->hID) continue;
		// 	cout << "process " << it2->first<<"\n";
		// 	int currReach = max(ete_edge_reach(it2->first, order[selected_edge]), it2->second);
		// 	currReach = min(currReach, it->overlap);
		// 	cout << "max reach = " << currReach << "\n";
		// 	auto it3  = std::lower_bound(
		// 		D_e[it->hID].begin(), D_e[it->hID].end(), it2->first,
		// 		[](const QPair& p, int id){ return p.vID < id; }
		// 		);

		// 	if (it3 == D_e[it->hID].end() || it3->vID != it2->first) {
		// 		D_e[it->hID].insert(it3, QPair(it2->first, currReach));
		// 		triplets.push_back(make_pair(it2->first, Pair(it->hID, currReach)));
		// 	} else {
		// 		if (it3->overlap < currReach) {
		// 			it3->overlap = currReach;
		// 			triplets.push_back(make_pair(it2->first, Pair(it->hID, currReach)));
		// 		} 
		// 	}

		// }
		// cout << "update 2\n";

		for (auto it2 = D_e[it->hID].begin(); it2 != D_e[it->hID].end(); ++it2) {
			// cout << "3\n";
			int currReach = max(ete_edge_reach(it2->vID, order[selected_edge]), Dh[it2->vID]);
			// if (isCand[it2->vID]) {
			// 	currReach = max(cnt[it2->vID], cnt[it2->vID]);
			// } 
			// cout << " checking " << idx[it2->vID] << " with h->v: " << it2->overlap << ", current h->w = " << it->overlap << " and currReach = " << currReach << "\n";
			if (it2->overlap < it->overlap && currReach > it2->overlap) {
				// cout << "update!\n";
				auto it3 = std::lower_bound(
				ete_label[it2->vID].begin(), ete_label[it2->vID].end(), it->hID,
				[](const Pair& p, int id){ return p.hID < id; }
				);

				if (it3 != ete_label[it2->vID].end() && it3->hID == it->hID) {
					if (it3->overlap < min(it->overlap, currReach)) {
						it3->overlap = min(it->overlap, currReach);
						triplets.push_back(make_pair(it2->vID, Pair(it->hID, it3->overlap)));   
					    	
					}
					// it->overlap = std::max(it->overlap, overlap);
				} else {
					cout << "123\n";
					while (true){}
					ete_label[it2->vID].insert(it3, Pair(it->hID, it3->overlap));    
					triplets.push_back(make_pair(it2->vID, Pair(it->hID, it3->overlap)));         
				}
			}
		}
	
		// cout << "next\n";
	}

	// for (auto it = De_mayUpdate.begin(); it != De_mayUpdate.end(); ++it) {	
	// 	auto it2 = std::lower_bound(
	// 		D_e[it->first].begin(), D_e[it->first].end(), order[selected_edge],
	// 		[](const QPair& p, int id){ return p.vID < id; }
	// 	);

	// 	if (it2 != D_e[it->first].end()) {
	// 		cout << "should not be here!\n";
	// 		while (true){}
	// 		if (it2->vID != order[selected_edge]) {
	// 			D_e[it->first].insert(it2, Pair(order[selected_edge], it->second));    
	// 			de_triplets.push_back(make_pair(it->first, Pair(order[selected_edge], it->second))); 
	// 		} else if (it2->overlap < it->second) {
				
	// 			it2->overlap = it->second;
	// 			de_triplets.push_back(make_pair(it->first, Pair(order[selected_edge], it->second)));    
	// 		} else {
	// 			cout << "should not be here\n";
	// 			while (true){}
	// 		}
	// 	} else {
	// 		D_e[it->first].insert(it2, Pair(order[selected_edge], it->second));  
	// 		de_triplets.push_back(make_pair(it->first, Pair(order[selected_edge], it->second)));     
	// 	}
	// }



	
	auto maxEID = (ete_label[order[selected_edge]].begin())->hID;
	// cout << " for new CC existing max EID in ete_label is " << maxEID << "(idx = " << idx[maxEID] << ", " << (ete_label[order[selected_edge]].begin())->overlap << ")\n";
	for (auto eid : cand) {
		// cout << "try checking nbr " << eid << " with overlap " << cnt[order[eid]] << "\n";
		
		// cout << "ete edge check with " << eid << " and " << idx[maxEID] << " = " << ete_edge_reach(order[eid], maxEID) << "\n";
		// cout << "for current label_e[" << eid << "]: ";
		// for (auto tmp = ete_label[order[eid]].begin(); tmp != ete_label[order[eid]].end(); ++tmp) {
		// 	cout << "(" << idx[tmp->hID]  << "({" << tmp->hID  << "}, " << tmp->overlap << ") ";
		// }
		// cout << "\n";
		// cout << "for current label_e[" << idx[maxEID] << "]: ";
		// for (auto tmp = ete_label[maxEID].begin(); tmp != ete_label[maxEID].end(); ++tmp) {
		// 	cout << "(" << idx[tmp->hID] << "({" << tmp->hID  << "}, " << tmp->overlap << ") ";
		// }
		// cout << "\n";
		if (cnt[order[eid]] == 1 && ete_edge_reach(order[eid], maxEID) == 0) {
			
			auto maxEID_nbr = (ete_label[order[eid]].begin())->hID;
			// cout << "for new CC found " << eid << " contribute new CC with stored hID = " << maxEID_nbr << "(idx = " << idx[maxEID_nbr] << "\n";
			if (maxEID_nbr < maxEID) {
				for (auto it = D_e[maxEID].begin(); it != D_e[maxEID].end(); ++it) {
					ete_label[it->vID].insert(ete_label[it->vID].begin(), Pair(maxEID_nbr, 1));
					triplets.push_back(make_pair(it->vID, Pair(maxEID_nbr, 1)));
					
				}
			} else {
				for (auto it = D_e[maxEID_nbr].begin(); it != D_e[maxEID_nbr].end(); ++it) {
					ete_label[it->vID].insert(ete_label[it->vID].begin(), Pair(maxEID, 1));
					triplets.push_back(make_pair(it->vID, Pair(maxEID, 1)));
				}
			}
		} else {
			// cout << "pruning \n";
		}
	}

	// cout << "updating triplets\n";
	map<int, map<int, int>> insert;

	for (auto it = triplets.begin(); it != triplets.end(); ++it) {
		
		int from = it->first;
		const Pair& inserted_pair = it->second;

		int to = inserted_pair.hID;
		int overlap = inserted_pair.overlap;
		// cout << "=================== triplets grab (" << idx[from] << ", " << idx[to] << ", " << overlap << ")\n"; 
		auto it2 = std::lower_bound(
			D_e[to].begin(), D_e[to].end(), from,
			[](const QPair& p, int id){ return p.vID < id; }
		);

		if (it2 == D_e[to].end() || it2->vID != from) {
			D_e[to].insert(it2, QPair(from, overlap));  
			// it->overlap = std::max(it->overlap, overlap);
		} else {
			if (it2->overlap < overlap) {
				it2->overlap = overlap;        
			}    
		}

		for (auto vID : graph_edge[idx[from]].node) {
			
			
			auto& inner = insert[vID];          // 若 id1 不存在：自动创建一个空 map
			auto& cur   = inner[to];           // 若 id2 不存在：自动插入并默认值 0
			cur = std::max(cur, overlap);
			// cout << "try insert vID = " << vertex_id[vID] << " with overlap value " << cur << "\n";
			// if (vertex_id[vID] == 303 && idx[to] == 5 && cur == 2) {
			// 	while (true){}
			// }
			// if (cur == 17) {
			// 	while (true) {}
			// }
		}
	}
	// cout << "inserting nodes\n";
	for (auto it = insert.begin(); it != insert.end(); ++it) {
		
		auto vID = it->first;
		// cout << "trying to insert for node " << vertex_id[vID] << "\n";
		const auto& inner = it->second;
		auto label_it = label[vID].begin();
		for (auto it2 = inner.begin(); it2 != inner.end(); ++it2) {

			int id2 = it2->first;
			int value = it2->second;
			
			// cout << "inserting " << "(" << idx[id2] << ", " << value << ")\n";
			auto it3 = std::lower_bound(
				label[vID].begin(), label[vID].end(), id2,
				[](const Pair& p, int id){ return p.hID < id; }
			);

			if (it3 != label[vID].end()) {
				// cout << "continue inserting\n";
				if (it3->hID ==  id2) {
					// cout << "insert for vID = " << vertex_id[vID] << " with Pair(" << id2 << ", " << value << ") while ID matched\n";
					it3->overlap = max(it3->overlap, value);
				} else {
					// cout << "insert for vID = " << vertex_id[vID] << " with Pair(" << id2 << ", " << value << ") while ID not match\n";
					label[vID].insert(it3, Pair(id2, value));
				}
				// it->overlap = std::max(it->overlap, overlap);
			} else {
				// cout << "insert for vID = " << vertex_id[vID] << " with Pair(" << id2 << ", " << value << ") while reach the end\n";
				label[vID].insert(it3, Pair(id2, value));       
			}
		}
	
		
	}

	


	/*
	map<int, int> oneHop;
	for (auto currV : graph_edge[selected_edge].node) {
		for (auto currE: E[currV]) {
			
			if (oneHop.currE != oneHop.end()) {
				oneHop[currE]++;
			} else {
				oneHop.insert(make_pair(currE, 1));
			}
		}
	}


	for (auto it = oneHop.begin(); it != oneHop.end(); ++it) {
		for (auto it1 = ete_label[order[it->first]].begin(); it1 != ete_label[order[it->first]].end(); ++it1) {
			mayUpdate[it1->hID]
		} 
	}


	for (auto eid = 0; eid < needIncrement.size(); ++eid) {
		if (needIncrement[eid] == 1) {
			important[eid]++;
			// 做u的D(u) Le(u)的更新操作
			
			triplets.push_back(make_pair(selected_edge, Pair(eid, important[eid])));
		}
	}

	


	// 下一步， traverse 所有 更新的 1-hop nbr 的ete_label， 将其与important的交集做更新

	for (auto eid : cand) {
		if (eid == selected_edge) continue;
		for (auto it = ete_label[eid].begin(); it != ete_label[eid].end(); ++it) {
			if (important[it->hID] > it->overlap) {
				triplets.push_back(make_pair(eid, Pair(it->hID, max(it->overlap, important[it->hID]))));
				it->overlap = important[it->hID];
			}
		}

	}


    
    std::vector<std::pair<int,int>> oneHopNbr;
    oneHopNbr.reserve(cand.size());
	{
        BlockTimer t(prof.build_onehop);

        for (int eid : cand) {
            if (eid == selected_edge) continue;
            int ov = cnt[eid];
            if (ov > 0) oneHopNbr.emplace_back(eid, ov);
        }
    }

	{
        BlockTimer t(prof.pq_loop);

        while (!pq.empty()) {
            Pair_in_queue pair = pq.top(); pq.pop();
            int h = pair.hID;
            int overlap = pair.overlap;
			// if (visited_h[h]) continue;
			visited_h[h] = overlap;
			
			{
				BlockTimer ete_check_time(prof.ete_check);
				if (ete_reach(selected_edge, h, 0) >= overlap) continue;
			}

            triplets.push_back(std::make_pair(selected_edge, Pair(h, overlap)));

			{	
				BlockTimer t2(prof.update_ete_label);
			}

            {
                BlockTimer t3(prof.expand_nbrs);

                map<int, int> nbrs;
                for (int v : graph_edge[h].node) {
                    for (int eid : E[v]) {
                        if (eid <= selected_edge) continue;
                        auto itn = nbrs.find(eid);
                        if (itn != nbrs.end()) itn->second++;
                        else nbrs.insert(std::make_pair(eid, 1));
                    }
                }
                for (auto &p : nbrs) {
                    if (p.second < overlap || visited_h[p.first]) continue;
					if (visited_h[p.first] >= overlap) continue;
                    visited_h[p.first] = overlap;
                    pq.push(Pair_in_queue(p.first, overlap));
                }
            }
        }
    }
	*/

	/*


    // [Block 5] build oneHopNbr
    {
        BlockTimer t(prof.build_onehop);

        for (int eid : cand) {
            if (eid == selected_edge) continue;
            int ov = cnt[eid];
            if (ov > 0) oneHopNbr.emplace_back(eid, ov);
        }
    }

    // [Block 6] pref_max
    std::vector<int> pref_max;
    {
        BlockTimer t(prof.prefmax);

        pref_max.resize(ete_label[selected_edge].size());
        int max_cover_ov = std::numeric_limits<int>::min();
        for (size_t i = 0; i < ete_label[selected_edge].size(); ++i) {
            max_cover_ov = std::max(max_cover_ov, ete_label[selected_edge][i].overlap);
            pref_max[i] = max_cover_ov;
        }
    }

    // 初始入 pq（也可以计时，随你）
    for (int eid : cand) {
        if (eid == selected_edge || cnt[eid] == 0) continue;
		if (ete_reach(eid, selected_edge, 0) >= cnt[eid]) continue;
        pq.push(Pair_in_queue(eid, cnt[eid]));
        visited_h[eid] = cnt[eid];
    }
    visited[selected_edge] = 1;

    // [Block 7] pq loop（整体）
    {
        BlockTimer t(prof.pq_loop);

        while (!pq.empty()) {
            Pair_in_queue pair = pq.top(); pq.pop();
            int h = pair.hID;
            int overlap = pair.overlap;
			// if (visited_h[h]) continue;
			visited_h[h] = overlap;
			
			{
				BlockTimer ete_check_time(prof.ete_check);
				if (ete_reach(selected_edge, h, 0) >= overlap) continue;
			}

            triplets.push_back(std::make_pair(selected_edge, Pair(h, overlap)));

			{	
				BlockTimer t2(prof.update_ete_label);
				if (h < selected_edge) {

					auto it2 = ete_label[selected_edge].begin();
					auto max_ov = overlap - 1;

					while (it2 != ete_label[selected_edge].end() && it2->hID < h) {
						if (it2->overlap > max_ov) {
							max_ov = it2->overlap;
							triplets.push_back(std::make_pair(h, Pair(it2->hID, overlap)));  
						}
						++it2;
					}

					if (max_ov < overlap) {
						if (it2 == ete_label[selected_edge].end() || it2->hID > h)
							ete_label[selected_edge].insert(it2, Pair(h, overlap));
						else
							it2->overlap = overlap;
					}
				}
			}

            {
                BlockTimer t3(prof.expand_nbrs);

                map<int, int> nbrs;
                for (int v : graph_edge[h].node) {
                    for (int eid : E[v]) {
                        // if (visited_h[eid]) continue;
                        auto itn = nbrs.find(eid);
                        if (itn != nbrs.end()) itn->second++;
                        else nbrs.insert(std::make_pair(eid, 1));
                    }
                }
                for (auto &p : nbrs) {
                    if (p.second < overlap || visited_h[p.first]) continue;
					if (visited_h[p.first] >= overlap) continue;
                    visited_h[p.first] = overlap;
                    pq.push(Pair_in_queue(p.first, overlap));
                }
            }
        }
    }
	*/
    return true;
}



	/*
	auto it = std::lower_bound(graph_edge[selected_edge].node.begin(), graph_edge[selected_edge].node.end(), (*vertex_map)[inserted_node]);
	if (it != graph_edge[selected_edge].node.end() && *it == (*vertex_map)[inserted_node]) return false;


	// ofstream myfile("log.txt", std::ios::app);
  	
	// myfile << "======================================\n";
	// myfile << "try insert with original id = " << inserted_node << "to edge " << selected_edge << "\n";
	// myfile << "by using compacting current node map to " << (*vertex_map)[inserted_node] << ", and should map to " <<  (*old_vertex_map)[inserted_node] <<"\n";
	// myfile << "currently E[" <<  (*old_vertex_map)[inserted_node] << "] is ";
	// for (auto v : E[(*old_vertex_map)[inserted_node]]) {
	// 	myfile << v << " ";
	// }
	// myfile << "\n";
	// myfile << "V[" << selected_edge << "]: ";
	// for (auto e : graph_edge[selected_edge].node) {
	// 	myfile << e << " ";
	// }
	// myfile << "\n";

	

	// myfile << "it inserted successfully\n";
	
	fill(visited_h, visited_h + m + 1, 0);
	if (E[(*vertex_map)[inserted_node]].size() == 1) {
		label[(*old_vertex_map)[inserted_node]] = label[(*vertex_map)[inserted_node]];
		(*vertex_map)[inserted_node] = (*old_vertex_map)[inserted_node];
	}
	
	inserted_node = (*vertex_map)[inserted_node];
	auto original_size = graph_edge[selected_edge].length;
	
	graph_edge[selected_edge].node.insert(it, inserted_node);
	it = std::lower_bound(E[inserted_node].begin(), E[inserted_node].end(), selected_edge);
	E[inserted_node].insert(it, selected_edge);
	
	const auto& cand = E[inserted_node];
	std::vector<unsigned char> isCand(m + 1, 0);
	for (int eid : cand) isCand[eid] = 1;
	isCand[selected_edge] = 0;
	std::vector<int> cnt(m + 1, 0);
    for (int v : graph_edge[selected_edge].node) {
        for (int eid : E[v]) {
            if (isCand[eid]) ++cnt[eid];
        }
    }

	vector<pair<int,Pair>> triplets;

	std::vector<std::pair<int,int>> oneHopNbr;
	oneHopNbr.reserve(cand.size());
	priority_queue<Pair_in_queue> pq;
	for (int eid : cand) {
		if (eid == selected_edge) continue; 
		int ov = cnt[eid];                
		if (ov > 0) {
			oneHopNbr.emplace_back(eid, ov);
			
		}
	}
	cout << "1\n";


	// pq 基于重叠度， 若找到O(e_w) < O(selected_Edge) 且无法被cover， 则更新ete_label[selected_edge]
	bool maxIsFind = false;
	vector<int> pref_max;
	pref_max.resize(ete_label[selected_edge].size());
	int max_cover_ov = std::numeric_limits<int>::min();
	for (size_t i = 0; i < ete_label[selected_edge].size(); ++i) {
        max_cover_ov = std::max(max_cover_ov, ete_label[selected_edge][i].overlap);
        pref_max[i] = max_cover_ov;
    }

	for (int eid : cand) {
		if (eid == selected_edge || cnt[eid] == 0) continue; 
		pq.push(Pair_in_queue(eid, cnt[eid]));
		visited_h[eid] = cnt[eid];
		// if (eid >= selected_edge) break; // 这里只考虑更重要超边， 其他的下一个循环考虑
	}
	visited[selected_edge] = 1;
	cout << "2\n";
	while (!pq.empty()) {
		Pair_in_queue pair = pq.top();
		pq.pop();
		
		int h = pair.hID;
		int overlap = pair.overlap;
		
		if (ete_reach(selected_edge, h, 0) >= overlap) continue;
		triplets.push_back(make_pair(selected_edge, Pair(h, overlap)));
		if (h < selected_edge) {


			auto it = ete_label[selected_edge].begin();
			auto max_ov = overlap - 1;
			
			while (it != ete_label[selected_edge].end() && it->hID < h) {
				if (it->overlap >= overlap) {
					max_ov = it->overlap;
					triplets.push_back(make_pair(h, Pair(it->hID, overlap)));
				}
				++it;
			}

			if (max_ov < overlap) {
				if (it == ete_label[selected_edge].end() || (*it).hID > h) {
					ete_label[selected_edge].insert(it, Pair(h, overlap));
				} else {
					it->overlap = overlap;
				}
			}

			
			// auto it = std::lower_bound(
			// 	ete_label[selected_edge].begin(), ete_label[selected_edge].end(), h,
			// 	[](const Pair& p, int key) { return p.hID < key; }
			// );

			// if (it != ete_label[selected_edge].end() && it->hID == h) {
			// 	// 已存在：更新
			// 	it->overlap = overlap;
			// } else {
			// 	// 不存在：插入到正确位置，保持有序

			// 	//TODO 这里应该是 如果存在ew < selected_edge 且 ew->selected_edge >= overlap, 则不连h和selected_edge， 连h 和ew
			// 	ete_label[selected_edge].insert(it, Pair(h, overlap));
			// }
			
		}

		// cout << "3\n";
		map<int, int> nbrs;
		for (int v : graph_edge[h].node) {
			for (int eid : E[v]) {
				if (visited_h[eid]) continue;
				if (nbrs.find(eid) != nbrs.end()) {
					nbrs[eid]++;
				} else {
					nbrs.insert(make_pair(eid, 1));
				}
			}
		}
		for (auto p : nbrs) {
			if (p.second < overlap || visited_h[p.first]) continue;
			visited_h[h] = overlap;
			pq.push(Pair_in_queue(p.first, overlap));
		}
	}

	//


	/* 这块是使用1hop nbr的 
	std::sort(oneHopNbr.begin(), oneHopNbr.end(),
          [](const auto& a, const auto& b) {
              if (a.second != b.second) return a.second > b.second; 
              return a.first < b.first; 
          });

	auto it2 = std::lower_bound(
		ete_label[selected_edge].begin(), ete_label[selected_edge].end(), selected_edge,
		[](const Pair& p, int id){ return p.hID < id; }
	);

	if (it2 != ete_label[selected_edge].end() && it2->hID == selected_edge) {
        it2->overlap = original_size + 1;          
        // it->overlap = std::max(it->overlap, overlap);
    } else {
        ete_label[selected_edge].insert(it2, Pair(selected_edge, original_size + 1));       
    }
	



	// std::unordered_map<int, int> cnt;
	// size_t hint = 0;
	// for (int v : graph_edge[selected_edge].node) {
	// 	hint += E[v].size();
	// }
	// cnt.reserve(0.5 * hint);
	// for (it = graph_edge[selected_edge].node.begin(); it != graph_edge[selected_edge].node.end(); ++it) {
	// 	for (auto eid : E[*it]) {
	// 		++cnt[eid];
	// 	}
	// }
	// for (it = E[inserted_node].begin(); it != E[inserted_node].end(); ++it) {
	// 	for (auto it1 = graph_edge[*it].node.begin(); it1 != graph_edge[*it].node.end(); ++it1) {

	// 	}	
	// }
	
	
	return true;
	*/
// }





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
	cout << "query for src " << vertex_id[src] << " mapped to " << vertex_id[(*vertex_map)[vertex_id[src]]] << "\n";
	cout << "query for dst " << vertex_id[dst] << " mapped to " << vertex_id[(*vertex_map)[vertex_id[dst]]] << "\n";
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];		
	} else {
		src = (*vertex_map)[vertex_id[src]];
		dst = (*vertex_map)[vertex_id[dst]];
	}
	
	// cout << "label[u] = ";
	// for (auto it = label[src].begin(); it != label[src].end(); ++it) {
	// 	cout << "(" << idx[it->hID] << "{" << it->hID << "}" << ", " << it->overlap << "),";
	// }
	// cout << "\n";
	// cout << "label[v] = ";
	// for (auto it = label[dst].begin(); it != label[dst].end(); ++it) {
	// 	cout << "(" << idx[it->hID] << "{" << it->hID << "}" << ", " << it->overlap << "),";
	// }
	// cout << "\n";

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

	// cout << "for edge 1 with size = " << graph_edge[1].length << ": [";
	// for (auto v : graph_edge[1].node) {
	// 	cout << vertex_id[v] << " ";
	// }
	// cout << "]\n";
	// cout << "for edge 7 with size = " << graph_edge[7].length << ": [";
	// for (auto v : graph_edge[7].node) {
	// 	cout << vertex_id[v] << " ";
	// }
	// cout << "]\n";
	// cout << "for edge 8 with size = " << graph_edge[8].length << ": []";
	// for (auto v : graph_edge[8].node) {
	// 	cout << idx[v] << " ";
	// }
	// cout << "]\n";

	// for (auto i = 0; i <=m; i++) {
	// 	cout << "for edge " << i << ": [";
	// 	for (auto v : graph_edge[i].node) {
	// 		cout << vertex_id[v] << ", ";
	// 	}
	// 	cout << "]\n";
	// }

	auto start_time = std::chrono::high_resolution_clock::now();
	// cout << "query for original id = " << vertex_id[src] << ", " << vertex_id[dst] << "\n";
	if (original_id)
	{
		src = (*vertex_map)[src];
		dst = (*vertex_map)[dst];
	}
	
	// while (true){}

	vector<int> in_visit, out_visit;
	for (auto i = 0; i <= m; i++) {
		in_visit.push_back(0);
		out_visit.push_back(0);
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
				
				auto end = std::chrono::high_resolution_clock::now();
				auto time_spent = std::chrono::duration_cast<std::chrono::seconds>(end - start_time);
				if (time_spent.count() > 100) return result;
				auto pair = Q_in.top();
				auto h = pair.hID;
				auto o = pair.overlap;
				
				// if (o >= 2) cout << "from dst: get h = " << h << ", o = " << o << "\n";
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
					// if (min(it->second, o) >= 2) {
					// 	cout << "from " << h << " reaches " << it->first << " with " << min(it->second, o) << "\n";
					// }
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
				auto end = std::chrono::high_resolution_clock::now();
				auto time_spent = std::chrono::duration_cast<std::chrono::seconds>(end - start_time);
				if (time_spent.count() > 100) return result;
				auto pair = Q_out.top();
				auto h = pair.hID;
				auto o = pair.overlap;
				// if (o >= 2) cout << "from src: get h = " << h << ", o = " << o << "\n";
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
					// if (min(it->second, o) >= 2) {
					// 	cout << "from " << h << " reaches " << it->first << " with " << min(it->second, o) << "\n";
					// }
					Q_out.push(Pair_in_queue(it->first, min(it->second, o)));
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
					Q_out.push(Pair_in_queue(it->first, min(it->second, o)));
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
	Q_in.push(Pair_in_queue(src, graph_edge[idx[src]].length));
	Q_out.push(Pair_in_queue(dst, graph_edge[idx[dst]].length));
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
					Q_out.push(Pair_in_queue(it->first, min(it->second, o)));
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
					Q_in.push(Pair_in_queue(it->first, min(it->second, o)));
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
					Q_out.push(Pair_in_queue(it->first, min(it->second, o)));
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

void SL::print_prof(std::ostream& os) {
    os << "avg total(ns)      = " << prof.total.avg_ns() << "\n";
    os << "avg check_exist    = " << prof.check_exist.avg_ns() << "\n";
    os << "avg init_and_remap = " << prof.init_and_remap.avg_ns() << "\n";
    os << "avg update_struct  = " << prof.update_struct.avg_ns() << "\n";
    os << "avg build_cnt      = " << prof.build_cnt.avg_ns() << "\n";
    os << "avg build_onehop   = " << prof.build_onehop.avg_ns() << "\n";
    os << "avg prefmax        = " << prof.prefmax.avg_ns() << "\n";
    os << "avg pq_loop        = " << prof.pq_loop.avg_ns() << "\n";
	os << "avg ete_check        = " << prof.ete_check.avg_ns() << "\n";
    os << "avg update_ete_lbl = " << prof.update_ete_label.avg_ns() << "\n";
    os << "avg expand_nbrs    = " << prof.expand_nbrs.avg_ns() << "\n";
}