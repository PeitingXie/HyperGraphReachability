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
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> tokens;

        while (iss >> word) {
            tokens.push_back(word);
        }

        // 打印分割后的数据
        for (const std::string& token : tokens) {
            std::cout << token << " ";
        }

        std::cout << std::endl;
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




void Graph::insert_edge(int u, int v, int sign)
{
	
	
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
