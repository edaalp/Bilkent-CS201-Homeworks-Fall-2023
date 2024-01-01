//Eda Alparslan 22102334 Section 3
/** ADT sorted list: Link-based implementation.
@file LinkedSortedList.h */
#include <iostream>
#ifndef LINKED_SORTED_LIST_H
#define LINKED_SORTED_LIST_H
#include "SortedListInterface.h"
#include "Node.h"
#include <cassert>
using namespace std;
template < class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
private :
    Node<ItemType>* headPtr = nullptr; // Pointer to first node in the chain
    int itemCount; // Current count of list items
// Locates the node that is before the node that should or does
// contain the given entry.
// @param anEntry The entry to find.
// @return Either a pointer to the node before the node that contains
// or should contain the given entry, or nullptr if no prior node exists.
    Node<ItemType>* getNodeBefore( const ItemType& anEntry) const ;
// Locates the node at a given position within the chain.
    Node<ItemType>* getNodeAt( int position) const ;
// Returns a pointer to a copy of the chain to which origChainPtr points.
    Node<ItemType>* copyChain( const Node<ItemType>* origChainPtr);
public :
    LinkedSortedList<ItemType>();
    LinkedSortedList(const LinkedSortedList<ItemType>& aList);
    virtual ~LinkedSortedList();
    void insertSorted( const ItemType& newEntry);
    bool removeSorted( const ItemType& anEntry);
    int getPosition( const ItemType& newEntry) const;
// The following methods are the same as given in ListInterface:
    bool isEmpty() const ;
    int getLength() const ;
    bool remove( int position);
    void clear();
    ItemType getEntry( int position) const;
}; // end LinkedSortedList


















template < class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(){
    itemCount = 0;
    //headPtr == nullptr;
}
template < class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList( const LinkedSortedList<ItemType>& aList)
{
    headPtr = copyChain(aList.headPtr);
} // end copy constructor
template < class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::copyChain( const Node<ItemType>* origChainPtr)
{
    Node<ItemType>* copiedChainPtr;
    if (origChainPtr == nullptr)
    {
        copiedChainPtr = nullptr ;
        itemCount = 0;
    }
    else
    {
// Build new chain from given one
        Node<ItemType>* copiedChainPtr =
            new Node<ItemType>(origChainPtr->getItem());
        copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
        itemCount++;
    } // end if
    return copiedChainPtr;
} // end copyChain
template < class ItemType>
void LinkedSortedList<ItemType>::insertSorted( const ItemType& newEntry)
{
    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
    Node<ItemType>* prevPtr = getNodeBefore(newEntry);
    if (isEmpty() || (prevPtr == nullptr )) // Add at beginning
    {
        newNodePtr->setNext(headPtr);
        headPtr = newNodePtr;
    }
    else // Add after node before
    {
        Node<ItemType>* aftPtr = prevPtr->getNext();
        newNodePtr->setNext(aftPtr);
        prevPtr->setNext(newNodePtr);
    } // end if
    itemCount++;
} // end insertSorted
template < class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore( const ItemType& anEntry) const
{
    Node<ItemType>* curPtr = headPtr;
    Node<ItemType>* prevPtr = nullptr;

    if(curPtr != nullptr)
    while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
    {
        prevPtr = curPtr;
        curPtr = curPtr->getNext();

    } // end while
    return prevPtr;
} // end getNodeBefore

template < class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry( int position)const
{
// Enforce precondition
    bool ableToGet = (position >= 1) && (position <= itemCount);
    if (ableToGet)
    {
        Node<ItemType>* nodePtr = getNodeAt(position);
        return nodePtr->getItem();
    }
    else
    {
    } // end if
} // end getEntry

template < class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeAt( int position) const
{
// Debugging check of precondition
    assert ( (position >= 1) && (position <= itemCount) );
// Count from the beginning of the chain
    Node<ItemType>* curPtr = headPtr;
    for ( int skip = 1; skip < position; skip++)
        curPtr = curPtr->getNext();
    return curPtr ;
} // end getNodeAt

template < class ItemType>
bool LinkedSortedList<ItemType>::remove( int position)
{
bool ableToRemove = (position >= 1) && (position <= itemCount);
if (ableToRemove)
{
Node<ItemType>* curPtr = nullptr ;
if (position == 1)
{
// Remove the first node in the chain
curPtr = headPtr; // Save pointer to node
headPtr = headPtr->getNext();
}
else
{
// Find node that is before the one to delete
Node<ItemType>* prevPtr = getNodeAt(position - 1);
// Point to node to delete
curPtr = prevPtr->getNext();
// Disconnect indicated node from chain by connecting the
// prior node with the one after
prevPtr->setNext(curPtr->getNext());
} // end if
// Return node to system
curPtr->setNext( nullptr );
delete curPtr;
curPtr = nullptr ;
itemCount--; // Decrease count of entries
} // end if
return ableToRemove;
} // end remove


template < class ItemType>
void LinkedSortedList<ItemType>::clear()
{
while (!isEmpty())
remove(1);
} // end clear



template < class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList()
{
clear();
} // end destructor


template < class ItemType>
bool LinkedSortedList<ItemType>::removeSorted( const ItemType& anEntry)
{
bool ableToRemove = false ;
if (!LinkedSortedList<ItemType>::isEmpty())
{
int position = getPosition(anEntry);
ableToRemove = position > 0;
if (ableToRemove){
ableToRemove = LinkedSortedList<ItemType>::remove(position);
}
} // end if
return ableToRemove;
} // end removeSorted


template < class ItemType>
int LinkedSortedList<ItemType>::getPosition( const ItemType& anEntry) const
{
int position = 1;
int length = LinkedSortedList<ItemType>::getLength();
while ( (position <= length) &&
(anEntry > LinkedSortedList<ItemType>::getEntry(position)) )
{
position++;
} // end while
if ( (position > length) ||
(anEntry != LinkedSortedList<ItemType>::getEntry(position)) )
{
position = -position;
} // end if
return position;
} // end getPosition


template < class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const
{
    return (itemCount == 0);
}

template < class ItemType>
int LinkedSortedList<ItemType>::getLength() const
{
    return itemCount;
}
#endif
