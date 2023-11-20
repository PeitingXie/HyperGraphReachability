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
	
	SL * alg = new SL(graph);

	
	cout << "graph init complete\n";

	alg -> construct();
	
	cout << "construct complete\n";
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
	

	
	// for (int i = 1; i <= graph->n; i++) {
	// 	for (int j = 1; j <= graph->n; j++) {
			
			
	// 	}
	// }
	



	// for (auto i = 1; i <= graph->n; i++) {
	// 	for (auto j = 1; j <= graph->n; j++) {
	// 		for (auto k = 1; k <= 6; k++) {
	// 			cout << "check " << i << ", " << j << ", " << k << "\n";
	// 			auto res1 = alg->baseLine(i,j,k, 1);
	// 			auto res2 = alg->span_reach(i,j,k, 1);
	// 			if (res1 != res2) {
	// 				cout << "failed, baseline is " << res1 << ", span reach is " << res2 << "\n" ;
	// 				return 0;
	// 			}
				
	// 		}
	// 	}
	// }
	srand (time(NULL));




	// int reach = 0;
	// int total = 0;
	// for (auto overlap = 0; overlap < min(graph->max_size,5); overlap++) {
	// 	total++;
	// 	int k;

	// 	if (overlap == 0) {
	// 		k = rand() % 6 + 1;

	// 	} else {
	// 		k = overlap;

	// 	}


	
		
		// int count = 0;
		// int reach = 0;

		// while (count < 100000) {
			
		// 	// int i = rand() % graph->n + 1;
		// 	// int j = rand() % graph->n + 1;
		// 	// int k = rand() % graph->max_size + 1;
		// 	int i = 14838986;
		// 	int j = 3862771;
		// 	int k = 1;
		// 	string currk;
		// 	// if (overlap != 0) {
		// 	// 	currk = to_string(k);
		// 	// } else {
		// 	// 	currk = "random";
		// 	// }
		// 	cout << "test " << count << " with " << i << ", " << j << ", " << k << "\n";
			
		// 	auto res1 = alg->baseLine(i,j,k, 1);
		// 	// auto res1 = alg->baseline(246, 717, 125, 1);
		// 	cout << "baseline finished\n";

		// 	auto res2 = alg->span_reach(i,j,k, 1);
		// 	// auto res2 = alg->span_reach(246, 717, 125, 1);
		


		// 	if (res1 != res2) {
		// 		cout << "failed, baseline is " << res1 << ", span reach is " << res2 << "\n" ;
		// 		return 0;
		// 	}
		// 	if (res1 == true) reach++;
		// 	// break;
		// 	count++;
			
		// }
	//}
		
	





	
	
	
	std::string fullPath = argv[1];
	size_t lastSlashPos = fullPath.find_last_of('/');
    size_t dotPos = fullPath.find_last_of('.');
    std::string folderName;
    if (lastSlashPos != std::string::npos) {
        if (dotPos != std::string::npos && dotPos > lastSlashPos) {
            folderName = fullPath.substr(lastSlashPos + 1, dotPos - lastSlashPos - 1);
		}   
    }

	

	if (!std::filesystem::exists("test_result/" + folderName)) {
        try {
            std::filesystem::create_directory("test_result/" + folderName);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误: " << e.what() << std::endl;
        }
    }

	string baseOutput = "test_result/" + folderName + "/basetime";
	string twoHopOutput = "test_result/" + folderName + "/spanReachTime";

	cout << "max size is " << graph->max_size << "\n";

	
	for (auto overlap = 0; overlap < 6; overlap++) {
		int reach = 0;
		int total = 0;
		int k;
		string currBaseOutFile;
		string currTwoHopOutFile; 
		
		if (overlap == 0) {
			k = rand() % 5 + 1;
			currBaseOutFile = baseOutput + "Rand.txt";
			currTwoHopOutFile = twoHopOutput + "Rand.txt";
		} else {
			k = overlap;
			currBaseOutFile = baseOutput + to_string(k) + ".txt";
			currTwoHopOutFile = twoHopOutput + to_string(k) + ".txt";
		}

		std::ofstream outputFile(currBaseOutFile, std::ios::trunc);
		outputFile.close();

		std::ofstream outputFile2(currTwoHopOutFile, std::ios::trunc);
		outputFile2.close();


		int count = 0;


		// for (int i = 1; i < graph->n; i++) {
		// 	for (int j = 1; j < graph->n; j++) {
		// 		string currk;
		// 		if (overlap != 0) {
		// 			currk = to_string(k);
		// 		} else {
		// 			currk = "random";
		// 		}
		// 		cout << "test " << count << " with " << i << ", " << j << ", " << currk << "\n";
				
		// 		auto start_time = std::chrono::high_resolution_clock::now();
				
		// 		auto res1 = alg->baseLine(i,j,k, 1);
		// 		cout << "baseline finished\n";
		// 		auto end_time = std::chrono::high_resolution_clock::now();
		// 		auto elapsed_time_base = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		// 		// auto elapsed_time_base = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);


		// 		std::ofstream myfile(currBaseOutFile, std::ios::app);
				
		// 		myfile << elapsed_time_base.count() << "\n";
		// 		myfile.close();
				
				
		// 		start_time = std::chrono::high_resolution_clock::now();
		// 		auto res2 = alg->span_reach(i,j,k, 1);
		// 		end_time = std::chrono::high_resolution_clock::now();
		// 		auto elapsed_time_span = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		// 		// auto elapsed_time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

		// 		std::ofstream myfile2(currTwoHopOutFile, std::ios::app);
				
		// 		myfile2 << elapsed_time_span.count() << "\n";
		// 		myfile2.close();


		// 		if (res1 != res2) {
		// 			cout << "failed, baseline is " << res1 << ", span reach is " << res2 << "\n" ;
		// 			return 0;
		// 		}
		// 	}
		// }

		string currk;
		if (overlap != 0) {
			currk = to_string(k);
		} else {
			currk = "random";
		}

		while (count < 10000) {
			total++;
			int i = rand() % graph->n + 1;
			int j = rand() % graph->n + 1;
			
			
			


			cout << "test " << count << " with " << i << ", " << j << ", " << currk << "\n";
			
			auto start_time = std::chrono::high_resolution_clock::now();
			
			auto res1 = alg->baseLine(i,j,k, 1);
			cout << "baseline finished\n";
			auto end_time = std::chrono::high_resolution_clock::now();
			auto elapsed_time_base = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			// auto elapsed_time_base = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);


			std::ofstream myfile(currBaseOutFile, std::ios::app);
			
			myfile << elapsed_time_base.count() << "\n";
			myfile.close();
			
			
			start_time = std::chrono::high_resolution_clock::now();
			auto res2 = alg->span_reach(i,j,k, 1);
			end_time = std::chrono::high_resolution_clock::now();
			auto elapsed_time_span = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			// auto elapsed_time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

			std::ofstream myfile2(currTwoHopOutFile, std::ios::app);
			
			myfile2 << elapsed_time_span.count() << "\n";
			myfile2.close();


			if (res1 != res2) {
				cout << "failed, baseline is " << res1 << ", span reach is " << res2 << "\n" ;
				return 0;
			}
			if (res1 == true) reach++;
			count++;
			
		}
		string rate = "test_result/" + folderName + "/rate.txt";
		 std::ofstream file3(rate, std::ios::app);

		file3 << "test for " << argv[1] << ", k = " << currk <<" is finished\n";	
		file3 << "total test case = " << total << ", true case = " << reach << "\n"; 
	}
	
	



	




    // cout << "baseline query result is " << alg->baseLine(i,j,k, 1) << "\n";
	// cout << "label query result is " << alg->span_reach(i,j,k, 1) << "\n";
	fin.close();
	fout.close();
	


	// for (auto i = 1; i <= 8; i++) {
	// 	for (auto j = 1; j <= 8; j++) {
	// 		for (auto k = 1; k <= graph->max_size; k++) {
	// 			cout << "check " << i << ", " << j << ", " << k << "\n";
	// 			auto res1 = alg->baseLine(i,j,k, 1);
	// 			auto res2 = alg->span_reach(i,j,k, 1);
	// 			if (res1 != res2) {
	// 				cout << "failed, baseline is " << res1 << ", span reach is " << res2 << "\n" ;
	// 				return 0;
	// 			}
				
	// 		}
	// 	}
	// }

	// auto res1 = alg->baseLine(1,4,1, 1);
	// auto res2 = alg->span_reach(1,4,1, 1);
	
	// if (res1 != res2) {
	// 	cout << "failed, baseline is " << res1 << ", span reach is " << res2 << "with k = " << 1 <<"\n" ;
	// 	return 0;
	// }

	cout << "================================PASS================================\n";
	//
		//fout << "Hello world\n";



	// for (int i = 1; i <= 10; i++) {
		
	// 	auto res1 = alg->baseLine(1134,1135,i, 1);
	// 	auto res2 = alg->span_reach(1134,1135,i, 1);
		
	// 	if (res1 != res2) {
	// 		cout << "failed, baseline is " << res1 << ", span reach is " << res2 << "with k = " << i <<"\n" ;
	// 		return 0;
	// 	}
	
	// }



	return 0;
}
