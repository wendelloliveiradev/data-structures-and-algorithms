#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//Structs
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

struct Bst {
    Node *root;
};

//Function Prototypes
void initializeBst(Bst *tree);
void countingParentheses(string &str, int &num_node_parent, int &num_element);
void entriesTreatment(Bst *tree, string &str, int &num_node_parent);
Node *createNode(int element, Node *left, Node *right);
void insertBst(Node *&reference_node, int element);
int heightBst(Node *reference_node);
void balanceNode(Node *reference_node);
int balancingFactor(Node *reference_node);
void LL(Node *reference_node);
void LR(Node *reference_node);
void RR(Node *reference_node);
void RL(Node *reference_node);
bool avlTree(Node *reference_node);
void printTreeRepresentation(Node *reference_node);

//global variable to save the type of rotation
//could easily be changed to local variable and
//be passed over functions by reference
string type_of_rotation;   

int main() {
    Bst *tree = new Bst;
    string str;
    bool is_avl;
    int height_bst, num_node_parent = -3, num_element = -1;

    initializeBst(tree);

    cin >> str;

    countingParentheses(str, num_node_parent, num_element);

    entriesTreatment(tree, str, num_node_parent);

    is_avl = avlTree(tree->root);

    height_bst = heightBst(tree->root);

    cout << height_bst << endl;

    printTreeRepresentation(tree->root);
    
    cout << endl;

    balanceNode(tree->root);

    cout << endl;

    delete tree;
    return 0;
}

void initializeBst (Bst *tree) {
    tree->root = NULL;
}

void countingParentheses(string &str, int &num_node_parent, int &num_element) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == 40 || str[i] == 41)
            num_node_parent++;

        if (str[i] == 'C')
            num_element++;

        if (num_node_parent == (num_element * 4))
            break;
    }
}

void entriesTreatment(Bst *tree, string &str, int &num_node_parent) {
    bool flag_side = true;
    int number = 0;

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == 40 || str[i] == 41)  //when the number of parentheses is equal to 0 change the subtree side
            num_node_parent--;
        if (num_node_parent == 0)
            flag_side = false;    //case 'flag_side' is true, put the elements in the left subtree, put it in the right subtree other ways

        char *aux = new char[10000];    //setting an auxiliar string with each element number
        if (str[i] == 40 && str[i + 1] == 67) {
            int j = i + 2;
            int k = 0;
            while (str[j] != 40 && str[j] != 41) {
                aux[k] = str[j];
                j++;
                k++;
            }
            aux[k + 1] = '\0';
            stringstream intValue(aux); //converting string to integer
            intValue >> number;

            if (tree->root == NULL)   //adds the first element to the tree
                tree->root = createNode(number, NULL, NULL);
            else {
                if (flag_side)                    
                    insertBst(tree->root->left, number);
                else                    
                    insertBst(tree->root->right, number);
            }
        }
        delete[] aux;
    }
}

Node *createNode (int element, Node *left, Node *right) {
    Node *aux = new Node;

    aux->key = element;
    aux->left = left;
    aux->right = right;

    return aux;
}

void insertBst(Node *&reference_node, int element) {

    if (reference_node == NULL) {
        reference_node = createNode(element, NULL, NULL);
        return;
    }
    if (element < reference_node->key) {
        if (reference_node->left != NULL)
            insertBst(reference_node->left, element);
        else
            reference_node->left = createNode(element, NULL, NULL);
    }
    else {
        if (reference_node->right != NULL)
            insertBst(reference_node->right, element);
        else
            reference_node->right = createNode(element, NULL, NULL);
    }
}

int heightBst (Node *reference_node) {

    if (reference_node == NULL)
        return -1;
    else {
        int left_subtree_size = heightBst(reference_node->left);
        int right_subtree_size = heightBst(reference_node->right);

        if (left_subtree_size < right_subtree_size)
            return right_subtree_size + 1;
        else
            return left_subtree_size + 1;
    }
}

int balancingFactor(Node *reference_node) {
    int left_subtree_height = 0;
    int right_subtree_height = 0;
    int factor;

    if (reference_node == NULL)
        return 0;

    left_subtree_height = heightBst(reference_node->left);
    right_subtree_height = heightBst(reference_node->right);

    factor = left_subtree_height - right_subtree_height;

    return factor;
}

void balanceNode (Node *reference_node) {
    int balance_a, balance_b, balance_c;

    balance_a = balancingFactor(reference_node);
    balance_b = balancingFactor(reference_node->left);
    balance_c = balancingFactor(reference_node->right);

    if (balance_a < -1) {
        if (balance_c < 0) {
            type_of_rotation = "RR";
            RR(reference_node);
        }
        else if (balance_c > 0) {
            type_of_rotation = "RL";
            RL(reference_node);
        }
    } else if (balance_a > 1){
        if (balance_b > 0) {
            type_of_rotation = "LL";
            LL(reference_node);
        }
        else if (balance_b < 0) {
            type_of_rotation = "LR";
            LR(reference_node);
        }
    }
}

//left left rotation
void LL(Node *reference_node) {
    int height_bst;

    Node *node_pa = reference_node;
    Node *node_pb = node_pa->left;
    node_pa->left = node_pb->right;
    node_pb->right = node_pa;

    height_bst = heightBst(node_pb);

    cout << type_of_rotation << endl;
    cout << height_bst << endl;
    printTreeRepresentation(node_pb);
}

//left right rotation
void LR(Node *reference_node) {
    int height_bst;

    Node *node_pa = reference_node;
    Node *node_pb = node_pa->left;
    Node *node_pc = node_pb->right;
    node_pb->right = node_pc->left;
    node_pc->left = node_pb;
    node_pa->left = node_pc->right;
    node_pc->right = node_pa;

    height_bst = heightBst(node_pc);

    cout << type_of_rotation << endl;
    cout << height_bst << endl;
    printTreeRepresentation(node_pc);
}

//right right rotation
void RR(Node *reference_node) {
    int height_bst;

    Node *node_pa;
    Node *node_pb;
    node_pa = reference_node;
    node_pb = node_pa->right;
    node_pa->right = node_pb->left;
    node_pb->left = node_pa;

    height_bst = heightBst(node_pb);

    cout << type_of_rotation << endl;
    cout << height_bst << endl;
    printTreeRepresentation(node_pb);
}

//right left rotation
void RL(Node *reference_node) {
    int height_bst;

    Node *node_pa = reference_node;
    Node *node_pb = node_pa->right;
    Node *node_pc = node_pb->left;
    node_pb->left = node_pc->right;
    node_pc->right = node_pb;
    node_pa->right = node_pc->left;
    node_pc->left = node_pa;

    height_bst = heightBst(node_pc);

    cout << type_of_rotation << endl;
    cout << height_bst << endl;
    printTreeRepresentation(node_pc);
}

bool avlTree(Node *reference_node) {
    int balance;

    balance = balancingFactor(reference_node);

    if (reference_node->left == NULL && reference_node->right == NULL)
        return true;
    if (balance <= 1)
        return true;

    return false;
}

void printTreeRepresentation(Node *reference_node) {
    if (reference_node != NULL) {
        cout << "(C" << reference_node->key;
        printTreeRepresentation(reference_node->left);
        printTreeRepresentation(reference_node->right);
        cout << ")";
    }
    else
        cout << "()";
}