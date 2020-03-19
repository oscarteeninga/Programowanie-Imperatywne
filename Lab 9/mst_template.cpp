#include <cstdio>
#include <queue>

using namespace std;

struct edge
{
	int u, v;
	int s;
};

bool operator< (edge a, edge b)
{
	if (a.s > b.s)
		return true;
	else
		return false;
}


int find(int x, int* parent)
{
	while (parent[x] != x)x = parent[x];
	return x;
}

void unia(int x, int y, int* parent)
{
	int rx = find(x, parent);
	int ry = find(y, parent);

	if (ry != rx) {
		parent[ry] = rx;
	}
}

unsigned long long mst(priority_queue<edge> Q, int n)
{
	unsigned long long cost = 0;
	int *parent = new int[n + 1];

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}
	parent[0] = n;

	while (!Q.empty() && n>1) {
		edge temp = Q.top();
		if (find(temp.u, parent) != find(temp.v, parent)) {
			unia(temp.u, temp.v, parent);
			cost += temp.s;
			n--;
		}
		Q.pop();
	}
	return cost;
}

int main()
{
	int Z;
	scanf("%d", &Z);
	while (Z--)
	{
		int n, m;
		scanf("%d %d", &n, &m);

		edge temp;
		int u, v, s;

		priority_queue<edge> Q;

		for (int i = 0; i < m; i++)
		{
			scanf("%d %d %d", &u, &v, &s);
			temp.u = u;
			temp.v = v;
			temp.s = s;
			Q.push(temp);
		}

		unsigned long long cost = mst(Q, n);

		printf("%llu\n", cost);
	}
}
