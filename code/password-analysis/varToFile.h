#include <fstream>
#include <vector>

template <typename T>
void writeVarToFile(std::string filename, T x){
    std::ofstream stream;
    stream.open(filename);
    stream << x;
    stream.close();
}

template <typename T>
void writeVectToFile(std::string filename, std::vector<T> x){
    int xlen = x.size();
    std::ofstream stream;
    stream.open(filename);
    for(int i=0; i<xlen-1; i++){
        stream << x[i] << ",";
    }
    stream << x[xlen];
    stream.close();
}
