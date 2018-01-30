//
//  IOReader.h
//  
//
//  Created by cool on 16/8/25.
//
//

#ifndef ____IOReader__
#define ____IOReader__

#include <stdio.h>
#include <iostream>
using namespace std;

const int BUF_SIZE = 64;

class IOReader
{
    char*         _buf;
    FILE*        _fp;
    int              _nch;
    unsigned  _lineno;
    unsigned  _colno;
    int              _cur_index;
    
public:
    IOReader(unsigned buf_size = BUF_SIZE);
    ~IOReader();
    
    unsigned      GetLineNo()   { return _lineno; }
    unsigned      GetColNO()    { return _colno; }
    unsigned      OpenFile(char *file);
    void               AdvanceChar();
    void              ReadNext();
    char*            GetBuf()           { return _buf; }

};

#endif /* defined(____IOReader__) */
