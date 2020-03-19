#include <cstdio>
#include <queue>
//#include <iostream>
// #define DEBUG 1

using namespace std;

struct edge
{
	int u, v;
	int s;
};

bool operator< (edge a, edge b)
{
	if (a.s < b.s)
		return true;
	else
		return false;
}

void print_map(int **map, int n) {
#ifdef DEBUG
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
#endif
}

int find(int x, int* parent)
{
	while (parent[x] != x)x = parent[x];
	return x;
}

void unia(int x, int y, int* parent, int* rank)
{
	int rx = find(x, parent);
	int ry = find(y, parent);

	if (ry != rx) {
		if (rank[rx]>rank[ry]) {
			parent[ry] = rx;
		}
		else {
			parent[rx] = ry;
			if (rank[ry] == rank[rx])rank[ry]++;
		}
	}
}

void addEdges(int **map, int n, priority_queue<edge>& Q, int x, int y) {
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { 1,0,-1,0 };
	for (int i = 0; i<4; i++) {
		if (x + dx[i] >= 0 && x + dx[i]<n && y + dy[i] >= 0 && y + dy[i]<n && map[x + dx[i]][y + dy[i]] != -1) {
			edge e;
			e.u = x + dx[i];
			e.v = y + dy[i];
			e.s = map[x + dx[i]][y + dy[i]];
			map[x + dx[i]][y + dy[i]] = -1;
			Q.push(e);
		}
	}
}

int draught_calculator(int **map, int n, int k) {
	priority_queue<edge> Q;
	int drought = k;
	int actx = 0;
	int acty = 0;

	edge temp;
	temp.u = actx;
	temp.v = acty;
	temp.s = map[actx][acty];
	map[actx][acty] = -1;
	drought = min(drought, temp.s);
	addEdges(map, n, Q, actx, acty);

	while (!Q.empty()) {
		temp = Q.top();
		Q.pop();
		drought = min(drought, temp.s);
		if (n - 1 == temp.u && n - 1 == temp.v)return k - drought;
		addEdges(map, n, Q, temp.u, temp.v);
	}

	return -1;
}

int main()
{
	int Z;
	scanf("%d", &Z);
	while (Z--)
	{
		int n, k;
		scanf("%d %d", &n, &k);
		int **map = new int*[n];
		for (int i = 0; i < n; i++)
			map[i] = new int[n];

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		print_map(map, n);

		int result = draught_calculator(map, n, k);

		printf("%d\n", result);

		for (int i = 0; i < n; i++)
			delete[] map[i];
		delete[] map;

	}
}
