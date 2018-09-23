//
//  textChunk.cpp
//  esetChallange
//
//  Created by Fikrim Kabashi on 1.9.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#include "textChunk.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

TextChunk::TextChunk(){}

TextChunk::TextChunk(std::string const &path, long long position): position_(position), path_(path){}

//TextChunk::TextChunk(std::pair<std::string, long long> path): path_(path.first), position_(path.second){
//    size_ = kMaxChunkSize;
//}

TextChunk::TextChunk(std::pair<std::string, long long> path, long long size): path_(path.first), position_(path.second), size_(size), text_(new std::string){}

TextChunk::~TextChunk(){}

//void TextChunk::ReadFromFile(){
//    std::ifstream in;
//    in.open(path_);
//    if(in.is_open()){
//        if(this->position_ != 0)
//            in.seekg(position_);
//        text_.resize(size_);
//        in.read(&text_[0],size_);
//    }else{
//        std::cerr<<"Unable to open file: "<<path_<<"at position:"<<position_<<std::endl;
//    }
//    in.close();
//}

void TextChunk::ReadFromFile(){
    std::ifstream in;
        in.open(path_);
        if(in.is_open()){
            if(this->position_ != 0)
                in.seekg(position_);
            text_->resize(size_);
            in.read(&(*text_)[0], size_);
        }else{
            std::cerr<<"Unable to open file: "<<path_<<"at position:"<<position_<<std::endl;
        }
        in.close();
}

//{TODO:} urobit to rekurzivne aby naslo vsetky zhody v danom chunku
//{TODO:} nakodit lepsi vystup aby neboli zhody 2x precitat aj prefix aj sufix

void TextChunk::FindPattern(const std::string &pattern, std::vector<std::string> *output, std::mutex &mutex,
                            long long position) {
    size_t pos = text_->find(pattern, position);
    if (pos != std::string::npos) {
        FindPattern(pattern, output, mutex, pos+pattern.size());
        pos += position_;
        std::stringstream ss;
        ss<<pos;
        mutex.lock();
        output->push_back(std::string(ss.str()));
        mutex.unlock();
        //Sem pride FindePrefix a FindSufix a spravit korektny zapis vystupi
    }
}

std::string TextChunk::FindPrefix() {
    return std::string("Ahoj");
}

std::string TextChunk::FindSufix() {
    return std::string("Ola");
}

