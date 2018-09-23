//
//  searchEngine.hpp
//  esetChallange
//
//  Created by Fikrim Kabashi on 5.9.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#ifndef searchEngine_hpp
#define searchEngine_hpp

#include "buffer.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include <deque>
#include <utility>
#include <thread>
#include <mutex>

class SearchEngine{
public:
    SearchEngine();
    SearchEngine(std::string const &path, std::string const &pattern);
    ~SearchEngine();
    
    void FindAllPaths(std::string const &path);
    void StartSearching();
    void TextSplitting();
    void FindWorkers();
    void ProcessChunk(TextChunk chunk);        //todo: dokodit
    void Join();
    void PrintAllFiles();
    void PrintOutput();
    std::mutex &getMutex();
private:
    Buffer buffer_;
    bool end_;
    std::string pattern_;
    std::vector<std::string> output_;
    std::vector<std::thread> workers_;
    std::mutex mutex_;
    std::deque<std::pair<std::string, long long>> paths_and_positions_;
    
};
#endif /* searchEngine_hpp */
