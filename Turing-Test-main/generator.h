//
// Created by LJY on 24-11-12.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include"randomization.h"
#include<iostream>
#include<vector>
#include<graphics.h>
#include<conio.h>
#include<windows.h>

const double pi=acos(-1);

struct captcha_data
{
    std::string question;
    std::string result;
};

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

void print_human()
{
	IMAGE img;
	initgraph(1700, 450,EX_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	std::string a="Human";
	for(int i=1;i<=5;i++)
	{
		char t=a[i-1];
		std::string now="./picture/";
		if((t>='A'&&t<='Z')||t=='+'||t=='-'||t=='*')
			now+='~';
		if(t=='+')
			now+="add";
		else if(t=='-')
			now+="sub";
		else if(t=='*')
			now+="mul";
		else
			now+=t;
		now+="/1.png";
		loadimage(&img,now.c_str(), 210,210,false);
		putimage((i-1)*320+50,50,&img);
	}
	for(int i=1;i<=1700;i++)//gray background color
		for(int j=1;j<=450;j++)
			if(near_white(getpixel(i,j)))
				putpixel(i,j,rand_color_white());
	getch();
}

void print_bot()
{
	IMAGE img;
	initgraph(1700, 450,EX_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	std::string a="Bot";
	for(int i=2;i<=4;i++)
	{
		char t=a[i-2];
		std::string now="./picture/";
		if((t>='A'&&t<='Z')||t=='+'||t=='-'||t=='*')
			now+='~';
		if(t=='+')
			now+="add";
		else if(t=='-')
			now+="sub";
		else if(t=='*')
			now+="mul";
		else
			now+=t;
		now+="/1.png";
		loadimage(&img,now.c_str(), 210,210,false);
		putimage((i-1)*320+50,50,&img);
	}
	for(int i=1;i<=1700;i++)//gray background color
		for(int j=1;j<=450;j++)
			if(near_white(getpixel(i,j)))
				putpixel(i,j,rand_color_white());
	getch();
}

void print(const captcha_data &a)
{
	IMAGE img1,img2;
	initgraph(1800, 450,EX_SHOWCONSOLE);
	static IMAGE img(1800, 450);
	SetWorkingImage(&img);
	setbkcolor(WHITE);
	cleardevice();
	for(int i=1;i<=5;i++)
	{
		char t=a.question[i-1];
		std::string now="./picture/";
		if((t>='A'&&t<='Z')||t=='+'||t=='-'||t=='*')
			now+='~';
		if(t=='+')
			now+="add";
		else if(t=='-')
			now+="sub";
		else if(t=='*')
			now+="mul";
		else
			now+=t;
		now+="/1.png";
		loadimage(&img1,now.c_str(), 220,120,false);
		double angle=pi/12+pi/6*rand_double();
		if(rng()&1)
			angle=-angle;
		rotateimage(&img2, &img1,angle,WHITE,true);
		putimage((i-1)*320+rand_int(25,50),rand_int(20,100),&img2);
	}
	for(int i=1;i<=60;i++)//paint rectangles
	{
		double left=rng()%1600+80,top=rng()%300+80;
		int length=round(30+30*rand_double()),width=round(15+15*rand_double());
		double angle=2*pi*rand_double();
		for(double x=1;x<=length;x+=0.1)
			for(double y=1;y<=width;y+=0.1)
			{
				double cross=hypot(x,y),ang=angle+atan(y/x);
				double pos_x=left+cross*cos(ang),pos_y=top+cross*sin(ang);
				if(rng()%4==1)
					putpixel(pos_x,pos_y,rand_color_gray());
			}
	}
	for(int i=1;i<=40;i++)//paint lines
	{
		double left=rng()%1600+80,top=rng()%300+80;
		int length=round(300+700*rand_double()),width=round(3+3*rand_double());
		double angle=2*pi*rand_double();
		for(double x=1;x<=length;x+=0.1)
			for(double y=1;y<=width;y+=0.1)
			{
				double cross=hypot(x,y),ang=angle+atan(y/x);
				double pos_x=left+cross*cos(ang),pos_y=top+cross*sin(ang);
				if(rng()%2==1)
					putpixel(pos_x,pos_y,rand_color());
			}
	}
	for(int i=1;i<=1800;i++)//gray background color
		for(int j=1;j<=450;j++)
			if(near_white(getpixel(i,j)))
				putpixel(i,j,rand_color_white());
			else if(near_black(getpixel(i,j)))
				putpixel(i,j,rand_color_black());
	SetWorkingImage();
	putimage(0, 0, &img);
}

inline bool check(const captcha_data &a)
{
	print(a);
    std::cout<<"Please rewrite (maybe calculate) the content above:";
    std::string c;
    std::getline(std::cin,c);
	closegraph();
    return c==a.result;
}

#endif //GENERATOR_H
