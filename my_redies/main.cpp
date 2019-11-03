#include <iostream>
#include "src/db.h"
#include "src/db_wr.h"

using namespace std;

int main()
{
    db * db_ = new wr();
    std::string c = " aaa";

    delete db_;
    return 0;
}
