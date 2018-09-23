//
//  buffer.hpp
//  esetChallange
//
//  Created by Fikrim Kabashi on 5.9.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#ifndef buffer_hpp
#define buffer_hpp

#include "textChunk.hpp"
#include <stdio.h>
#include <string>
#include <deque>
#include <utility>


class Buffer{
public:
    Buffer();
    ~Buffer();
    
    std::deque<TextChunk>* GetChunks();
    void FillBuffer(const std::pair<std::string, long long> pathAndPositions, long long chunkSize = kMaxChunkSize);
private:
    std::deque<TextChunk> text_chunks_;
};

#endif /* buffer_hpp */
