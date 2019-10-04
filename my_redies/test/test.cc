#include <stdio.h>
#include <string>
int main()
{
  std::string b(" b");
   b = "a" + b;
   printf("%s\n",b.c_str());
    return 0;
}

