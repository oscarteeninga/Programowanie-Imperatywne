#include <iostream>
using namespace std;

typedef struct point {
    int x, y;
} point;

typedef struct neighbours {
    int n;
    point elems[4];
} neighbours;

neighbours get_neighbours(int** labyrinth, int n, int m, point p) {
    // find (if exist) all neighbours of point p
    neighbours neighbours1 = {};
    neighbours1.n = 0;
    int tabX[4] = {p.x-1, p.x, p.x, p.x+1};
    int tabY[4] = {p.y, p.y+1, p.y-1, p.y};
    for (int i = 0; i < 4; i++) {
        if (tabX[i] >= 0 && tabX[i] < n && tabY[i] >= 0 && tabY[i] < m && labyrinth[tabX[i]][tabY[i]] == 1) {
            point point1 = {};
            point1.x = tabX[i];
            point1.y = tabY[i];
            neighbours1.elems[neighbours1.n] = point1;
            neighbours1.n++;
        }
    }
    return neighbours1;
    // (consider points: one above p, one below p, one on the left site and one on the right site)
    // use defined structures
}

bool dfs(int** graph, int n, int m, bool** visited, point p, point end) {
    // if p is already at the end - return true
    if (p.x == end.x && p.y == end.y) return true;
    // mark p visited
    visited[p.x][p.y] = true;
    // call recursively on every unvisited neighbour
    neighbours near = get_neighbours(graph, n, m, p);
    // if all calls finished fruitlessly - you didn't find exit
    for (int i = 0;i < near.n; i++) {
        if (!visited[near.elems[i].x][near.elems[i].y] && dfs(graph, n, m, visited, near.elems[i], end))
            return true;
    }
    return false;
}


int main() {
    int n, m;
    cin >> n;
    cin >> m;
    int **labyrinth = new int*[n];
    for(int i=0; i<n; i++) labyrinth[i] = new int[m];
    bool** visited = new bool*[n];
    for(int i=0; i<n; i++) visited[i] = new bool[m];
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> labyrinth[i][j];
        }
    }
    point start, end;
    cin >> start.x;
    cin >> start.y;
    cin >> end.x;
    cin >> end.y;
    cout << (dfs(labyrinth, n, m, visited, start, end) ? "TAK" : "NIE") << endl;
}
