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

int main(int argc, char** argv){
    if(argc != 2){
        throw std::invalid_argument("Received invalid arguments");
    }
    std::string lineString;
    std::ifstream file(argv[1]);
    if (!file.is_open()){
        std::cout << "Failed to open" << std::endl;
    }

    // These variables hold the statstics that we want to analyse.
    std::vector<unsigned int> lengths;
    lengths.resize(maxlen); // Anything above "maxlen" characters will go in a seperate variable.
    unsigned int aboveMaxLen = 0;
    unsigned int ignored = 0;

    // Main loop where the analysis of the file will take place
    while (getline (file, lineString)) {
        if(check(lineString)){
            int linelen = lineString.length();
            if (linelen < maxlen){
                lengths[linelen]+=1;
            }else{
                aboveMaxLen+=1;
            }
        }else{
            ignored+=1;
        }
    }
    file.close();

    // Display statistics to the terminal
    for(int i=0; i<maxlen; i++){
        std::cout << i << ": " << lengths[i] << std::endl;
    }
    std::cout << "Longer: " << aboveMaxLen << std::endl;
    std::cout << "Ignored: " << ignored << std::endl;

    // Save statstics
    // One file per statistic should make life easiest
    std::ofstream statsOutput;
    statsOutput.open("output/lengths");
    for(int i=0; i<maxlen; i++){
        statsOutput << lengths[i];
        if(i != maxlen-1){
            statsOutput << ",";
        }
    }
    statsOutput.close();
    statsOutput.open("output/aboveMaxLen");
    statsOutput << aboveMaxLen;
    statsOutput.close();
    statsOutput.open("output/ignored");
    statsOutput << ignored;
    statsOutput.close();

    return 0;
}
