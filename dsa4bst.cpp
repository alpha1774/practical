#include<iostream>
using namespace std;

class node {
public:
    node* left;
    node* right;
    int data;

    node(int val) {
        data = val;
        left = right = nullptr;
    }
    friend class BST;
};

class BST {
public:
    node* root;

    BST() {
        root = NULL;
    }

    // Insert method to insert nodes properly
    node* insert(node* n, int value) {
        if (n == nullptr) {
            return new node(value);
        }
        if (value < n->data) {
            n->left = insert(n->left, value);
        } else {
            n->right = insert(n->right, value);
        }
        return n;
    }

    // Main insert function that doesn't overwrite root
    void insertValue(int value) {
        root = insert(root, value); // Insert the value at the correct position
    }

    // In-order traversal
    void inorder(node* n) {
        if (n == nullptr) return;
        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }

    // Display the tree using in-order traversal
    void display() {
        inorder(root);
        cout << endl;
    }

    // Find the height (longest path) of the tree
    int longestPath(node* n) {
        if (n == nullptr) {
            return 0;
        }
        int leftHeight = longestPath(n->left);
        int rightHeight = longestPath(n->right);
        return max(leftHeight, rightHeight) + 1;
    }

    // Get the longest path (height) from root
    int getLongestPath() {
        return longestPath(root);
    }

    // Find the minimum value in the tree
    int findMinValue(node* n) {
        if (n == nullptr) {
            cout << "Tree is empty!" << endl;
            return -1;
        }
        while (n->left != nullptr) {
            n = n->left;
        }
        return n->data;
    }

    // Get the minimum value in the tree
    int getMinValue() {
        return findMinValue(root);
    }

    // Swap the left and right children of each node
    void swapChildren(node* n) {
        if (n == nullptr) return;
        node* temp = n->left;
        n->left = n->right;
        n->right = temp;
        swapChildren(n->left);
        swapChildren(n->right);
    }

    // Swap children from root
    void swapChildrenFromRoot() {
        swapChildren(root);
    }

    // Search for a value in the tree
    bool search(node* n, int value) {
        if (n == nullptr) {
            return false;
        }
        if (n->data == value) {
            return true;
        }
        if (value < n->data) {
            return search(n->left, value);
        } else {
            return search(n->right, value);
        }
    }

    // Search for a value from root
    bool searchFromRoot(int value) {
        return search(root, value);
    }
};

int main() {
    BST tree;
    int no, value;

    cout << "Enter number of nodes to insert into BST: ";
    cin >> no;

    cout << "Enter values to insert: ";
    for (int i = 0; i < no; i++) {
        cin >> value;
        tree.insertValue(value); // Use insertValue to maintain the tree structure correctly
    }

    cout << "BST in-order traversal: ";
    tree.display();

    cout << "Longest path from root (height): " << tree.getLongestPath() << endl;

    cout << "Minimum value in the tree: " << tree.getMinValue() << endl;

    tree.swapChildrenFromRoot();
    cout << "BST after swapping left and right children: ";
    tree.display();

    cout << "Enter value to search: ";
    cin >> value;
    if (tree.searchFromRoot(value)) {
        cout << "Value " << value << " found in the tree." << endl;
    } else {
        cout << "Value " << value << " not found in the tree." << endl;
    }

    return 0;
}
