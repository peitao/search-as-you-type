#ifndef __TRIENAIVEIMP_H__
#define __TRIENAIVEIMP_H__
#include <vector>
#include <utility>
using std::vector;
using std::pair;
#include "TrieBase.h"
template<class KeyType,class KeyContainer , class DataType>
class TrieNaiveNode
{
private:
	typedef vector< pair< KeyType, TrieNaiveNode* > > KeysTable;
	KeysTable mChildKeys;
	vector< DataType > * mLeafData;
	size_t mMin,mMax;
	KeyType mKey;
	pair<typename KeysTable::iterator , bool > getKeyPos( const KeyType & k )
	{
		for( typename KeysTable::iterator i = mChildKeys.begin(); i != mChildKeys.end(); i++ )
		{
			if( i->first == k) return make_pair(i,true);
			else if (i->first > k) return make_pair(i,false);
		}
		return make_pair(mChildKeys.end(),false);
	}
public:
	void dropTheTroubleWhenComputeNodeRange(size_t & seedId)
	{
		if ( mLeafData  &&  mChildKeys.size() != 0) mMin = seedId++;
	}
	void computeNodeRange(size_t & seedId)
	{
		if( mLeafData  &&  mChildKeys.size() != 0 ) 
		{
			mMax = mChildKeys.back().second->getNodeRange().second;
			return ;
		}
		else if ( mLeafData  &&  mChildKeys.size() == 0 ) 
		{
			mMin = mMax = seedId++;
		}
		else
		{
			mMin = mChildKeys.front().second->getNodeRange().first;
			mMax = mChildKeys.back().second->getNodeRange().second;
		}
		
	}
	const KeyType & getNodeKey() const
	{
		return mKey;
	}
	pair<size_t,size_t> getNodeRange() const
	{
		return pair<size_t,size_t>(mMin,mMax);
	}
	const vector< DataType > * getLeafData () const
	{
		return mLeafData;
	}
	TrieNaiveNode(const KeyType & k):mLeafData(0),mKey(k),mMin(0),mMax(0)
	{
		//DEBUG_OUT("New a TrieNaiveNode")
		//DEBUG_OUT(mKey)
	}
	~TrieNaiveNode()
	{
		if( mLeafData ) delete mLeafData;
	}
	TrieNaiveNode * getChildNode( const KeyType & key )
	{
		pair<typename KeysTable::iterator,bool> i = getKeyPos(key);
		if ( i.second == false ) return NULL;
		else return i.first->second;
	}
	void addLeafData( const DataType & data )
	{
		if( mLeafData )
		{	
			mLeafData -> push_back ( data );
		}
		else mLeafData = new vector< DataType > ( 1,data );
	}
	TrieNaiveNode * addChild(const KeyType & k , TrieNaiveNode * pNode)
	{
		pair<typename KeysTable::iterator,bool> i = getKeyPos(k);
		mChildKeys.insert( i.first, make_pair( k,pNode ) );
		return pNode;
	}
	vector<TrieNaiveNode *> getChildVector()
	{
		vector<TrieNaiveNode *> ret ;
		typename KeysTable::iterator i = mChildKeys.begin();
		for ( ; i != mChildKeys.end(); i++ )
		{
			ret.push_back(i->second);
		}
		return ret;
	}
	
};

template<class KeyType,class KeyContainer,class DataType>
class TrieNaiveImp : public TrieBase<KeyType,KeyContainer,DataType>
{
private:
	typedef typename TrieBase<KeyType,KeyContainer,DataType>::TrieNodeHandler TrieNodeHandler;
	typedef TrieNaiveNode<KeyType,KeyContainer,DataType> TrieNaiveNodeType;
	TrieNaiveNodeType * mRoot;

	pair<TrieNaiveNodeType *,typename KeyContainer::const_iterator> findFull( const KeyContainer & keys) // KeyContainer::iterator i; *i is Key
	{
		
		TrieNaiveNodeType * pNode = mRoot;
		typename KeyContainer::const_iterator i = keys.begin();
		for ( ; i != keys.end(); i++ )
		{
			TrieNaiveNodeType * cNode = pNode -> getChildNode( *i );
			
			if( cNode )	pNode = cNode;
			else return make_pair( pNode, i );
		}
		return make_pair( pNode, i );
	}
	TrieNaiveNodeType * newOneBranch( const KeyContainer & keys, typename KeyContainer::const_iterator i, TrieNaiveNodeType * pNode )
	{
		TrieNaiveNodeType * retNode = pNode;
		for ( ; i != keys.end() ; i++ )
		{
			retNode = retNode->addChild( *i , new TrieNaiveNodeType( *i ) );
		}
		return retNode;
	}
	void outputToStreamByPlotDo(ostream & out,TrieNaiveNodeType * pNode)
	{
		vector<TrieNaiveNodeType*>  child = pNode->getChildVector();
		if (pNode->getNodeKey())
		{
			out<<"\""<<pNode<<"\" "<<"["<<"label=\""<<pNode->getNodeKey();
			out<<"<"<<pNode<<">";
			out<<":("<<pNode->getNodeRange().first<<","<<pNode->getNodeRange().second<<")";
			
			if(pNode->getLeafData()) 
			out <<":"<<pNode->getLeafData()->size();
			out<<"\"";
			if(pNode->getLeafData()) 
			out <<" color = blue  style = filled";
			out<<"]\n";
		}
		for( size_t i = 0; i < child.size() ; i++ )
		{
			out<<"\""<<pNode<<"\" -> \""<<child[i]<<"\"\n";
			outputToStreamByPlotDo(out,child[i]);
		}
	}
	void computeAndStoreIdsDo (TrieNaiveNodeType * pNode, size_t & seedId)
	{
		pNode -> dropTheTroubleWhenComputeNodeRange( seedId );
		vector<TrieNaiveNodeType*>  child = pNode->getChildVector();
		for ( size_t i = 0; i < child.size(); i++ )
		{
			computeAndStoreIdsDo ( child[i] , seedId );
		}
		pNode -> computeNodeRange (seedId);
	}
public: 
	TrieNaiveImp(){
		mRoot = new TrieNaiveNodeType(KeyType());
	}	
	
	void insert( const KeyContainer & keys, const DataType & data ) // KeyContainer::iterator i; *i is Key
	{
		pair<TrieNaiveNodeType *,typename KeyContainer::const_iterator> ret = findFull( keys );
		TrieNaiveNodeType * pNode = ret.first;
		typename KeyContainer::const_iterator i = ret.second;
		pNode = newOneBranch( keys, i , pNode );
		pNode -> addLeafData( data );
		
	}
	void computeAndStoreIds()
	{
		size_t seedId = 1;
		computeAndStoreIdsDo(mRoot,seedId);
	}
	void outputToStreamByPlot(ostream & out)
	{
		out<<"digraph{\n";
		outputToStreamByPlotDo(out,mRoot);
		out<<"}\n";
	}
	void getNDeepChildSet( TrieNodeHandler node , size_t cDeep ,size_t deep , list< pair < TrieNodeHandler,size_t> > & result)
	{
		if ( cDeep > deep ) return ;
		TrieNaiveNodeType * pNode = ( TrieNaiveNodeType * ) node;
		result.push_back(make_pair(node,cDeep));
		vector<TrieNaiveNodeType*> child = pNode->getChildVector();
		for (size_t i = 0; i<child.size();i++)
		{
			getNDeepChildSet((TrieNodeHandler)child[i],cDeep+1,deep,result);
		}
	}
	TrieNodeHandler getRootNodeHandler()
	{
		return (TrieNodeHandler)mRoot;
	}
	const KeyType & getNodeKey(TrieNodeHandler node) const 
	{
		return ( (TrieNaiveNodeType *) node ) ->getNodeKey();
	}
	vector<TrieNodeHandler> getChildNodeHandlers(TrieNodeHandler node)
	{
		TrieNaiveNodeType * pNode = (TrieNaiveNodeType *) node;
		vector<TrieNaiveNodeType *> vec = pNode->getChildVector();
		vector<TrieNodeHandler> ret;
		for(size_t i = 0;i<vec.size();i++)
		{
			ret.push_back( (TrieNodeHandler)vec[i] );
		}
		
		return ret;
	}
};
#endif /* __TRIENAIVEIMP_H__ */



















