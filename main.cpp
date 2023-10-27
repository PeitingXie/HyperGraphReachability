#include "HI.h"


int main(int argc, char *argv[])
{
	bool directed = false;
	if (string(argv[2]) == "D")
		directed = true;
	else if (string(argv[2]) != "U")
	{
		cout << "Parameter Error" << endl;
		return 0;
	}

	Graph * graph = new Graph(argv[1], directed);
	
	//SL * alg = new SL(graph);
	
	//alg -> construct();
	
	char* query_file = argv[3];
	char* output_file = argv[4];

    




	
	// if (!strcmp(argv[3], "insert"))
	// {
	// 	int u, v, ts;

	// 	ifstream fin;
	// 	fin.open(argv[4]);

	// 	int last_ts = -1;
	// 	(alg -> S).clear();

	// 	while (fin >> u >> v >> ts)
	// 	{
	// 		if (last_ts != -1 && ts != last_ts)
	// 		{
	// 			if ((alg -> S).size()) alg -> insert(last_ts);
	// 			(alg -> S).clear();
	// 		}

	// 		u = graph -> get_vertex_id(u);
	// 		v = graph -> get_vertex_id(v);
	// 		//cout << "Insert edge " << u << " " << v << " " << ts << "\n";
	// 		graph -> insert_edge(u, v, ts);
			
	// 		if (u != v) (alg -> S).push_back(Edge(u, v, ts));
	// 		last_ts = ts;
	// 	}

	// 	if (last_ts != -1 && (alg -> S).size()) alg -> insert(last_ts);

	// 	fin.close();
	// 	query_file = argv[5];
	// 	output_file = argv[6];
	// }
	// else if (!strcmp(argv[3], "delete"))
	// {
	// 	int u, v, ts;
	// 	int cnt = 0;

	// 	ifstream fin;
	// 	fin.open(argv[4]);

	// 	while (fin >> u >> v >> ts)
	// 	{
	// 		cnt++;
	// 		u = graph -> get_vertex_id(u);
	// 		v = graph -> get_vertex_id(v);
	// 		graph -> delete_edge(u, v, cnt);
	// 	}
	// 	alg -> erase(ts);

	// 	fin.close();
	// 	query_file = argv[5];
	// 	output_file = argv[6];
	// }

	
	ifstream fin(query_file);
	ofstream fout(output_file);

	int v, u, sign;
	int count = 0;
	// cout <<"get vertex size:\n";
	// for (int i = 1; i <= 12; i++) {
	// 	cout << graph -> get_vertex_id(i) << " ";
	// }
	// cout << "\n";

	//alg->estimate();
	/*
	cout << "new file-----------------------------------------\n";
	while (fin >> u >> v >> sign) {
		
		int res = alg -> span_reach(u, v, sign, true);
		if (res == 0) {
			fout << "False" << endl;
			//cout << "False" << "\n";
		} else {
			fout << "True" << endl;
			//cout << "True\n";
		}
		//cout << count++ <<"\n";
	}*/
	

	
	for (int i = 1; i <= graph->n; i++) {
		for (int j = 1; j <= graph->n; j++) {
			
			
		}
	}
	

	cout << "================================PASS================================\n";
	//
		//fout << "Hello world\n";
	fin.close();
	fout.close();
	
	return 0;
}
