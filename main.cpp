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


	string folder = "scale";
	string disFolder = "dis";
	string dictName = argv[1];
	dictName.erase(dictName.size() - 4);
	dictName.erase(0, 5);
	cout << "dict path is " << dictName << "\n";

	string dictPath = folder + "/" + dictName;
	string disPath = disFolder + "/" + dictName;
	
	string filePath = dictPath + "/" + "memory.txt";

	string disFilePath = disPath + "/" + "dis.txt";

	if (!std::filesystem::exists(dictPath)) {
        try {
            std::filesystem::create_directory(dictPath);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误1: " << e.what() << std::endl;
        }
    }

	if (!std::filesystem::exists(disFolder)) {
        try {
            std::filesystem::create_directory(disFolder);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误1: " << e.what() << std::endl;
        }
    }

	if (!std::filesystem::exists(disPath)) {
        try {
            std::filesystem::create_directory(disPath);
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


	Graph * graph = new Graph(argv[1], directed, scale);
	
	SL * alg = new SL(graph);

	
	cout << "graph init complete\n";

	vector<vector<int>> hot;
	vector<int> centrality;
	for (auto i = 1; i <= graph->n; i++) {
		centrality.push_back(graph->E[i].size());
	}
	sort(centrality.begin(), centrality.end());
	// int pivot = graph->n * 0.8;
	vector<int> threshold;
	double level = 0.2;
	int count = 0;
	double val = 0;
	while (val < 1) {
		threshold.push_back(centrality[graph->n * val]);
		count += 1;
		val = count * 0.2;
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
		for (auto j = threshold.size() -1; j >= 0; j--) {
			if (graph->E[i].size() >= threshold[j] ) {
				hot[j].push_back(i);
				break;
			}
		}
	}
	
	cout << "size = " << count << "\n";
	// while (true) {
		
	// }



	alg -> construct(filePath);
	
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

	srand (time(NULL));

	
	std::string fullPath = argv[1];
	size_t lastSlashPos = fullPath.find_last_of('/');
    size_t dotPos = fullPath.find_last_of('.');
    std::string folderName;
    if (lastSlashPos != std::string::npos) {
        if (dotPos != std::string::npos && dotPos > lastSlashPos) {
            folderName = fullPath.substr(lastSlashPos + 1, dotPos - lastSlashPos - 1);
		}   
    }

	string degDist = "result_BFS/";

	if (!std::filesystem::exists(degDist)) {
        try {
            std::filesystem::create_directory(degDist);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误: " << e.what() << std::endl;
        }
    }


	if (!std::filesystem::exists(degDist + folderName)) {
        try {
            std::filesystem::create_directory(degDist + folderName);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "创建文件夹时出现错误: " << e.what() << std::endl;
        }
    }

	

	cout << "max size is " << graph->max_size << "\n";


	
	

	string baseOutput = degDist + folderName + "/basetime";
	string twoHopOutput = degDist + folderName + "/spanReachTime";
	string eteOutput = degDist + folderName + "/eteTime";
	
	for (auto overlap = 0; overlap < 1; overlap++) {
		int reach = 0;
		int total = 0;
		int k;
		string currBaseOutFile;
		string currTwoHopOutFile; 
		string currEteOutFile; 

		
		
		currBaseOutFile = baseOutput + to_string(overlap) + ".txt";
		currTwoHopOutFile = twoHopOutput + to_string(overlap) + ".txt";
		currEteOutFile = eteOutput + to_string(overlap) + ".txt";
		std::ofstream outputFile(currBaseOutFile, std::ios::trunc);
		outputFile.close();

		std::ofstream outputFile2(currTwoHopOutFile, std::ios::trunc);
		outputFile2.close();

		std::ofstream outputFile3(currEteOutFile, std::ios::trunc);
		outputFile3.close();

		std::ofstream outputFile4(disFilePath, std::ios::trunc);
		outputFile4.close();
		
		int count = 0;


		
		while (count < 1000) {
			total++;
			
			int i = rand() % graph->n + 1;
			int j = rand() % graph->n + 1;
			// if (hot[overlap].size() == 0) {
			// 	count++;
			// 	continue;
			// }
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


			cout << "test " << count << " with " << i << ", " << j << " with threshold = " << centrality[graph->n * (level + overlap * 0.03)] <<"\n";
			

			auto start_time = std::chrono::high_resolution_clock::now();
			

			auto res1 = alg->baseLine(i,j, 1);
			// auto res1 = 0;
			auto end_time = std::chrono::high_resolution_clock::now();
			// auto elapsed_time_base = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			auto elapsed_time_base = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);


			std::ofstream myfile(currBaseOutFile, std::ios::app);
			
			myfile << elapsed_time_base.count() << "\n";
			myfile.close();
			
			start_time = std::chrono::high_resolution_clock::now();
			
			auto res2 = alg->reach(i,j,1);
			cout << "result is " << res2 << "\n";
			 end_time = std::chrono::high_resolution_clock::now();
			// auto elapsed_time_span = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			auto elapsed_time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

			std::ofstream myfile2(currTwoHopOutFile, std::ios::app);
			
			myfile2 << elapsed_time_span.count() << "\n";
			myfile2.close();

			std::ofstream file_dis(disFilePath, std::ios::app);
			file_dis << res2 << " " << elapsed_time_span.count() << "\n";
			file_dis.close();
			//    
			
			
			cout << "baseline finished\n";
			/*
			start_time = std::chrono::high_resolution_clock::now();
			auto res3 = alg->ete_reach(i, j, 1);
			end_time = std::chrono::high_resolution_clock::now();
			elapsed_time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
			
			std::ofstream myfile3(currEteOutFile, std::ios::app);
			myfile3 << elapsed_time_span.count() << "\n";
			myfile3.close();
			*/


			if (res1 != res2) {
				cout << "failed, baseline is " << res1 << ", vte_reach is " << res2 << "\n" ;
				return 0;
			}
			
			

			string rate = degDist + folderName + "/rate.txt";
			std::ofstream file4(rate, std::ios::app);
			file4 << res2 << "\n";
			file4.close();

			if (res2 > 1) reach++;
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
