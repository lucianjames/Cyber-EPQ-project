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

	unsigned int n_up = 0; // only uppercase
	unsigned int n_lw = 0; // only lowercase
	unsigned int n_dg = 0; // only digits
	unsigned int n_sp = 0; // only special
	
	unsigned int n_up_lw = 0; // uppercase + lowercase
	unsigned int n_up_dg = 0; // uppercase + digits
	unsigned int n_up_sp = 0; // uppercase + special

	unsigned int n_lw_dg = 0; // lowercase + digits
	unsigned int n_lw_sp = 0; // lowercase + special

	unsigned int n_dg_sp = 0; // digits + special

	unsigned int n_up_lw_dg = 0; // uppercase + lowercase + digits
	unsigned int n_up_lw_sp = 0; // uppercase + lowercase + special

	unsigned int n_lw_dg_sp = 0; // lowercase + digits + special
	unsigned int n_up_dg_sp = 0; // uppercase + digits + special

	unsigned int n_up_lw_dg_sp = 0; // uppercase + lowercase + digits + special

    
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
            bool lcu = containsUpper(lineString);
            bool lcl = containsLower(lineString);
            bool lcd = containsDigit(lineString);
            bool lcs = containsSpecial(lineString);

			if(!(lcl || lcd || lcs)){n_up++;}
			if(!(lcu || lcd || lcs)){n_lw++;}
			if(!(lcu || lcl || lcs)){n_dg++;}
			if(!(lcu || lcl || lcd)){n_sp++;}
            
            if((lcl && lcu) && !(lcd || lcs)){n_up_lw++;}
            if((lcu && lcd) && !(lcl || lcs)){n_up_dg++;}
            if((lcu && lcs) && !(lcl || lcd)){n_up_sp++;}
            
            if((lcl && lcd) && !(lcu || lcs)){n_lw_dg++;}
            if((lcl && lcs) && !(lcu || lcd)){n_lw_sp++;}
            
            if((lcd && lcs) && !(lcu || lcl)){n_dg_sp++;}
            
            if((lcu && lcl && lcd) && !lcs){n_up_lw_dg++;}
            if((lcu && lcl && lcs) && !lcd){n_up_lw_sp++;}

            if((lcl && lcd && lcs) && !lcu){n_lw_dg_sp++;}
            if((lcu && lcd && lcs) && !lcl){n_up_dg_sp++;}
			
            if(lcu && lcl && lcs && lcd){n_up_lw_dg_sp++;}

            
            
        }else{
            ignored+=1;
        }
    }
    file.close();

    // Save statstics
    writeVectToFile("output/lengths", lengths);

	writeVarToFile("output/n_up", n_up);
	writeVarToFile("output/n_lw", n_lw);
	writeVarToFile("output/n_dg", n_dg);
	writeVarToFile("output/n_sp", n_sp);
	
	writeVarToFile("output/n_up_lw", n_up_lw);
	writeVarToFile("output/n_up_dg", n_up_dg);
	writeVarToFile("output/n_up_sp", n_up_sp);
	
	writeVarToFile("output/n_lw_dg", n_lw_dg);
	writeVarToFile("output/n_lw_sp", n_lw_sp);
	
	writeVarToFile("output/n_dg_sp", n_dg_sp);

	writeVarToFile("output/n_up_lw_dg", n_up_lw_dg);
	writeVarToFile("output/n_up_lw_sp", n_up_lw_sp);

	writeVarToFile("output/n_lw_dg_sp", n_lw_dg_sp);
	writeVarToFile("output/n_up_dg_sp", n_up_dg_sp);

	writeVarToFile("output/n_up_lw_dg_sp", n_up_lw_dg_sp);
    
    writeVarToFile("output/aboveMaxLen", aboveMaxLen);
    writeVarToFile("output/ignored", ignored);

    return 0;
}
