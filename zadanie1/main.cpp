#include <iostream>

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    TreeNode<T>* insert(TreeNode<T>* node, const T& value);
    TreeNode<T>* remove(TreeNode<T>* node, const T& value);
    TreeNode<T>* findMin(TreeNode<T>* node);
    void inOrder(TreeNode<T>* node);
    void destroyTree(TreeNode<T>* node);

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const T& value);
    void remove(const T& value);
    void printInOrder();
    bool search(const T& value);
    ~BinarySearchTree();
};

template <typename T>
TreeNode<T>* BinarySearchTree<T>::insert(TreeNode<T>* node, const T& value) {
    if (node == nullptr)
        return new TreeNode<T>(value);

    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);

    return node;
}

template <typename T>
void BinarySearchTree<T>::insert(const T& value) {
    root = insert(root, value);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::remove(TreeNode<T>* node, const T& value) {
    if (node == nullptr)
        return node;

    if (value < node->data)
        node->left = remove(node->left, value);
    else if (value > node->data)
        node->right = remove(node->right, value);
    else {
        if (node->left == nullptr) {
            TreeNode<T>* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            TreeNode<T>* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode<T>* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }

    return node;
}

template <typename T>
void BinarySearchTree<T>::remove(const T& value) {
    root = remove(root, value);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::findMin(TreeNode<T>* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

template <typename T>
void BinarySearchTree<T>::inOrder(TreeNode<T>* node) {
    if (node == nullptr)
        return;

    inOrder(node->left);
    std::cout << node->data << " ";
    inOrder(node->right);
}

template <typename T>
void BinarySearchTree<T>::printInOrder() {
    inOrder(root);
    std::cout << std::endl;
}

template <typename T>
bool BinarySearchTree<T>::search(const T& value) {
    TreeNode<T>* current = root;

    while (current != nullptr) {
        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
        else
            return true; // Найдено
    }

    return false; // Не найдено
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    destroyTree(root);
}

template <typename T>
void BinarySearchTree<T>::destroyTree(TreeNode<T>* node) {
    if (node == nullptr)
        return;

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main() {
    BinarySearchTree<int> bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    std::cout << "In-order traversal: ";
    bst.printInOrder();

    bst.remove(30);

    std::cout << "In-order traversal after removing 30: ";
    bst.printInOrder();

    std::cout << "Searching for 60: " << (bst.search(60) ? "Found" : "Not found") << std::endl;
    std::cout << "Searching for 30: " << (bst.search(30) ? "Found" : "Not found") << std::endl;

    return 0;
}