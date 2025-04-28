#include<iostream>
using namespace std;

class Node {
public:
    string key, meaning;
    Node *left, *right;
    Node(string k, string m) : key(k), meaning(m), left(NULL), right(NULL) {}
};

class AVL {
    Node *root;
    
    int height(Node* n) {
        if (!n) return -1;
        return 1 + max(height(n->left), height(n->right));
    }
    
    int balanceFactor(Node* n) {
        return height(n->left) - height(n->right);
    }
    
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    
    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    
    Node* balance(Node* n) {
        if (!n) return n;
        int bf = balanceFactor(n);
        if (bf > 1) {
            if (balanceFactor(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (bf < -1) {
            if (balanceFactor(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }
    
    Node* insert(Node* n, string key, string meaning) {
        if (!n) return new Node(key, meaning);
        if (key < n->key) n->left = insert(n->left, key, meaning);
        else if (key > n->key) n->right = insert(n->right, key, meaning);
        else {
            cout << "Duplicate keyword not allowed.\n";
            return n;
        }
        return balance(n);
    }
    
    void inOrder(Node* n) {
        if (!n) return;
        inOrder(n->left);
        cout << n->key << " : " << n->meaning << endl;
        inOrder(n->right);
    }
    
    void reverseInOrder(Node* n) {
        if (!n) return;
        reverseInOrder(n->right);
        cout << n->key << " : " << n->meaning << endl;
        reverseInOrder(n->left);
    }
    
    Node* search(Node* n, string key) {
        if (!n || n->key == key) return n;
        if (key < n->key) return search(n->left, key);
        return search(n->right, key);
    }
    
    Node* findMin(Node* n) {
        while (n->left) n = n->left;
        return n;
    }
    
    Node* deleteNode(Node* n, string key) {
        if (!n) return NULL;
        if (key < n->key) n->left = deleteNode(n->left, key);
        else if (key > n->key) n->right = deleteNode(n->right, key);
        else {
            if (!n->left || !n->right) {
                Node* temp = n->left ? n->left : n->right;
                delete n;
                return temp;
            }
            Node* temp = findMin(n->right);
            n->key = temp->key;
            n->meaning = temp->meaning;
            n->right = deleteNode(n->right, temp->key);
        }
        return balance(n);
    }
    
public:
    AVL() : root(NULL) {}

    void addWord() {
        string k, m;
        cout << "Enter keyword: ";
        cin >> k;
        cout << "Enter meaning: ";
        cin >> m;
        root = insert(root, k, m);
    }

    void display() {
        cout << "\nAscending order:\n";
        inOrder(root);
        cout << "\nDescending order:\n";
        reverseInOrder(root);
    }

    void findWord() {
        string k;
        cout << "Enter keyword to search: ";
        cin >> k;
        if (search(root, k)) cout << "Keyword found.\n";
        else cout << "Keyword not found.\n";
    }

    void removeWord() {
        string k;
        cout << "Enter keyword to delete: ";
        cin >> k;
        root = deleteNode(root, k);
        cout << "Keyword deleted (if it existed).\n";
    }

    void updateWord() {
        string k;
        cout << "Enter keyword to update: ";
        cin >> k;
        Node* found = search(root, k);
        if (found) {
            cout << "Current meaning: " << found->meaning << endl;
            cout << "Enter new meaning: ";
            cin >> found->meaning;
            cout << "Meaning updated.\n";
        } else {
            cout << "Keyword not found.\n";
        }
    }

    void maxComparisons() {
        cout << "Maximum comparisons needed: " << height(root) + 1 << endl;
    }
};

int main() {
    AVL tree;
    int choice;
    
    do {
        cout << "\n==== AVL Tree Dictionary ====";
        cout << "\n1. Insert keyword";
        cout << "\n2. Display keywords";
        cout << "\n3. Search keyword";
        cout << "\n4. Delete keyword";
        cout << "\n5. Update meaning";
        cout << "\n6. Max comparisons";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: tree.addWord(); break;
            case 2: tree.display(); break;
            case 3: tree.findWord(); break;
            case 4: tree.removeWord(); break;
            case 5: tree.updateWord(); break;
            case 6: tree.maxComparisons(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
