#include <iostream>
#include <climits>
#include <utility>
#include <vector>
#include <queue>

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
}

void addEdge(Node *u, Node *v, int w) {
    pair <Node *, int> u_edge(v, w);
    pair <Node *, int> v_edge(u, w);
    u->neighbours.push_back(u_edge);
    v->neighbours.push_back(v_edge);
}

auto cmp = [](Node *x, Node *y) { return x->dist > y->dist; };

void relax(Node *u, Node *v, int weight) {
    if(v->dist>u->dist+weight){
        v->dist=u->dist+weight;
        v->parent=u;
    }
}

int getMin(Node **nodes, bool set[], int n){
    int min=INF;
    int index=0;
    for(int i=0;i<n;i++){
        if(!set[i]&&nodes[i]->dist<min){
            index=i;
            min=nodes[index]->dist;
        }
    }
    return index;
}



void dijkstra(Node **nodes, int n, Node *start) {
    priority_queue <Node *, vector<Node *>, decltype(cmp)> queue(cmp);
    bool set[n];
    for(int i=0;i<n;i++){
        set[i]=false;
        nodes[i]->parent=NULL;
        nodes[i]->dist=INF;
    }
    start->dist=0;
    for(int i=0;i<n;i++){
        int index=getMin(nodes,set,n);
        set[index]=true;
        Node *u=nodes[index];
        for(int k=0;k<u->neighbours.size();k++){
                if(!set[k]) {
                    relax(u,u->neighbours[k].first,u->neighbours[k].second);
                }
        }
    }
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
    dijkstra(nodes, N, nodes[start]);
    cout << nodes[end]->dist << endl;

    for (int i=0; i<N; i++) delete nodes[i];
}
