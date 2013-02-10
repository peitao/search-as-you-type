#ifndef __LISTINDEX_H__
#define __LISTINDEX_H__

#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "utility.h"

using std::vector;
using std::pair;
using std::string;
using std::stringstream;
using std::istream;
using std::ostream;

template<class KeyType,class ValueType>
class ListIndex
{

protected:
typedef vector< pair< KeyType, vector<ValueType> > > MList;
	MList mList;
protected:
	void pushAListFast(const KeyType & key,vector<ValueType> & plist)
	{
		mList.push_back( typename MList::value_type( key, vector<ValueType>() ) );
		mList.back().second.swap(plist);
	}
public:
	void initFromFile(const char * filename)
	{
		std::ifstream fin(filename);
		CHECK_FALSE(fin,string()+"Fail to open file \" "+filename+" \" in \"initFromFile\" ")
		initFromStream(fin);
						
	}
	void initFromStream(istream & in)
	{
		while(1)
		{
			KeyType key;
			vector<ValueType> tempList;
			if( ! parserOneLineFromStream( in, key, tempList ) ) break;
			pushAListFast( key, tempList );
		}
	}
	void outputToStream(ostream & out)
	{
		for( typename MList::iterator i = mList.begin(); i != mList.end(); i++ )
		{
			outputOneLineToStream( out, i->first, i->second );
		}
	}
	void outputToFile(const char * filename)
	{
		std::ofstream fout(filename);
		CHECK_FALSE(fout,string()+"Fail to open file \" "+filename+" \" in \"outputToFile\" ")
		outputToStream(fout);
	}
};

#endif /* __LISTINDEX_H__ */



























