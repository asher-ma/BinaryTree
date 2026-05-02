/*
// ERR: This is getEntry() for a BST not a general binary tree
//      The general binary tree getEntry() must check every node
// Finds and returns searched value if found in tree
template <typename ItemType>
ItemType BinaryTree<ItemType>::getEntry( const ItemType& anEntry) const {
    BinaryNode<ItemType>* current = this->rootPtr;

    while (current != nullptr) {
        if (anEntry == current->getItem()) {
            return current->getItem();
        } else if (anEntry < current->getItem()){
            current = current->getLeftChildPtr();
        } else {
            current = current->getRightChildPtr();
        }
    }
    throw NotFoundExcep("Entry not found in tree");
}

// ERR: This is contains() for a BST not a general binary tree
//      The general binary tree contains() must check every node
// Returns true if tree contains searched entry, otherwise false
template <typename ItemType>
bool BinaryTree<ItemType>::contains( const ItemType& anEntry) const {
    BinaryNode<ItemType>* current = this->rootPtr;

    while (current != nullptr) {
        if (anEntry == current->getItem()) {
            return true;
        } else if (anEntry < current->getItem()){
            current = current->getLeftChildPtr();
        } else {
            current = current->getRightChildPtr();
        }
    }
    return false;
}
*/