//
//  globals.h
//  esetChallange
//
//  Created by Fikrim Kabashi on 26.8.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#ifndef globals_h
#define globals_h

#include <thread>

const int kMaxPatternSize = 128;
const int kMaxBufferSize = 10;
const long long kMaxChunkSize = 50;
const int kPrefixSize = 0;
const int kSufixSize = 0;
const int kMaxThreads = std::thread::hardware_concurrency();



#endif /* globals_h */
