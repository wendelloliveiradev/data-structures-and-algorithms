#include <iostream>

using namespace std;

//Structs
struct Node {
    int balancing_factor;
    int key;
    struct Node *left;
    struct Node *right;
};

struct Bst {
    Node *root;
};

//Function Prototypes
void initializeBst(Bst *tree);
Node *createNode(int element, Node *left, Node *right);
void balancingFactorPerNode(Node *&reference_node);
bool searchElement(Node *reference_node, int element);
void searchAndInsert(Node *&reference_node, int element);
void searchAndRemove(Node *&reference_node, int element);
void removeAvl(Node *&reference_node);
void searchSmallest(Node *&reference_node, Node *&next);
void searchBiggest(Node *&reference_node, Node *&next);
int bstHeight(Node *reference_node);
int balancingFactor(Node *reference_node);
void balancingCheck(Node *&reference_node);
void balanceNode(Node *&reference_node);
void printAvl(Node *reference_node);

int main() {
    Bst *tree = new Bst;
    int number, element;
    bool has_element = false;

    initializeBst(tree);

    cin >> number;

    for (int i = 0; i < number; ++i) {  
        //insert elements in the AVL
        cin >> element;

        if (tree->root == NULL)
            tree->root = createNode(element, NULL, NULL);
        else
            searchAndInsert(tree->root, element);
    }

    number = 0;
    cin >> number;

    has_element = searchElement(tree->root, number);

    if (has_element) {  
        //case the element already is in the tree,
        //remove it, and rebalance the tree
        searchAndRemove(tree->root, number);
        balancingFactorPerNode(tree->root);
        balancingCheck(tree->root);
    }
    else {  
        //case not in the tree, insert it and
        //rebalance the tree
        searchAndInsert(tree->root, number);
        balancingFactorPerNode(tree->root);
        balancingCheck(tree->root);
    }

    printAvl(tree->root);

    delete tree;
    return 0;
}

void initializeBst (Bst *tree) {
    tree->root = NULL;
}

Node *createNode (int element, Node *left, Node *right) {
    Node *aux = new Node;

    aux->balancing_factor = 0;
    aux->key = element;
    aux->left = left;
    aux->right = right;

    return aux;
}

void balancingFactorPerNode (Node *&reference_node) {
    if (reference_node == NULL)
        return;
    else {
        reference_node->balancing_factor = balancingFactor(reference_node);
        balancingFactorPerNode(reference_node->left);
        balancingFactorPerNode(reference_node->right);
    }
}

int balancingFactor (Node *reference_node) {
    int left_subtree_height = 0;
    int right_subtree_height = 0;
    int factor;

    if (reference_node == NULL)
        return 0;

    left_subtree_height = bstHeight(reference_node->left);
    right_subtree_height = bstHeight(reference_node->right);

    factor = left_subtree_height - right_subtree_height;

    return factor;
}

bool searchElement(Node *reference_node, int element) {
    bool ret;

    if (reference_node == NULL)
        return false;
    
    if (reference_node->key == element)
        return true;
    
    else if (reference_node->key < element) {
        ret = searchElement(reference_node->right, element);
        return ret;
    }
    else {
        ret = searchElement(reference_node->left, element);
        return ret;
    }

    return ret;
}

void searchAndInsert (Node *&reference_node, int element) {
    if (reference_node == NULL)
        reference_node = createNode(element, NULL, NULL);

    else if (reference_node->key < element) {
        if (reference_node->right != NULL)
            searchAndInsert(reference_node->right, element);
        else
            reference_node->right = createNode(element, NULL, NULL);
    } else {
        if (reference_node->left != NULL)
            searchAndInsert(reference_node->left, element);
        else
            reference_node->left = createNode(element, NULL, NULL);
    }

    reference_node->balancing_factor = balancingFactor(reference_node);
    balancingCheck(reference_node);
}

void searchAndRemove (Node *&reference_node, int element) {
    if (reference_node == NULL)
        return;

    if (reference_node->key == element) {
        removeAvl(reference_node);
        if (reference_node != NULL) {
            reference_node->balancing_factor = balancingFactor(reference_node);
            balancingCheck(reference_node);
        }
        return;
    }
    else if (reference_node->key < element)
        searchAndRemove(reference_node->right, element);
    else
        searchAndRemove(reference_node->left, element);

    reference_node->balancing_factor = balancingFactor(reference_node);
    balancingCheck(reference_node);
}

void removeAvl(Node *&reference_node) {
    if (reference_node == NULL)
        return;

    if (reference_node->left == NULL && reference_node->right == NULL) {
        reference_node = reference_node->left;
        delete reference_node;
    }
    else if (reference_node->left != NULL && reference_node->right == NULL)
        searchBiggest(reference_node, reference_node->left);
    else
        searchSmallest(reference_node, reference_node->right);
}

void searchSmallest(Node *&reference_node, Node *&next) {
    if (next->left == NULL) {
        reference_node->key = next->key;
        next = next->right;
    } else
        searchSmallest(reference_node, next->left);
}

void searchBiggest(Node *&reference_node, Node *&next) {
    if (next->right == NULL) {
        reference_node->key = next->key;
        next = next->left;
    } else
        searchBiggest(reference_node, next->right);
}

int bstHeight(Node *reference_node) {
    if (reference_node == NULL)
        return -1;
    else {
        int left_subtree_height = bstHeight(reference_node->left);
        int right_subtree_height = bstHeight(reference_node->right);
        if (left_subtree_height < right_subtree_height)
            return right_subtree_height + 1;
        else
            return left_subtree_height + 1;
    }
}

void balancingCheck(Node *&reference_node) {
    if (reference_node == NULL)
        return;
    else if (reference_node->balancing_factor > 1 || reference_node->balancing_factor < -1) {
        balanceNode(reference_node);
        balancingFactorPerNode(reference_node);
    }

    //recursive calls of AVL
    balancingCheck(reference_node->left);
    balancingCheck(reference_node->right);
}

void balanceNode(Node *&reference_node) {   
    //Balance where it's needed
    if (reference_node->balancing_factor < -1) {
        if (reference_node->right->balancing_factor < 0) {  
            //rotation type RR (simple left rotation)
            Node *node_pa = reference_node;
            Node *node_pb = node_pa->right;
            node_pa->right = node_pb->left;
            node_pb->left = node_pa;
            reference_node = node_pb;
        }
        else if (reference_node->right->balancing_factor > 0) {   
            //rotation type RL (double left rotation)
            Node *node_pa = reference_node;
            Node *node_pb = node_pa->right;
            Node *node_pc = node_pb->left;
            node_pb->left = node_pc->right;
            node_pc->right = node_pb;
            node_pa->right = node_pc->left;
            node_pc->left = node_pa;
            reference_node = node_pc;
        }
    } else if (reference_node->balancing_factor > 1){
        if (reference_node->left->balancing_factor > 0) {   
            //rotation type LL (simple right rotation)
            Node *node_pa = reference_node;
            Node *node_pb = node_pa->left;
            node_pa->left = node_pb->right;
            node_pb->right = node_pa;
            reference_node = node_pb;
        }
        else if (reference_node->left->balancing_factor < 0) {   
            //rotation type LR (double right rotation)
            Node *node_pa = reference_node;
            Node *node_pb = node_pa->left;
            Node *node_pc = node_pb->right;
            node_pb->right = node_pc->left;
            node_pc->left = node_pb;
            node_pa->left = node_pc->right;
            node_pc->right = node_pa;
            reference_node = node_pc;
        }
    }
}

void printAvl(Node *reference_node) {
    if (reference_node != NULL) {
        cout << "(C" << reference_node->key;
        printAvl(reference_node->left);
        printAvl(reference_node->right);
        cout << ")";
    }
    else
        cout << "()";
}