int nUpper(const std::string x){
    int n = 0;
    for(int i=0; i<x.length(); i++){
        char c = x[i];
        if(isupper(c)){
            n++;
        }
    }
    return n;
}
int nLower(const std::string x){
    int n = 0;
    for(int i=0; i<x.length(); i++){
        char c = x[i];
        if(islower(c)){
            n++;
        }
    }
    return n;
}
int nDigit(const std::string x){
    int n = 0;
    for(int i=0; i<x.length(); i++){
        char c = x[i];
        if(isdigit(c)){
            n++;
        }
    }
    return n;

}
int nSpecial(const std::string x){
    int n = 0;
    for(int i=0; i<x.length(); i++){
        char c = x[i];
        if(!(isalpha(c))){
            n++;
        }
    }
    return n;
}
