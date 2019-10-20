//
// Created by kiosk on 19-10-7.
//
#include "decondig.h"

void deconding::EncodeInt32(  char *intput , uint32_t value) {

    //varByte算法，根据数据大小使用不同个数的字节来进行存储
    //varint 编码是对于较小数来进行压缩，但是需要大数可能需要5bytes
    //采用每8bit存入，第一个字节标志为数据是不是已经读取完毕
    //同时在这里还可以使用zigzag 方式，把第一位的符号位往最后挪
    const int B = 128;
    int iEncodeLen = 0;
     char * ptr =  intput;
    while(value >= B)
    {
        *(ptr + ( iEncodeLen++)) = ( char)((value & (B-1)) | B);
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


int deconding::smaz_compress(std::string &in, int inlen, std::string *out) {
   unsigned  int h1,h2,h3= 0 ;
   int verblen = 0;
   char verb[256];
   int in_ = 0;
   while(inlen) {
       int j = 7; // 每7个字符进行比较

       int slot_offest = 0;
       h1 = h2 = in[in_] << 3;
       if (inlen > 1) h2 += in[in_ + 1];
       if (inlen > 2) h3 = h2 ^ in[in_ + 2];
       if (j > inlen) j = inlen;
       std::string slot;
       for (; j >= 0; j--) {
           switch (j) {
               case 1:
                   slot = Smaz_cb[h1 % 241];
                   break;
               case 2:
                   slot = Smaz_cb[h2 % 241];
                   break;
               default:
                   slot = Smaz_cb[h3 % 241];
                   break;
           }
       }
   }
}
long deconding::smaz_decompress(std::string &in, int inlen, std::string *out) {
    long c = 0;
    auto *_out = const_cast<char *>  (out->data());
    while(inlen){
        if(in.at(c) == static_cast<char>(254))
        {
            *_out = in.at(c+1);
            _out++;
            c += 2;
            inlen -= 2;
        }
        else if (in.at(c) == static_cast<char>(255))
        {
            int len = (in.at(c+1)) + 1;

            memcpy(_out,in.data() + c +2,len);
            out += len;
            c += 2+len;
            inlen -= 2+len;
        }else {
            out->append( Smaz_rcb[in.at(c)]);// 追加到其后
            c++; // 切换到下一位
            inlen--;
        }
    }
    return out->data() - _out;
}
