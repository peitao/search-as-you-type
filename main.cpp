#include <iostream>
#include "utility.h"
#include "TrieIndex.h"
#include "ListIndex.h"

using namespace std;
void test_list_index();
int main (int argc, char const* argv[])
{
	//test_list_index();
	
	TrieIndex myIndex;
	myIndex.buildIndexFromFile("data/int_word.txt");
	myIndex.initTheSearchStat(2);
	myIndex.addOneChar('l');
	myIndex.addOneChar('i');
	myIndex.addOneChar('u');
	
	return 0;
}


void test_list_index()
{
	DEBUG_OUT("test_list_index() begin")
	ListIndex<int,int> listint;
	listint.initFromFile("data/int_int.txt");
	listint.outputToFile("data/int_int.txt.out");
	
	ListIndex<int,string> list1;
	list1.initFromFile("data/int_word.txt");
	list1.outputToFile("data/int_word.txt.out");
	
	ListIndex<string,string> list2;
	list2.initFromFile("data/word_word.txt");
	list2.outputToFile("data/word_word.txt.out");
}
