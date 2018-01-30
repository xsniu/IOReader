//
//  IOReader.cpp
//  
//
//  Created by cool on 16/8/25.
//
//

#include "IOReader.h"
#include <string.h>

IOReader::IOReader(unsigned buf_size) : _lineno(0), _colno(0), _fp(0), _nch(0), _cur_index(0)/*, _tab_num(0)*/
{
    _buf = new char[buf_size];
    memset(_buf, 0, buf_size);
}

IOReader::~IOReader()
{
    if (_fp) {
        fclose(_fp);
    }

    if (_buf)
    {
        delete [ ]_buf;
        _buf = 0;
    }
}

unsigned IOReader::OpenFile(char *file)
{
    if (fopen_s(&_fp, file, "rt"))
    {
        cout << "File %s can not open!" << endl;
        return 0;
    }

    _lineno = 1;
    AdvanceChar();
    return 1;
}

void IOReader::AdvanceChar()
{
    _nch = fgetc(_fp);
    if (_nch == EOF)
    {
        return;
    }
    
    ++_colno;
//     if (_nch == '\t')
//     {
//         ++_tab_num;
//     }

    if (_nch == '\n')
    {
        ++_lineno;
        _colno = 0;
/*        _tab_num = 0;*/
    }
}

void IOReader::ReadNext()
{
    // skip space
    if (_buf == 0)
    {
        return;
    }

    while (_nch != EOF && (isspace(_nch) || _nch == '\t'))
    {
        AdvanceChar();
    }

    if (_nch == EOF)
    {
       delete [ ] _buf;
       _buf = 0;
        return;
    }

    _cur_index = 0;
    for (; ;)
    {
        _buf[_cur_index++] = _nch;
        AdvanceChar();

        if (EOF == _nch || isspace(_nch))
        {
            break;
        }

        if (_cur_index >= BUF_SIZE)
        {
            cout << "String is too long at line  %d." << _lineno << endl;
            return;
        }


    }
    memset(_buf + _cur_index, 0, BUF_SIZE - _cur_index);
}