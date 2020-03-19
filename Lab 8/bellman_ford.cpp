#include <iostream>
#include <climits>
#include <vector>
#include <utility>

using namespace std;

const int INF = INT_MAX;

typedef struct Node {
    Node *parent;
    vector <pair<Node *, int> > neighbours;
    int val, dist;
} Node;

Node *newNode(int val) {
    Node *n = new Node;
    n->val = val;
    n->dist = INF;
    n->parent = NULL;
    return n;
}

void addEdge(Node *u, Node *v, int w) {
    pair <Node *, int> edge(v, w);
    u->neighbours.push_back(edge);
}


bool bellmann_ford(Node **nodes, int n, Node *start) {

    start->dist = 0;
    bool change;
    for (int i = 1; i < n; i++) {
        change = true;
        for (int j = 0; j < n; j++) {
            for (vector<pair<Node *, int>>::iterator it = nodes[j]->neighbours.begin();
                 it != nodes[j]->neighbours.end(); it++) {
                if (nodes[j]->dist + it->second < it->first->dist) {
                    change = false;
                    it->first->dist = nodes[j]->dist + it->second;
                    nodes[it->first->val]->parent = it->first;
                }
            }
        }
        if (change)
            return true;
    }

    for (int i = 0; i < n; i++) {
        for (vector<pair<Node *, int>>::iterator it = nodes[i]->neighbours.begin();
             it != nodes[i]->neighbours.end(); it++) {
            if (nodes[i]->dist + it->second < it->first->dist) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int N, k, start, end;
    cin >> N >> k;
    Node *nodes[N];
    for (int i = 0; i < N; i++) nodes[i] = newNode(i);

    for (int i = 0; i < k; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(nodes[u], nodes[v], w);
    }

    cin >> start >> end;
    if (!bellmann_ford(nodes, N, nodes[start])) cout << "CYKL" << endl;
    else if (nodes[end]->dist < INF) cout << nodes[end]->dist << endl;
    else cout << "NIE" << endl;

    for(int i=0; i<N; i++) delete nodes[i];
}
