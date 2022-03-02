#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "varToFile.h"
#include "contains.h"
#include "check.h"

#define maxlen 25 // Anything more than 25 is rather likely to just be junk

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
    unsigned int errors = 0;
    
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
            
            // Character set shit
            bool lcu = containsUpper(lineString);
            bool lcl = containsLower(lineString);
            bool lcd = containsDigit(lineString);
            bool lcs = containsSpecial(lineString);
            if(!(lcl || lcd || lcs)){n_up++;}
            else if(!(lcu || lcd || lcs)){n_lw++;}
            else if(!(lcu || lcl || lcs)){n_dg++;}
            else if(!(lcu || lcl || lcd)){n_sp++;}
            else if((lcl && lcu) && !(lcd || lcs)){n_up_lw++;}
            else if((lcu && lcd) && !(lcl || lcs)){n_up_dg++;}
            else if((lcu && lcs) && !(lcl || lcd)){n_up_sp++;}
            else if((lcl && lcd) && !(lcu || lcs)){n_lw_dg++;}
            else if((lcl && lcs) && !(lcu || lcd)){n_lw_sp++;}
            else if((lcd && lcs) && !(lcu || lcl)){n_dg_sp++;}
            else if((lcu && lcl && lcd) && !lcs){n_up_lw_dg++;}
            else if((lcu && lcl && lcs) && !lcd){n_up_lw_sp++;}
            else if((lcl && lcd && lcs) && !lcu){n_lw_dg_sp++;}
            else if((lcu && lcd && lcs) && !lcl){n_up_dg_sp++;}
            else if(lcu && lcl && lcs && lcd){n_up_lw_dg_sp++;}
            else{errors++;}
        }else{
            ignored+=1; // Ignore string if its a mess
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
