//
// Created by kiosk on 19-9-3.
//
#include "deconding.h"
void deconding::SetInt32(std::string *dst, uint32_t value) {

}
void deconding::SetInt64(std::string *dst, uint64_t value) {

}
void deconding::Setintset(std::string *dst, std::set<int> value) {

}
void deconding::Setsds(std::string *dst, std::string value) {

}
unsigned char* deconding::EncodeInt32(char *intput , uint32_t value) {

    //varByte算法，根据数据大小使用不同个数的字节来进行存储
    //varint 编码是对于较小数来进行压缩，但是需要大数可能需要5bytes
    //采用每8bit存入，第一个字节标志为数据是不是已经读取完毕
    //同时在这里还可以使用zigzag 方式，把第一位的符号位往最后挪

    const int B = 128;
    int iEncodeLen = 0;
    unsigned char * ptr = reinterpret_cast< unsigned char  *> (intput);
    while(value >= B)
    {
        *(ptr + ( iEncodeLen++)) = (unsigned char)((value & (B-1)) | B);
        value >>= 7;
    }
    *(ptr + (iEncodeLen ++ )) = value;
    return ptr;
}
unsigned char *deconding::EncodeInt64(char *intput , uint64_t value) {
    const int B = 128 ;
    unsigned char  * ptr = reinterpret_cast<unsigned char *>(intput);
    static int i = 0 ;
    while( value >= B){
        ptr[i]  = (unsigned char) (value | B);
        value >>= 7 ;
        i++;
    }
    ptr[i] = static_cast<unsigned char > (value);
    return ptr;
}
const char* deconding::EncodeSds(char *intput , std::string value) {

}
std::string deconding::DecodeSds(const unsigned char *ptr) {

}
uint32_t deconding::DecodeInt32(const  unsigned char *ptr) {
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
uint64_t deconding::DecodeInt64(const unsigned char *ptr) {
    uint64_t  result = 0 ;
    for(uint32_t i  = 0 ; i <= 63 ; i += 7)
    {
        uint64_t byte = *(reinterpret_cast<const uint8_t  *>(ptr));
        ptr++;
        if(byte & 128){
            result |= ((byte & 127) << i );
        }
        else {
            result |= (byte << i);
            return result;
        }
    }
    return 0;
}
