#ifndef RANDOMIZATION_H
#define RANDOMIZATION_H

#include<ctime>
#include<random>

inline long long t=0;
inline std::mt19937 rng(time(0));
double rand_double(){return 1.0*(rng()%1000000000)/1e9;}
int rand_int(int l,int r){return rng()%(r-l+1)+l;}
int rand_color_gray()
{
	int base_value=rng()%256,offset=rng()%61-30;
	return std::max(0, std::min(255, base_value + offset))*(256*256+256+1);
}
int rand_color(){return rng()%16777216;}
int rand_color_white()
{
	return (rand_int(180,255)*256+rand_int(180,255))*256+rand_int(180,255);
}
int rand_color_black()
{
	return (rand_int(0,75)*256+rand_int(0,75))*256+rand_int(0,75);
}
bool near_white(int col)
{
	int x=col%256;col/=256;
	int y=col%256;col/=256;
	int z=col%256;
	return (x>=180&&y>=180&&z>=180);
}
bool near_black(int col)
{
	int x=col%256;col/=256;
	int y=col%256;col/=256;
	int z=col%256;
	return (x<=75&&y<=75&&z<=75);
}
inline void update_mt(){if(t!=std::time(nullptr))t=time(nullptr),rng.seed(t);}

#endif
