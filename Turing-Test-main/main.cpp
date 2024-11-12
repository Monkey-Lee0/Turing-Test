#include<bits/stdc++.h>
#include"generator.h"
std::mt19937 RNG(time(nullptr));
int main()
{
    while(true)
    {
        if(RNG()&1)
        {
            if(check(generator_normal(5)))
                std::cout<<"Oh! You are maybe a human!"<<std::endl;
            else
                std::cout<<"Hello, bot. You are arrested!"<<std::endl;
        }
        else
        {
            if(check(generator_arithmetic(30)))
                std::cout<<"Oh! You are maybe a human!"<<std::endl;
            else
                std::cout<<"Hello, bot. You are arrested!"<<std::endl;
        }
    }


    return 0;
}
