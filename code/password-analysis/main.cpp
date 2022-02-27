#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

#define maxlen 32

std::string fixHex(std::string hexString){
    size_t len = hexString.length();
    std::string newString;
    for(int i=0; i<len; i+=2){
        std::string byte = hexString.substr(i,2);
        char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
        newString.push_back(chr);
    }
    return newString;
}

bool checkAndFixEncodings(std::string& str){
    // Some hex strings in one of the files seems to be marked with $HEX[(the string)], this should help fix strings from that specific file.
    // I also need to find other ways to check for hex, and other such encodings.
    if (str.rfind("$HEX[", 0) == 0) { // pos=0 limits the search to the prefix
        str.erase(0,5);
        str.pop_back();
        str = fixHex(str);
    }
    return true;
}

bool isASCII(const std::string str){
    return !std::any_of(str.begin(), str.end(), [](char c){return static_cast<unsigned char>(c) > 127;}); // This is straight from the internet, god knows how it works, but it does (i think).
}

bool check(std::string& str){
    // This tries to detect and fix hex strings
    if(!checkAndFixEncodings(str)) {return false;}
    if(!isASCII(str)) {return false;}
    return true;
}

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

bool containsUpper(const std::string x){
	for(int i=0; i<x.length(); i++){
		char c = x[i];
		if(isupper(c)){
			return true;
		}
	}
	return false;
}

bool containsLower(const std::string x){
	for(int i=0; i<x.length(); i++){
		char c = x[i];
		if(islower(c)){
			return true;
		}
	}
	return false;
}

bool containsDigit(const std::string x){
	for(int i=0; i<x.length(); i++){
		char c = x[i];
		if(isdigit(c)){
			return true;
		}
	}
	return false;
}

bool containsSpecial(const std::string x){
	for(int i=0; i<x.length(); i++){
		char c = x[i];
		if(!(isalpha(c) || isdigit(c))){
			return true;
		}
	}
	return false;
}


int main(int argc, char** argv){
    if(argc != 2){
        throw std::invalid_argument("Received invalid arguments");
    }
    std::string lineString;
    std::ifstream file(argv[1]);
    if (!file.is_open()){
        std::cout << "Failed to open file" << std::endl;
    }

    // These variables hold the statstics that we want to analyse.
    std::vector<unsigned int> lengths;
    lengths.resize(maxlen); // Anything above "maxlen" characters will go in a seperate variable.
	unsigned int nContainsUpper = 0;
	unsigned int nContainsLower = 0;
	unsigned int nContainsDigit = 0;
	unsigned int nContainsSpecial = 0;
    unsigned int aboveMaxLen = 0;
    unsigned int ignored = 0;
    
    // Main loop where the analysis of the file will take place
    while (getline (file, lineString)) { 
        if(check(lineString)){ // Check string isnt a mess
        	// Line length
            int linelen = lineString.length();
            if (linelen < maxlen){
                lengths[linelen]+=1;
            }else{
                aboveMaxLen+=1;
            }
            
            // Contains uppercase
            if(containsUpper(lineString)){
            	nContainsUpper+=1;
            }
            // Contains lowercase
            if(containsLower(lineString)){
            	nContainsLower+=1;
            }
            // Contains numbers
            if(containsDigit(lineString)){
            	nContainsDigit+=1;
            }
            // Contains special
            if(containsSpecial(lineString)){
            	nContainsSpecial+=1;
            }
            
            
        }else{
            ignored+=1;
        }
    }
    file.close();

    // Save statstics
    writeVectToFile("output/lengths", lengths);
    writeVarToFile("output/containsUpper", nContainsUpper);
    writeVarToFile("output/containsLower", nContainsLower);
    writeVarToFile("output/containsDigit", nContainsDigit);
    writeVarToFile("output/containsSpecial", nContainsSpecial);
    writeVarToFile("output/aboveMaxLen", aboveMaxLen);
    writeVarToFile("output/ignored", ignored);

    return 0;
}
