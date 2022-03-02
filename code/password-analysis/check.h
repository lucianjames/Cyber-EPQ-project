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
