#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include "BinaryNode.h"
#include "BinaryTreeAbstract.h"
#include "BinaryTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedException.h"


template < class ItemType>
class BinarySearchTree : public BinaryTree<ItemType> {

    protected :
        BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode);
        BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success);
        
        BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* nodePtr);        
        BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* subTreePtr, ItemType& inorderSuccessor);

        BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const ;

    public :
        BinarySearchTree();
        BinarySearchTree(const ItemType& rootItem);
        BinarySearchTree(const BinarySearchTree<ItemType>& tree);
        virtual ~BinarySearchTree();
        
        void setRootData( const ItemType& newData) const ; // throw (PrecondViolatedExcep);
        bool add( const ItemType& newEntry);
        bool remove( const ItemType& anEntry);
        ItemType getEntry( const ItemType& anEntry) const ; // throw (NotFoundException);
        bool contains( const ItemType& anEntry) const ;
                
        BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);
}; // end BinarySearchTree

#include "../src/BinarySearchTree.cpp"

#endif