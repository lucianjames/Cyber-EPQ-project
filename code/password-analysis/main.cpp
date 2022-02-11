#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

#define maxlen 32

std::string fixHex(std::string hexString){
    std::cout << "BEFORE: " << hexString << std::endl;
    size_t len = hexString.length();
    std::string newString;
    for(int i=0; i<len; i+=2){
        std::string byte = hexString.substr(i,2);
        char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
        newString.push_back(chr);
    }
    std::cout << "AFTER: " << newString << std::endl;
    return newString;
}

bool checkAndFixHex(std::string& str){
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
    if(!checkAndFixHex(str)) {return false;}
    if(!isASCII(str)) {return false;}
    return true;
}

int main(int argc, char** argv){
    if(argc != 2){
        throw std::invalid_argument("Received invalid arguments");
    }
    std::string fileString;
    std::ifstream f(argv[1]);
    if (!f.is_open()){
        std::cout << "Failed to open" << std::endl;
    }

    // These variables hold the statstics that we want to analyse.
    std::vector<unsigned int> lengths;
    lengths.resize(maxlen); // Anything above "maxlen" characters will go in a seperate variable.
    unsigned int veryLong = 0;
    unsigned int ignored = 0;

    // Main loop where the analysis of the file will take place
    while (getline (f, fileString)) {
        if(check(fileString)){
            int linelen = fileString.length();
            if (linelen < maxlen){
                lengths[linelen]+=1;
            }else{
                veryLong+=1;
            }
        }else{
            ignored+=1;
        }
    }
    f.close();

    for(int i=0; i<maxlen; i++){
        std::cout << i << ": " << lengths[i] << std::endl;
    }
    std::cout << "Longer: " << veryLong << std::endl;
    std::cout << "Ignored: " << ignored << std::endl;

    return 0;
}
