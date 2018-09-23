//
//  main.cpp
//  esetChallange
//
//  Created by Fikrim Kabashi on 17.8.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#include <iostream>
#include <string>
#include "searchEngine.hpp"
#include "globals.h"



int main(int argc, const char * argv[]) {
    
    if(argc != 3){
        std::cerr<<"Few arguments!"<<std::endl;
        return EXIT_FAILURE;
    }

    std::string inputPath = std::string(argv[1]);
    std::string inputPattern = std::string(argv[2]);

    if(inputPattern.size() > kMaxPatternSize) {
        std::cerr<<"Insertes pattern is to long!"<<std::endl;
        return EXIT_FAILURE;
    }
    

    SearchEngine searchEngine(inputPath, inputPattern);

    return 0;
}

