#include <iostream>
#include "BinarySearchTree.h"

void printItem(int& item) {
    std::cout << item << " ";
}

int main() {
    BinarySearchTree<int> bst;

    // Insertions
    std::cout << "Inserting: 30 20 40 10 50\n";
    bst.add(30);
    bst.add(20);
    bst.add(40);
    bst.add(10);
    bst.add(50);

    // Traversals
    std::cout << "\nInorder traversal:   "; bst.inorderTraverse(printItem);   std::cout << "\n";
    std::cout << "Preorder traversal:  "; bst.preorderTraverse(printItem);  std::cout << "\n";
    std::cout << "Postorder traversal: "; bst.postorderTraverse(printItem); std::cout << "\n";

    // Search
    int searchKey = 40;
    std::cout << "\nSearch " << searchKey << ": "
              << (bst.contains(searchKey) ? "Found" : "Not found") << "\n";

    searchKey = 99;
    std::cout << "Search " << searchKey << ": "
              << (bst.contains(searchKey) ? "Found" : "Not found") << "\n";

    // Deletion
    int removeKey = 20;
    std::cout << "\nRemove " << removeKey << ": "
              << (bst.remove(removeKey) ? "Success" : "Failed") << "\n";

    std::cout << "Inorder after removal: "; bst.inorderTraverse(printItem); std::cout << "\n";

    // Clear
    std::cout << "\nClearing tree...\n";
    bst.clear();
    std::cout << "isEmpty: " << (bst.isEmpty() ? "true" : "false") << "\n";

    return 0;
}