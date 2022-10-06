#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>

#define USI unsigned short int

using namespace std;

void initializeCompsTable(unordered_map<USI, USI> &usercomps_table, USI &size);
void getStronglyConComp(list<USI> *adj_list, unordered_map<USI, USI> &uc_table, USI &size);
void dfsOrder(list<USI> *adj_list, USI v, bool *visited, stack<USI> &stack_comp);
list<USI> *transposeGraph(list<USI> *adj, USI &size);
void dfsComp(list<USI> *adj_list, int v, USI &const_v, bool visited[], unordered_map<USI, USI> &uc_table);
void isThereRelation(unordered_map<USI, USI> &uc_table, USI &user_a, USI &user_b);

list<USI> OUTPUT;

int main() {
    USI N, M, user_a, user_b;
    int P;
    list<USI> *adj_list;
    unordered_map<USI, USI> usercomps_table;
    usercomps_table.reserve(10000);

    cin >> N >> M;

    adj_list = new list<USI>[N];

    USI size = N+1;
    initializeCompsTable(usercomps_table, size);

    for (USI i = 0; i < M; i++) {
        cin >> user_a >> user_b;
        adj_list[user_a].push_back(user_b);
    }

    getStronglyConComp(adj_list, usercomps_table, N);

    cin >> P;

    for (int i = 0; i < P; ++i) {
        cin >> user_a >> user_b;
        isThereRelation(usercomps_table, user_a, user_b);
    }

    for (auto itr : OUTPUT)
        cout << itr << endl;

    return 0;
}

void initializeCompsTable(unordered_map<USI, USI> &usercomps_table, USI &size) {
    for (USI i = 0; i < size; ++i)
        usercomps_table[i] = -1;
}

void getStronglyConComp(list<USI> *adj_list, unordered_map<USI, USI> &uc_table, USI &size) {
    stack<USI> comp_stack;
    list<USI> *adj_list_t;

    bool *visited = new bool[size];
    for(USI i = 0; i < size; i++)
        visited[i] = false;

    for (USI i = 0; i < size; ++i)
        if (!visited[i])
            dfsOrder(adj_list, i, visited, comp_stack);

    adj_list_t = transposeGraph(adj_list, size);

    for(USI i = 0; i < size; i++)
        visited[i] = false;

    while (!comp_stack.empty()) {
        USI vertice = comp_stack.top();
        comp_stack.pop();

        if (!visited[vertice]) {
            USI const_v = vertice;
            dfsComp(adj_list_t, vertice, const_v, visited, uc_table);
        }
    }

    delete[] visited;
}

void dfsOrder(list<USI> *adj_list, USI v, bool *visited, stack<USI> &stack_comp) {
    visited[v] = true;

    list<USI>::iterator i;
    for(i = adj_list[v].begin(); i != adj_list[v].end(); ++i)
        if(!visited[*i])
            dfsOrder(adj_list, *i, visited, stack_comp);

    stack_comp.push(v);
}

list<USI> *transposeGraph(list<USI> *adj, USI &size) {
    auto *adj_aux = new list<USI>[size];
    for (USI j = 0; j < size; j++) {
        list<USI>::iterator i;

        for(i = adj[j].begin(); i != adj[j].end(); ++i)
            adj_aux[*i].push_back(j);
    }
    return adj_aux;
}

void dfsComp(list<USI> *adj_list, int v, USI &const_v, bool visited[], unordered_map<USI, USI> &uc_table) {
    visited[v] = true;

    uc_table[v] = const_v;

    list<USI>::iterator i;
    for (i = adj_list[v].begin(); i != adj_list[v].end(); ++i)
        if (!visited[*i])
            dfsComp(adj_list, *i, const_v, visited, uc_table);
}

void isThereRelation(unordered_map<USI, USI> &uc_table, USI &user_a, USI &user_b) {
    if (uc_table[user_a] == uc_table [user_b])
        OUTPUT.push_back(1);
    else
        OUTPUT.push_back(0);
}