#include <iostream>

using namespace std;

typedef struct Node {
    int n;
    struct Node* next;
} Node;

void dfs(Node** graph, int* components, int nodeNum, int component_no) {
    if (components[nodeNum] != -1)
        return;
    
    components[nodeNum] = component_no;
    Node *tmp = graph[nodeNum];
    
    if (tmp == nullptr)
        return;
    
    while (tmp != nullptr) {
        dfs(graph, components, tmp->n, component_no);
        tmp = tmp->next;
    }
    // traverse the graph and mark all nodes which belong to the component
}

int* count_components(Node** graph, int n) {
    // this array shows to which component each node belongs
    int* components = new int[n];
    // -1 means that node hasn't been visited yet
    for(int i=0; i<n; i++) components[i] = -1;
    // prepare components counter
    int counter = 0;
    // in loop: find unvisited node, call DFS/BFS
    for (int i = 0; i < n; i++) {
        dfs(graph, components, i, counter);
        counter++;
    }
    return components;
}

void clearAll(Node **graph, int n) {
    for (int i = 0; i < n; i++) {
        Node *tmp = graph[i];
        while (tmp != nullptr) {
            Node *bef = tmp;
            tmp = tmp->next;
            delete bef;
        }
    }
}

int main() {
    int n, k, p;
    cin >> n;
    Node **graph = new Node*[n];
    cin >> k;
    cin >> p;
    for (int i=0; i<k; i++) {
        Node *tmp1 = new Node, *tmp2 = new Node;
        int x, y;
        cin >> x;
        cin >> y;
        tmp1->n = y;
        tmp1->next = graph[x];
        graph[x] = tmp1;
        tmp2->n = x;
        tmp2->next = graph[y];
        graph[y] = tmp2;
    }
    int* components = count_components(graph, n);
    for (int i=0; i<p; i++) {
        int x, y;
        cin >> x;
        cin >> y;
        cout << (components[x] == components[y] ? "TAK" : "NIE") << endl;
    }
    clearAll(graph, n);
}
