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
