//
//  textChunk.hpp
//  esetChallange
//
//  Created by Fikrim Kabashi on 1.9.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#ifndef textChunk_hpp
#define textChunk_hpp

#include "globals.h"
#include <stdio.h>
#include <string>
#include <vector>


class TextChunk{
public:
    TextChunk();
    TextChunk(std::string const &path,long long position);
//    TextChunk(std::pair<std::string, long long> path);
    TextChunk(std::pair<std::string, long long> path, long long size);
    ~TextChunk();
    
    void ReadFromFile();
    void FindPattern(const std::string &pattern, std::vector<std::string> *output, std::mutex &mutex,
                     long long position = 0
                     );
    std::string FindPrefix();
    std::string FindSufix();
private:
    std::string path_;
    long long position_;
    long long size_;
//    std::vector<char> text_;
    std::string* text_;
};
#endif /* textChunk_hpp */
