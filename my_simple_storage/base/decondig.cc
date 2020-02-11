//
// Created by kiosk on 19-10-7.
//
#include "decondig.h"

void deconding::EncodeInt32(char *intput , uint32_t value) {
    //varByte算法，根据数据大小使用不同个数的字节来进行存储
    //varint 编码是对于较小数来进行压缩，但是需要大数可能需要5bytes
    //采用每8bit存入，第一个字节标志为数据是不是已经读取完毕
    //同时在这里还可以使用zigzag 方式，把第一位的符号位往最后挪
    const int B = 128;
    int iEncodeLen = 0;
    char * ptr =  intput;
    while(value >= B)
    {
        *(ptr + ( iEncodeLen++)) = static_cast<char>  ((value & (B-1)) | B);
        value >>= 7;
    }
    *(ptr + (iEncodeLen ++ )) = value;
}


uint32_t deconding::DecodeInt32(const  char *ptr)
{
    uint32_t b = 0 , len = 0;
    while(true)
    {
        b |= ((ptr[len] &(0x7f)) << (7 * len));
        if((ptr[len] & 0x80) != 0x80)
            break;
        len++;
    }
    return b;
}

