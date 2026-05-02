#include <iostream>
#include "BinaryTree.h"

void printItem(int& item) {
    std::cout << item << " ";
}

void printResult(const std::string& testName, bool passed) {
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << testName << "\n";
}

int main() {
    std::cout << "=== BinaryTree Test Suite ===\n\n";

    // -------------------------
    // Constructor / isEmpty
    // -------------------------
    std::cout << "-- Constructors / isEmpty --\n";
    {
        BinaryTree<int> empty;
        printResult("Default constructor: isEmpty()", empty.isEmpty());

        BinaryTree<int> single(42);
        printResult("Root constructor: not isEmpty()", !single.isEmpty());
        printResult("Root constructor: getRootData()", single.getRootData() == 42);
    }

    // -------------------------
    // add / getHeight / getNumberOfNodes
    // -------------------------
    std::cout << "\n-- add / getHeight / getNumberOfNodes --\n";
    {
        BinaryTree<int> tree;
        tree.add(1);
        tree.add(2);
        tree.add(3);
        tree.add(4);
        tree.add(5);

        printResult("getNumberOfNodes() == 5", tree.getNumberOfNodes() == 5);
        printResult("getHeight() >= 3",        tree.getHeight() >= 3);
        printResult("not isEmpty() after adds", !tree.isEmpty());
    }

    // -------------------------
    // contains / getEntry
    // -------------------------
    std::cout << "\n-- contains / getEntry --\n";
    {
        BinaryTree<int> tree;
        tree.add(10);
        tree.add(20);
        tree.add(30);

        std::cout << "  Testing contains(10)...\n";
        printResult("contains(10)", tree.contains(10));

        std::cout << "  Testing contains(20)...\n";
        printResult("contains(20)", tree.contains(20));

        std::cout << "  Testing contains(30)...\n";
        printResult("contains(30)", tree.contains(30));

        std::cout << "  Testing !contains(99)...\n";
        printResult("!contains(99)", !tree.contains(99));

        std::cout << "  Testing getEntry(10)...\n";
        printResult("getEntry(10) == 10", tree.getEntry(10) == 10);

        std::cout << "  Testing getEntry(99) throws...\n";
        bool threw = false;
        try {
            tree.getEntry(99);
        } catch (...) {
            threw = true;
        }
        printResult("getEntry(99) throws", threw);
    }

    // -------------------------
    // setRootData
    // -------------------------
    std::cout << "\n-- setRootData --\n";
    {
        BinaryTree<int> tree(5);
        tree.setRootData(99);
        printResult("setRootData(99)", tree.getRootData() == 99);
    }

    // -------------------------
    // remove
    // -------------------------
    std::cout << "\n-- remove --\n";
    {
        try {
            BinaryTree<int> tree;
            tree.add(1);
            tree.add(2);
            tree.add(3);
            tree.add(4);
            tree.add(5);

            int before = tree.getNumberOfNodes();
            bool removed = tree.remove(3);
            printResult("remove(3) returns true",         removed);
            printResult("getNumberOfNodes() decremented", tree.getNumberOfNodes() == before - 1);
            printResult("!contains(3) after remove",      !tree.contains(3));

            bool removedMissing = tree.remove(99);
            printResult("remove(99) returns false",       !removedMissing);
        } catch (...) {
            std::cout << "[ERROR] remove section threw an exception\n";
        }
    }

    // -------------------------
    // clear
    // -------------------------
    std::cout << "\n-- clear --\n";
    {
        BinaryTree<int> tree;
        tree.add(1);
        tree.add(2);
        tree.add(3);
        tree.clear();
        printResult("isEmpty() after clear()",          tree.isEmpty());
        printResult("getNumberOfNodes() == 0 after clear", tree.getNumberOfNodes() == 0);
    }

    // -------------------------
    // Traversals
    // -------------------------
    std::cout << "\n-- Traversals --\n";
    {
        BinaryTree<int> tree;
        tree.add(1);
        tree.add(2);
        tree.add(3);
        tree.add(4);
        tree.add(5);

        std::cout << "  Preorder:  "; tree.preorderTraverse(printItem);  std::cout << "\n";
        std::cout << "  Inorder:   "; tree.inorderTraverse(printItem);   std::cout << "\n";
        std::cout << "  Postorder: "; tree.postorderTraverse(printItem); std::cout << "\n";
    }

    // -------------------------
    // Copy constructor
    // -------------------------
    std::cout << "\n-- Copy constructor --\n";
    {
        BinaryTree<int> original;
        original.add(7);
        original.add(14);
        original.add(21);

        BinaryTree<int> copy(original);
        printResult("copy contains(7)",  copy.contains(7));
        printResult("copy contains(14)", copy.contains(14));
        printResult("copy contains(21)", copy.contains(21));

        // Modifying original should not affect copy
        original.remove(7);
        printResult("copy still contains(7) after original.remove(7)", copy.contains(7));
    }

    // -------------------------
    // operator=
    // -------------------------
    std::cout << "\n-- operator= --\n";
    {
        BinaryTree<int> a;
        a.add(5);
        a.add(10);

        BinaryTree<int> b;
        b.add(99);
        b = a;

        printResult("b contains(5) after assignment",   b.contains(5));
        printResult("b contains(10) after assignment",  b.contains(10));
        printResult("b !contains(99) after assignment", !b.contains(99));

        // Modifying a should not affect b
        a.remove(5);
        printResult("b still contains(5) after a.remove(5)", b.contains(5));

        // Self-assignment should not crash
        b = b;
        printResult("self-assignment survives", b.contains(10));
    }

    // -------------------------
    // Subtree constructor
    // -------------------------
    std::cout << "\n-- Subtree constructor --\n";
    {
        try {
            BinaryTree<int> left(2);
            BinaryTree<int> right(3);
            BinaryTree<int> tree(1, &left, &right);

            printResult("subtree root == 1",               tree.getRootData() == 1);
            printResult("subtree contains(2)",             tree.contains(2));
            printResult("subtree contains(3)",             tree.contains(3));
            printResult("subtree getNumberOfNodes() == 3", tree.getNumberOfNodes() == 3);
        } catch (...) {
            std::cout << "[ERROR] subtree constructor section threw an exception\n";
        }
    }

    std::cout << "\n=== Done ===\n";
    return 0;
}