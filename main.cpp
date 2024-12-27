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
	double scale = stod(argv[5]);

	int t_value = stoi(argv[6]);
	string folder = "scale";
	string dictName = argv[1];
	dictName.erase(dictName.size() - 4);
	dictName.erase(0, 5);
	cout << "dict path is " << dictName << "\n";

	string dictPath = folder + "/" + dictName;

	
	
	string filePath = dictPath + "/" + "scale.txt";


	if (!std::filesystem::exists(dictPath)) {
        try {
            std::filesystem::create_directory(dictPath);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误1: " << e.what() << std::endl;
        }
    }
	if (!std::filesystem::exists(dictPath + "/query_time")) {
        try {
            std::filesystem::create_directory(dictPath + "/query_time");
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误1: " << e.what() << std::endl;
        }
    }

	if (!std::filesystem::exists(dictPath + "/query_time/" + to_string(static_cast<int>(scale * 100)))) {
        try {
            std::filesystem::create_directory(dictPath + "/query_time/" + to_string(static_cast<int>(scale * 100)));
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误1: " << e.what() << std::endl;
        }
    }

	if (scale == 0.2) {
		std::ofstream file(filePath, std::ofstream::trunc);
	}
	
	std::ofstream file(filePath, std::ofstream::app);

	if (!file.is_open()) {
		std::cerr << "无法打开文件: " << filePath << std::endl;
		return -1;
	}

	file << "current scale = " << argv[5] << "\n";
	file.close();

	srand (time(NULL));

	Graph * graph = new Graph(argv[1], directed, scale);
	
	if (!std::filesystem::exists(dictPath + "/query.txt")) {
        std::ofstream query_gen(dictPath + "/query.txt", std::ofstream::trunc);
		for (auto i = 0; i < 100000; i++) {
			int u = rand() % graph->n + 1;
			int v = rand() % graph->n + 1;
			query_gen << u << " " << v << "\n";
		}
    }
	// exit(1);

	SL * alg = new SL(graph);

	
	cout << "graph init complete\n";
	
	vector<vector<int>> hot;
	vector<int> centrality;
	vector<int> threshold;
	double level = 0.2;
	int count = 0;
	double val = level + count * 0.2;
	
	for (auto i = 1; i <= graph->n; i++) {
		centrality.push_back(graph->E[i].size());
	}
	sort(centrality.begin(), centrality.end());
	// int pivot = graph->n * 0.8;
	
	while (val < 1) {
		threshold.push_back(centrality[graph->n * val]);
		count += 1;
		val = level + count * 0.2;
		hot.push_back(vector<int>());
		// cout << "val is " << val << "\n";
	}
	// cout << "here\n";
	// int threshold1 = centrality[pivot];
	// int threshold2 = centrality[graph->n * 0.83];
	// int threshold2 = centrality[graph->n * 0.86];
	// int threshold2 = centrality[graph->n * 0.89];
	// int threshold2 = centrality[graph->n * 0.92];
	// int threshold2 = centrality[graph->n * 0.95];
	// int threshold2 = centrality[graph->n * 0.98];
	// cout << "pivot is " << threshold << "\n";
	// while (true) {

	// }

	for (auto i = 1; i <= graph->n; i++) {
		for (auto j = 0; j < threshold.size(); j++) {
			if (graph->E[i].size() >= threshold[j] ) {
				hot[j].push_back(graph->vertex_id[i]);
			}
		}
	}
	
	cout << "size = " << count << "\n";
	// while (true) {
		
	// }


	
	alg -> construct(filePath);
	return 0;
	cout << "construct complete\n";
	// return 0;
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

	

	if (!std::filesystem::exists("ete_test_result/" + folderName)) {
        try {
            std::filesystem::create_directory("ete_test_result/" + folderName);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误: " << e.what() << std::endl;
        }
    }


	if (!std::filesystem::exists("threshold/" + to_string(t_value))) {
        try {
            std::filesystem::create_directory("threshold/" + to_string(t_value));
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误: " << e.what() << std::endl;
        }
    }


	if (!std::filesystem::exists("threshold/" + to_string(t_value) + "/" + folderName)) {
        try {
            std::filesystem::create_directory("threshold/" + to_string(t_value) + "/" + folderName);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误: " << e.what() << std::endl;
        }
    }
	

	cout << "max size is " << graph->max_size << "\n";

	// string baseOutput = "ete_test_result/" + folderName + "/basetime";
	// string base1Output = "ete_test_result/" + folderName + "/base1time";
	// string twoHopOutput = "ete_test_result/" + folderName + "/spanReachTime";
	// string eteOutput = "ete_test_result/" + folderName + "/eteTime";
	// "threshold/" + to_string(t_value) + "/" + folderName
	string baseOutput = "threshold/" + to_string(t_value) + "/" + folderName + "/basetime";
	string base1Output = "threshold/" + to_string(t_value) + "/" + folderName + "/base1time";
	string twoHopOutput = "threshold/" + to_string(t_value) + "/" + folderName + "/spanReachTime";
	string eteOutput = "threshold/" + to_string(t_value) + "/" + folderName + "/eteTime";
	// string baseOutput = dictPath + "/query_time/" + to_string(static_cast<int>(scale * 100)) + "/basetime";
	// string base1Output = dictPath + "/query_time/" + to_string(static_cast<int>(scale * 100)) + "/base1time";
	// string twoHopOutput = dictPath + "/query_time/" + to_string(static_cast<int>(scale * 100)) + "/spanReachTime";
	// string eteOutput = dictPath + "/query_time/" + to_string(static_cast<int>(scale * 100)) + "/eteTime";

	// std::ofstream testmr("record/" + folderName+".txt", std::ios::trunc);
	std::ofstream testmr("record/" + folderName+"min.txt", std::ios::trunc);



	for (auto overlap = 0; overlap < 1; overlap++) {
		int reach = 0;
		int total = 0;
		int k;
		string currBaseOutFile, currBaseNbrFile;
		string currTwoHopOutFile; 
		string currEteOutFile; 

		
		
		currBaseOutFile = baseOutput + to_string(overlap) + ".txt";
		currBaseNbrFile = base1Output + to_string(overlap) + ".txt";
		currTwoHopOutFile = twoHopOutput + to_string(overlap) + ".txt";
		currEteOutFile = eteOutput + to_string(overlap) + ".txt";

		// std::ofstream outputFile_nbr(currBaseNbrFile, std::ios::trunc);
		// outputFile_nbr.close();

		// std::ofstream outputFile(currBaseOutFile, std::ios::trunc);
		// outputFile.close();

		std::ofstream outputFile2(currTwoHopOutFile, std::ios::trunc);
		outputFile2.close();

		std::ofstream outputFile3(currEteOutFile, std::ios::trunc);
		outputFile3.close();

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

		
		


		std::ifstream input_query(dictPath + "/query.txt");
		string src, dst;
		while (input_query >> src >> dst) {
		// while (count < 1000) {
			total++;
			int i = stoi(src);
			int j = stoi(dst);
			// int i = rand() % graph->n + 1;
			// int j = rand() % graph->n + 1;
			// cout << "i = " << i << ", j = " << j << "\n";
			// int srcID = rand() % hot[overlap].size();
			// int dstID = rand() % hot[overlap].size();
			// int i = hot[overlap][srcID];
			// int j = hot[overlap][dstID];
			// i = rand() % graph->n + 1;
			// j = rand() % graph->n + 1;
			// i = 857;
			// j = 2636;
			// k = 4; 
			// i = 2;
			// j = 7;

			if (total == 500000) {
				// count ++;
				break;
				// continue;
			}
			cout << "test " << count << " with " << i << ", " << j << "\n";






			auto start_time = std::chrono::high_resolution_clock::now();
			

			// auto res1 = alg->threshold_baseLine(i,j, 1, t_value);
			// auto res1 = alg->baseLine(i,j, 1);
			// auto res1 = alg->ete_reach(i, j, 1);
			// auto res1 = alg->reach1(i,j, 1);
			auto res1 = 0;
			auto end_time = std::chrono::high_resolution_clock::now();
			// auto elapsed_time_base = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			auto elapsed_time_base = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			cout << "result is " << res1 << "\n";


			std::ofstream myfile(currBaseOutFile, std::ios::app);
			
			myfile << elapsed_time_base.count() << "\n";
			myfile.close();
			

			// start_time = std::chrono::high_resolution_clock::now();
			
			// auto res2 = alg->baseLine_with_nbr(i,j,1);
			//  end_time = std::chrono::high_resolution_clock::now();
			// auto elapsed_time_span = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			auto time_with_nbr = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

			std::ofstream myfile_nbr(currBaseNbrFile, std::ios::app);
			
			myfile_nbr << time_with_nbr.count() << "\n";
			myfile_nbr.close();





			
			start_time = std::chrono::high_resolution_clock::now();
			
			// auto res3 = alg->threshold_reach(i,j,1, t_value);
			auto res3 = alg->reach(i,j,1);
			 end_time = std::chrono::high_resolution_clock::now();
			// auto elapsed_time_span = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			auto elapsed_time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
			testmr << res3 << "\n";
			std::ofstream myfile2(currTwoHopOutFile, std::ios::app);
			
			myfile2 << elapsed_time_span.count() << "\n";
			myfile2.close();


			//    
			
			
			cout << "baseline finished\n";
			start_time = std::chrono::high_resolution_clock::now();
			// auto res4 = alg->threshold_ete_reach(i, j, 1, t_value);
			end_time = std::chrono::high_resolution_clock::now();
			elapsed_time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
			
			std::ofstream myfile3(currEteOutFile, std::ios::app);
			myfile3 << elapsed_time_span.count() << "\n";
			// cout << "ete time is " << elapsed_time_span.count() << "ns\n";
			myfile3.close();



			


			string rate = "ete_test_result/" + folderName + "/rate.txt";
			std::ofstream file4(rate, std::ios::app);
			// file4 << res4 << "\n";
			file4.close();

			
			// if (res1 != res3) {
			// 	cout << "failed, baseline is " << res1 << ", vte_reach is " << res3 << "\n" ;
			// 	return 0;
			// }
			if (res3 > 1) reach++;
			count++;
			
		}
		

		// file3 << "test for " << argv[1] << ", k = " << currk <<" is finished\n";	
		// file3 << "total test case = " << total << ", true case = " << reach << "\n"; 

		cout << "test for " << argv[1] << " is finished\n";	
		cout << "total test case = " << total << ", true case = " << reach << "\n"; 
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
