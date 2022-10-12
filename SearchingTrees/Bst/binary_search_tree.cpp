#include <iostream>

using namespace std;

//Structs
struct Node {
    int element;
    struct Node *left;
    struct Node *right;
};

struct Bst {
    Node *root;
    int size_bst;
};

//Function Prototypes
void initializeBst(Bst *tree);
Node *createNode(int element, Node *left, Node *right);
void insertBst(Bst *tree, Node *reference_node, int element);
bool search(Node *reference_node, int element);
void searchAndInsert(Bst *tree, Node *reference_node, int element);
void searchAndRemove(Bst *tree, Node *reference_node, Node *previous_node, int element);
void deleteFromBst(Bst *tree, Node *reference_node, Node *previous_node);
void searchSmallestRightSubtree(Bst *tree, Node *reference_node, Node *next_node, Node *previous_node);
void searchBiggestLeftSubtree(Bst *tree, Node *reference_node, Node *next_node, Node *previous_node);
int heightBst(Node *reference_node);

int main() {
    auto *tree = new Bst;
    int aux = 0;
    int height_bst = 0;
    bool is_element_tree = false;

    initializeBst(tree);

    while (true) {
        cin >> aux;
        if (aux == -1)
            break;
        if (tree->root == nullptr) {
            tree->root = createNode(aux, nullptr, nullptr);
            tree->size_bst++;
        }
        else
            insertBst(tree, tree->root, aux);
    }

    cin >> aux;

    height_bst = heightBst(tree->root);

    cout << tree->size_bst << " " << height_bst << endl;

    is_element_tree = search(tree->root, aux);

    if (is_element_tree) {
        searchAndRemove(tree, tree->root, tree->root, aux);
    } else
        searchAndInsert(tree, tree->root, aux);

    height_bst = heightBst(tree->root);

    if (tree->size_bst == 1)
        height_bst++;

    cout << tree->size_bst << " " << height_bst << endl;

    return 0;
}

void initializeBst(Bst *tree) {
    tree->root = nullptr;
    tree->size_bst = 0;
}

Node *createNode(int element, Node *left, Node *right) {
    auto *aux = new Node;

    aux->element = element;
    aux->left = left;
    aux->right = right;

    return aux;
}

bool search(Node *reference_node, int element) {
    bool ret;

    if (reference_node == nullptr)
        return false;
    if (reference_node->element == element)
        return true;
    else if (reference_node->element < element) {
        ret = search(reference_node->right, element);
        return ret;
    }
    else {
        ret = search(reference_node->left, element);
        return ret;
    }
}

void searchAndInsert(Bst *tree, Node *reference_node, int element) {
    if (reference_node == nullptr) {
        reference_node = createNode(element, nullptr, nullptr);
        tree->size_bst++;
    }
    else if (reference_node->element < element) {
        if (reference_node->right != nullptr)
            searchAndInsert(tree, reference_node->right, element);
        else {
            reference_node->right = createNode(element, nullptr, nullptr);
            tree->size_bst++;
        }
    } else {
        if (reference_node->left != nullptr)
            searchAndInsert(tree, reference_node->left, element);
        else {
            reference_node->left = createNode(element, nullptr, nullptr);
            tree->size_bst++;
        }
    }
}

void searchAndRemove(Bst *tree, Node *reference_node, Node *previous_node, int element) {
    if (reference_node != nullptr) {
        if (reference_node->element == element) {
            if (reference_node == previous_node)
                initializeBst(tree);
            else
                deleteFromBst(tree, reference_node, previous_node);
        }
        else if (reference_node->element < element)
            searchAndRemove(tree, reference_node->right, reference_node, element);
        else
            searchAndRemove(tree, reference_node->left, reference_node, element);
    }
}

void insertBst(Bst *tree, Node *reference_node, int element) {
    if (element < reference_node->element) {
        if (reference_node->left != nullptr)
            insertBst(tree, reference_node->left, element);
        else {
            reference_node->left = createNode(element, nullptr, nullptr);
            tree->size_bst++;
        }
    }
    else {
        if (reference_node->right != nullptr)
            insertBst(tree, reference_node->right, element);
        else {
            reference_node->right = createNode(element, nullptr, nullptr);
            tree->size_bst++;
        }
    }
}

void deleteFromBst(Bst *tree, Node *reference_node, Node *previous_node) {
    if (reference_node != nullptr) {
        if (reference_node->left == nullptr && reference_node->right == nullptr) {
            if (tree->size_bst == 1)
                initializeBst(tree);
            else {
                if (previous_node->left == reference_node)
                    previous_node->left = nullptr;
                else if (previous_node->right == reference_node)
                    previous_node->right = nullptr;

                tree->size_bst--;
            }
        }
        else if (reference_node->left != nullptr && reference_node->right == nullptr)
            searchBiggestLeftSubtree(tree, reference_node, reference_node->left, reference_node->left);
        else
            searchSmallestRightSubtree(tree, reference_node, reference_node->right, reference_node->right);
    }
}

void searchSmallestRightSubtree(Bst *tree, Node *reference_node, Node *next_node, Node *previous_node) {
    if (next_node->left == nullptr) {
        if (next_node == previous_node) {
            reference_node->element = next_node->element;
            reference_node->right = next_node->right;
            tree->size_bst--;
        } else {
            reference_node->element = next_node->element;
            reference_node->right = next_node->right;
            previous_node->left = nullptr;
            tree->size_bst--;
        }
    } else
        searchSmallestRightSubtree(tree, reference_node, next_node->left, next_node);
}

void searchBiggestLeftSubtree(Bst *tree, Node *reference_node, Node *next_node, Node *previous_node) {
    if (next_node->right == nullptr) {
        if (next_node == previous_node) {
            reference_node->element = next_node->element;
            reference_node->left = next_node->left;
            tree->size_bst--;
        } else {
            reference_node->element = next_node->element;
            reference_node->left = next_node->left;
            previous_node->right = nullptr;
            tree->size_bst--;
        }
    } else
        searchBiggestLeftSubtree(tree, reference_node, next_node->right, next_node);
}

int heightBst(Node *reference_node) {
    if (reference_node == nullptr)
        return 0;
    else {
        int left_subtree_height = heightBst(reference_node->left);
        int right_subtree_height = heightBst(reference_node->right);
        
        if (left_subtree_height < right_subtree_height)
            return right_subtree_height + 1;
        else
            return left_subtree_height + 1;
    }
}