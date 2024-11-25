g++ -O3 graph.cpp HI.cpp main.cpp -o till -std=c++17
./till data/NDC-substances-unique-hyperedges.txt D query.txt output1.txt 1
# ./till data/colored-MAG.txt D query.txt output1.txt
#./till graph.txt D query.txt output1.txt

#./till graph.txt D insert inserted_edge.txt query.txt output2.txt
#./till graph.txt D delete deleted_edge.txt query.txt output3.txt
