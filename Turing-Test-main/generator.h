//
// Created by LJY on 24-11-12.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include<random>
#include<ctime>
#include<iostream>
#include<vector>

struct captcha_data
{
    std::string question;
    std::string result;
};

inline std::mt19937 rng(0);
inline long long t=0;

inline void update_mt(){if(t!=std::time(nullptr))t=time(nullptr),rng.seed(t);}

inline captcha_data generator_normal(const int siz=5)
{
    update_mt();
    captcha_data new_captcha;
    for(int i=1;i<=siz;i++)
    {
        const int op=static_cast<int>(rng()%62);
        if(op<=9)
            new_captcha.question+=static_cast<char>(op + '0');
        else if(op<=35)
            new_captcha.question+=static_cast<char>(op-10+'a');
        else
            new_captcha.question+=static_cast<char>(op-36+'A');
    }
    new_captcha.result=new_captcha.question;
    return new_captcha;
}

inline captcha_data generator_arithmetic(const int siz=3)
{
    update_mt();
    captcha_data new_captcha;
    std::vector<int> number;
    for(int i=1;i<=siz;i++)
    {
        if(i!=1)
        {
            const int op=static_cast<int>(rng()%3);
            if(!op)
                new_captcha.question+="*";
            else if(op==1)
                new_captcha.question+="+";
            else
                new_captcha.question+="-";
        }
        new_captcha.question+=static_cast<char>(rng()%10+'0');
    }
    std::string expression;
    int las=-1,now=0;char op='+';
    for(int i=0;i<2*siz-1;i++)
    {
        if(new_captcha.question[i]>='0'&&new_captcha.question[i]<='9')
        {
            if(las==-1)
                las=new_captcha.question[i]-'0';
            else
                las*=new_captcha.question[i]-'0';
        }
        else if(new_captcha.question[i]!='*')
            expression+=std::to_string(las),expression+=new_captcha.question[i],las=-1;
    }
    expression+=std::to_string(las);
    las=0;
    for(auto t:expression)
    {
        if(t>='0'&&t<='9')
            now=now*10+t-'0';
        else
        {
            if(op=='+')
                las+=now;
            else
                las-=now;
            op=t,now=0;
        }
    }
    if(op=='+')
        las+=now;
    else
        las-=now;
    new_captcha.result=std::to_string(las);
    return new_captcha;
}

inline bool check(const captcha_data &a)
{
    std::cout<<a.question<<std::endl;
    std::cout<<"Please rewrite (maybe calculate) the content above:";
    std::string c;
    std::getline(std::cin,c);
    return c==a.result;
}

#endif //GENERATOR_H
