#ifndef __UTILITY_H__
#define __UTILITY_H__

#define DEBUG

#ifdef DEBUG
#include <iostream>
#define DEBUG_OUT(a)	std::cout<<a<<std::endl;
#endif

#ifndef DEBUG
#define DEBUG_OUT(a) 
#endif

#define CHECK_FALSE(a,b)   if(a == false) std::cerr<<b<<std::endl;

#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::istream;
using std::ostream;
using std::string;
using std::stringstream;

template <class T1,class T2>
bool parserOneLineFromStream( istream & in , T1 & t, vector<T2> & vec)
{
	string line;
	if(getline(in,line))
	{
		stringstream ss(line);
		ss>>t;
		T2 tmp;
		while(ss>>tmp)
		{
			vec.push_back(tmp);
		}
		return true;
	}
	else return false;
}
template <class T1,class T2>
void outputOneLineToStream(ostream & out,const T1 & t,const vector<T2> & vec)
{
	out<<t<<" ";
	for(typename vector<T2>::const_iterator i = vec.begin(); i != vec.end(); i++)
	{
		out<<*i<<" ";
	}
	out<<"\n";
}
#endif /* __UTILITY_H__ */

















