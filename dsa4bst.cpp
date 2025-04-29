#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BST {
private:
    node* root;

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

    void inorder(node* n) {
        if (n == nullptr) {
            return;
        }
        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }

    int longestPath(node* n) {
        if (n == nullptr) {
            return 0;
        }
        int leftDepth = longestPath(n->left);
        int rightDepth = longestPath(n->right);
        return max(leftDepth, rightDepth) + 1;
    }

    int findMin(node* n) {
        if (n == nullptr) {
            return -1; // or throw exception
        }
        while (n->left != nullptr) {
            n = n->left;
        }
        return n->data;
    }

    void swapChildren(node* n) {
        if (n == nullptr) {
            return;
        }
        swap(n->left, n->right);
        swapChildren(n->left);
        swapChildren(n->right);
    }

    // ✅ Updated search function to work even after swapping (simple traversal)
    bool search(node* n, int value) {
        if (n == nullptr) {
            return false;
        }
        if (n->data == value) {
            return true;
        }
        // Search both left and right subtrees
        return search(n->left, value) || search(n->right, value);
    }

public:
    BST() {
        root = nullptr;
    }

    void insertValue(int value) {
        root = insert(root, value);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    int longestPathFromRoot() {
        return longestPath(root);
    }

    int findMinValue() {
        return findMin(root);
    }

    void swapChildrenFromRoot() {
        swapChildren(root);
    }

    bool searchFromRoot(int value) {
        return search(root, value);
    }
};

int main() {
    BST tree;
    int n, value;

    cout << "Enter number of nodes to insert into BST: ";
    cin >> n;
    cout << "Enter values to insert: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        tree.insertValue(value);
    }

    cout << "BST in-order traversal: ";
    tree.display();

    cout << "Longest path from root (height): " << tree.longestPathFromRoot() << endl;
    cout << "Minimum value in the tree: " << tree.findMinValue() << endl;

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
