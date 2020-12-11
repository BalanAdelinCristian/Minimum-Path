#include <stdbool.h>
#include <limits.h>
#define V 9

/// Determines the minimum distance
int minDistance(int dist[], bool Set[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (Set[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

/// Prints the found path
void printPath(int parent[], int j)
{
	if (parent[j] == - 1)
		return;

	printPath(parent, parent[j]);

	printf("%d ", j);
}

/// Determines the shortest path
void dijkstra(int graph[V][V], int src, int dest)
{
	int dist[V];
	bool Set[V];
	int parent[V];

	for (int i = 0; i < V; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX;
		Set[i] = false;
	}

	dist[src] = 0;
	for (int count = 0; count < V - 1; count++)
	{
		int u = minDistance(dist, Set);
		Set[u] = true;
		for (int v = 0; v < V; v++)
			if (!Set[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
	}

	printf("%d -> %d \t\t %d\t\t%d ", src, dest, dist[dest], src);
    printPath(parent, dest);
}
