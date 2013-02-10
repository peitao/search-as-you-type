#ifndef __TRIEBASE_H__
#define __TRIEBASE_H__
#include <ostream>
#include <list>
#include <utility>

using std::ostream;
using std::list;
using std::pair;

template <class Key,class KeyContainer,class DataType>
class TrieBase
{
public:
	typedef void * TrieNodeHandler;
	
	virtual void insert( const KeyContainer & keys, const DataType & data ) = 0; // KeyContainer::iterator i; *i is Key

	virtual void computeAndStoreIds()=0;
	
	virtual void outputToStreamByPlot(ostream & out ) = 0;
	
	virtual void getNDeepChildSet( TrieNodeHandler node , size_t cDeep ,size_t deep , list< pair < TrieNodeHandler,size_t> > & result ) = 0;

	virtual TrieNodeHandler getRootNodeHandler() = 0;
	
	virtual const Key & getNodeKey(TrieNodeHandler node) const = 0;
	
	virtual vector<TrieNodeHandler> getChildNodeHandlers(TrieNodeHandler node) = 0;
};


#endif /* __TRIEBASE_H__ */

