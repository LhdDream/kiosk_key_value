//
// Created by kiosk on 19-9-3.
//
#include "deconding.h"

#include <utility>
void deconding::SetInt32(std::string *dst, uint32_t value) {
    //将value 存入string　中
    unsigned char buf[5];
    bzero(buf,sizeof(unsigned char) * 5);
    const char *ptr = reinterpret_cast<const char *>(EncodeInt32(buf, value));
    dst->append(ptr);
}
void deconding::SetInt64(std::string *dst, uint64_t value) {
    unsigned  char buf[10];
    bzero(buf,sizeof(unsigned char ) * 10);
    const  char * ptr = reinterpret_cast<const char *>(EncodeInt64(buf, value));
    dst->append(ptr);
}
//解压缩的以相同的方式进行解压缩
void deconding::Setsds(std::string *dst, std::string value) {
    dst->append(EncodeSds(std::move(value)));
}

unsigned char* deconding::EncodeInt32( unsigned char *intput , uint32_t value) {

    //varByte算法，根据数据大小使用不同个数的字节来进行存储
    //varint 编码是对于较小数来进行压缩，但是需要大数可能需要5bytes
    //采用每8bit存入，第一个字节标志为数据是不是已经读取完毕
    //同时在这里还可以使用zigzag 方式，把第一位的符号位往最后挪
    const int B = 128;
    int iEncodeLen = 0;
    unsigned char * ptr =  intput;
    while(value >= B)
    {
        *(ptr + ( iEncodeLen++)) = (unsigned char)((value & (B-1)) | B);
        value >>= 7;
    }
    *(ptr + (iEncodeLen ++ )) = value;
    return ptr;
}
unsigned char *deconding::EncodeInt64(unsigned char *intput , uint64_t value) {
    const int B = 128 ;
    auto  * ptr = reinterpret_cast<unsigned char *>(intput);
    static int i = 0 ;
    while( value >= B){
        ptr[i]  = (unsigned char) (value | B);
        value >>= 7 ;
        i++;
    }
    ptr[i] = static_cast<unsigned char > (value);
    return ptr;
}
const char* deconding::EncodeSds( const std::string& value) {
    sds temp(value);
    return temp.data();
}
std::string deconding::DecodeSds(sds *ptr) {
    return ptr->Tostring();
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
uint64_t deconding::DecodeInt64(const  char *ptr)
{
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
bool deconding::GetInt32(sds * input,uint32_t * value){
    *value = DecodeInt32(input->data());
    return *value != 0;
}
bool deconding::GetInt64(sds *input, uint64_t *value) {
    *value = DecodeInt64(input->data());
    return *value != 0;
}
bool deconding::GetSds(sds *input, sds *value) {
    *value = DecodeSds(value);
    return *value != nullptr;
}
