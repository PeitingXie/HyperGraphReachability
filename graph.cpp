#include "graph.h"


Graph::Graph(char *graph_file, bool _directed)
{
	max_v = 10000000;
	max_e = 100000000;
	
	n = 0;
	m = 0;

	directed = _directed;
	


    graph_head = new HyperEdge* [max_e + 1];
	graph_edge = new HyperEdge [max_e + 1];

    //E = new int* [max_v + 1];
   
    //memset(E, 0, sizeof(*E) * (max_v + 1));

    cout << "here\n";
	memset(graph_head, 0, sizeof(*graph_head) * (max_e + 1));
	

	d_in = new int [max_v + 1];
	memset(d_in, 0, sizeof(*d_in) * (max_v + 1));
		
	

	vertex_id = new int [max_v + 1];

	int u, v;
	int sign;
	
	ifstream fin(graph_file);
    string line;
    
    while (getline(fin, line)) {
        // 使用 stringstream 将一行数据按空格分割
        istringstream iss(line);
        string word;
        vector<int> tokens;

        while (iss >> word) {
            int v = get_vertex_id(stoi(word));
            tokens.push_back(v);
            
        }

        // 打印分割后的数据
        insert_edge(tokens);

        for (auto token : tokens) {
            std::cout << token << " ";
        }

        std::cout << std::endl;
    }
	
	for (int i = 1; i <= m; i++) {
		map<int, int> m;
		for (auto v : graph_edge[i].node) {
			for (auto h : E[v]) {
				if (h <= i) continue;
				if (m.find(h) != m.end()) {
					m[h]++;
				} else {
					m.insert(make_pair(h, 1));
				}
			}
		}

		for (auto pair : m) {
			neighbour[pair.first].push_back(make_pair(i, pair.second));
			neighbour[i].push_back(make_pair(pair.first, pair.second));
		}
	}


    

	fin.close();
}


Graph::~Graph()
{
	if (graph_head) delete[] graph_head;
	if (graph_edge) delete[] graph_edge;
	if (d_in) delete[] d_in;
	if (vertex_id) delete[] vertex_id;

	if (directed)
	{
		if (d_out) delete[] d_out;
	}
}




void Graph::insert_edge(vector<int> nodes)
{
	m++;
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
