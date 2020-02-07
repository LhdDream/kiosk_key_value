//
// Created by kiosk on 19-9-6.
//

#ifndef MY_REDIES_RANDOM_H
#define MY_REDIES_RANDOM_H
//随机数类
#include <random>
#include <ctime>
int random_unint()
{
    std::srand(std::time(0));
    int uniform_random_variable = std::rand() % 9;
    return uniform_random_variable;
}
#endif //MY_REDIES_RANDOM_H
