////
//// Created by kiosk on 2020/2/10.
////
//#include <iostream>
//#include "../src/core/db.h"
//#include "../base/dict_builder.h"
//#include <memory>
//#include <chrono>
//using namespace std;
//
//
//char *rand_str(char *str,const int len)
//{
//    srand(time(nullptr));
//    int i;
//    for(i=0;i<len;++i)
//    {
//        switch((rand()%3))
//        {
//            case 1:
//                str[i]='A'+rand()%26;
//                break;
//            case 2:
//                str[i]='a'+rand()%26;
//                break;
//            default:
//                str[i]='0'+rand()%10;
//                break;
//        }
//    }
//    str[++i]='\0';
//    return str;
//}
//int main(){
//
//    std::unique_ptr<db> m_db= dict::Init("1.log");
//    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
//
//    /*代码段*/
//
//    char c[6];
//    for(int i = 0 ;  i < 1000000 ;i++)
//    {
//        bzero(c, sizeof(c));
//        rand_str(c,4);
//    }
//
//    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
//    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
//    std::cout << "time used ：" << time_used.count() << "seconds." << std::endl;
//
//
//    return 0;
//}
