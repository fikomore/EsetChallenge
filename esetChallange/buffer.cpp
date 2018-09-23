//
//  buffer.cpp
//  esetChallange
//
//  Created by Fikrim Kabashi on 5.9.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#include "buffer.hpp"
#include <iostream>

Buffer::Buffer(){}

Buffer::~Buffer(){}

void Buffer::FillBuffer(const std::pair<std::string, long long> path, long long chunkSize){
    text_chunks_.push_back(TextChunk(path, chunkSize));
}


std::deque<TextChunk>* Buffer::GetChunks(){
    return &text_chunks_;
}

