//
// Created by kiosk on 2020/2/10.
//
#include "../src/core/db.h"
#include "../base/dict_builder.h"

int main(){
    std::unique_ptr<dict> m_db = dict::Init("1.log","tts");
    std::string c ;
    m_db->Get("1",c);
    return 0;
}
