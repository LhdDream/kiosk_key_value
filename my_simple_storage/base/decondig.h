#ifndef MY_SIMPLE_STORAGE_DECONDING_H
#define MY_SIMPLE_STORAGE_DECONDING_H
//打算使用snappy来进行解压缩
#include <string>
#include <cstring>
namespace deconding{
    //对于int32 进行编码的压缩
    void EncodeInt32(char *intput , uint32_t value);
    uint32_t DecodeInt32(const char * ptr);
    //短字符串的压缩
    void Smaz_Compress(const char *in, int inlen,  std::string &out);
    void Smaz_Decompress(const char *in, int inlen,std::string & out);
}


#endif //MY_REDIES_ZIPLIST_H