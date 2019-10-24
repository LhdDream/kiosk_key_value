//
// Created by kiosk on 19-10-23.
//
#include "Block.h"
//这里使用block进行解码等操作
static void DecondEntry(const std::string *p,std::string *key,std::string *value)
{
    // 找出key的长度
    auto it = p->find("\r\n"); // 找出Key的长度
    if(it != -1) {
        std::copy(p->begin(), p->begin() + it, key->begin());
        std::copy(p->begin() + it+ 2,p->end() -2 ,value->end());
        //获取到key和value
    }
    else
        return ;
    // 把key放入其中
}
