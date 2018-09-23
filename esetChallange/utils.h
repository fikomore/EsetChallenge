//
//  utils.h
//  esetChallange
//
//  Created by Fikrim Kabashi on 7.9.18.
//  Copyright © 2018 Fikrim Kabashi. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <sys/stat.h>
#include <string>

long long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    long long rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

#endif /* utils_h */
