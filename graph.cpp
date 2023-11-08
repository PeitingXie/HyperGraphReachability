#include "graph.h"


Graph::Graph(char *graph_file, bool _directed)
{
	max_v = 20000000;
	max_e = 100000000;
	
	n = 0;
	m = 0;
	max_size = 0;
	directed = _directed;
	
	

	graph_edge = new HyperEdge [max_e + 1];

    //E = new int* [max_v + 1];
   
    //memset(E, 0, sizeof(*E) * (max_v + 1));

    // cout << "here\n";
	


		
	

	vertex_id = new int [max_v + 1];

	int u, v;
	int sign;
	
	ifstream fin(graph_file);
    string line;
    
	int num = 0;
	int count = 0;
    while (getline(fin, line)) {
        // 使用 stringstream 将一行数据按空格分割

        istringstream iss(line);
        string word;
        vector<int> tokens;

        while (iss >> word) {
            int v = get_vertex_id(stoi(word));
            tokens.push_back(v);
           
        }

		
		if (tokens.size() == 1) {
			num++;
			// continue;
		} 

		int currSize = tokens.size();
		max_size = max(max_size, currSize);

		if (count % 1000 == 0) {
			cout << "input for line " << count << "\n";
		}
		count++;
        insert_edge(tokens);

        // for (auto token : tokens) {
        //     std::cout << token << " ";
        // }

        // std::cout << std::endl;
    }
	cout << "data reading is finished\n";
	cout << "total usefule edge num is " << m << "\n";
	cout << "edge num where size = 1 is :" << num << "\n";
	cout << "total n = " << n << ", m" << num + m << "\n";
	
	fin.close();
	// double avg = 0;
	// for (auto i = 1; i <= m; i++) {
	// 	set<int> s;
	// 	for (auto v : graph_edge[i].node) {
	// 		for (auto k : E[v]) {
	// 			s.insert(k);
	// 		}
	// 	}
	// 	avg += s.size();
	// 	s.clear();
	// }

	// cout << "avg degree is " << avg / m << "\n";
	// while (true) {

	// }
}


Graph::~Graph()
{
	if (graph_edge) delete[] graph_edge;

	if (vertex_id) delete[] vertex_id;


}




void Graph::insert_edge(vector<int> nodes)
{
	m++;
	// if (m >578000) cout << nodes.size() <<"\n";
    for (auto v : nodes) {
        
		E[v].push_back(m);
		
        graph_edge[m].node.push_back(v);
	}
	
	graph_edge[m].length = nodes.size();

}





void Graph::delete_edge(int u, int v, int edge_id)
{
	
}


int Graph::get_vertex_id(int v)
{
	if (!vertex_map[v])
	{
		if (n < max_v)
		{
			vertex_map[v] = ++n;
			vertex_id[n] = v;
		}
		else
		{
			cout << "max_v is too small.\n";
			exit(0);
		}
	}
	return vertex_map[v];
}
