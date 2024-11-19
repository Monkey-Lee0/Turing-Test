#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include"generator.h"
using namespace std;

int main()
{
	int T=10,cnt=0;
    while(T--)
    {
        if(rng()&1)
        {
            if(check(generator_normal(5)))
                std::cout<<"Oh! You are maybe a human!"<<std::endl,cnt++;
            else
                std::cout<<"Hello, bot. You are arrested!"<<std::endl;
        }
        else
        {
            if(check(generator_arithmetic(3)))
                std::cout<<"Oh! You are maybe a human!"<<std::endl,cnt++;
            else
                std::cout<<"Hello, bot. You are arrested!"<<std::endl;
        }
    }
	if(cnt>=3)
		print_human();
	else
		print_bot();

    return 0;
}
