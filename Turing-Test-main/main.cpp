#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include"generator.h"
using namespace std;

int main()
{
	cerr<<"What do you want to do?"<<endl;
	cerr<<"1.check whether you are a human."<<endl;
	cerr<<"2.get some captcha picture"<<endl;
	int op;
	cin>>op;
	if(op==1)
	{
		int T=10,cnt=0;
		while(T--)
		{
			if(rng()&1)
			{
				if(check(generator_normal(5)))
					std::cerr<<"Oh! You are maybe a human!"<<std::endl,cnt++;
				else
					std::cerr<<"Hello, bot. You are arrested!"<<std::endl;
			}
			else
			{
				if(check(generator_arithmetic(3)))
					std::cerr<<"Oh! You are maybe a human!"<<std::endl,cnt++;
				else
					std::cerr<<"Hello, bot. You are arrested!"<<std::endl;
			}
		}
		if(cnt>=3)
			print_human();
		else
			print_bot();
	}
	else
	{
		cerr<<"type(0:arithmetic,1:normal):";
		cin>>op;
		cout<<"filename:";
		string name;
		cin>>name;
		cout<<"count:";
		int count;
		cin>>count;
		cerr<<"please wait..."<<endl;
		for(int i=1;i<=count;i++)
		{
			if(op)
				save(generator_normal(5),i,name);
			else
				save(generator_arithmetic(3),i,name);
			cerr<<"picture "<<i<<" generated"<<endl;
		}
	}

    return 0;
}
