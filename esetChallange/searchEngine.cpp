//
//  searchEngine.cpp
//  esetChallange
//
//  Created by Fikrim Kabashi on 5.9.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#include "searchEngine.hpp"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/system/system_error.hpp>
#include "utils.h"
#include <algorithm>

SearchEngine::SearchEngine(){}

SearchEngine::SearchEngine(std::string const &path, std::string const &pattern): pattern_(pattern), output_(*new std::vector<std::string>) {
    end_=false;
    FindAllPaths(path);
    StartSearching();
//    PrintAllFiles();
}

SearchEngine::~SearchEngine(){}

void SearchEngine::FindAllPaths(const std::string &path){
    if (!boost::filesystem::is_directory(path) && !boost::filesystem::is_regular_file(path)) {
        std::cerr<<"\""<< path <<"\" is not a File or a Directory!"<<std::endl;
        std::_Exit(1);
    }
    boost::filesystem::path p = path;
    boost::system::error_code ec;
    if (boost::filesystem::is_directory(p)) {
        for (boost::filesystem::recursive_directory_iterator it(p,ec), end; it != end; it.increment(ec)) {
            if (!boost::filesystem::is_directory(it->path())) {
                if (it->path().extension() == ".txt") {
                    this->paths_and_positions_.push_back(std::make_pair(it->path().generic_string(), 0));
                }
            }
        }
    }
    else{
        if (p.extension() == ".txt") {
            this->paths_and_positions_.push_back(std::make_pair(path, 0));
        }
    }
    if (paths_and_positions_.size() == 0) {
        std::cerr<< "Any .txt file in this directory!"<< std::endl;
        std::_Exit(1);
    }
}

void SearchEngine::StartSearching() {
    while (!end_) {
        TextSplitting();
        FindWorkers();
        std::cout<<"Velkost outputu: "<<output_.size()<<std::endl;
        Join();
        PrintOutput();
    }
}

void SearchEngine::TextSplitting() {
    if (paths_and_positions_.size() != 0) {
        if (buffer_.GetChunks()->size()<kMaxBufferSize) {
            long long file_size = GetFileSize(paths_and_positions_.front().first);
            if (paths_and_positions_.front().second==0) {
                if (file_size<kMaxChunkSize) {
                    buffer_.FillBuffer(paths_and_positions_.front(), file_size);
                    paths_and_positions_.pop_front();
                }else {
                    buffer_.FillBuffer(paths_and_positions_.front());
                    paths_and_positions_.front().second += (kMaxChunkSize-pattern_.size()-kPrefixSize);
                }
            }else {
                if ((file_size - paths_and_positions_.front().second) < kMaxChunkSize) {
                    buffer_.FillBuffer(paths_and_positions_.front(), file_size-paths_and_positions_.front().second);
                    paths_and_positions_.pop_front();
                }else {
                    buffer_.FillBuffer(paths_and_positions_.front());
                    paths_and_positions_.front().second += (kMaxChunkSize-pattern_.size()-kPrefixSize);
                }
            }
        }
    }
}

void SearchEngine::FindWorkers() {
    if (workers_.size()<kMaxThreads) {
        if(buffer_.GetChunks()->size()>0) {
            workers_.push_back(std::thread(&::SearchEngine::ProcessChunk,this, buffer_.GetChunks()->front()));
            buffer_.GetChunks()->pop_front();
        }
    }
}

void SearchEngine::ProcessChunk(TextChunk chunk) {
    TextChunk t = chunk;
    t.ReadFromFile();
    t.FindPattern(pattern_, &output_, mutex_);
}

void SearchEngine::Join() {
    for (int i=0; i<workers_.size(); i++) {
        if (workers_[i].joinable()) {
            workers_[i].join();
            workers_.erase(workers_.begin()+i);
        }
    }
}

void SearchEngine::PrintAllFiles() {
    for (int i=0; i<paths_and_positions_.size(); i++) {
        std::cout<<paths_and_positions_[i].first<<std::endl;
    }
}

void SearchEngine::PrintOutput() {
    for (int i=0; i<output_.size(); i++) {
        std::cout<<"Pozicia:"<<output_[i]<<std::endl;
    }
}
