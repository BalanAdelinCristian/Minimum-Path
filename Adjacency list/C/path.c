#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "path.h"
#include "create_graph.h"

void printPath(int parent[], int child)
{
	if (parent[child] == - 1)
		return;

	printPath(parent, parent[child]);

	printf("%d ", child);
}

/// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
	struct MinHeapNode* minHeapNode = malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}

/// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap = malloc(sizeof(struct MinHeap));
	minHeap->pos = (int *)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

/// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

/// A standard function to heapify at given idx
/// This function also updates position of nodes when they are swapped.
/// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
            smallest = left;

	if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
            smallest = right;

	if (smallest != idx)
	{
		/// The nodes to be swapped in min heap
		struct MinHeapNode *smallestNode = minHeap->array[smallest];
		struct MinHeapNode *idxNode = minHeap->array[idx];

		/// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		/// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

/// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

/// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	/// Store the root node
	struct MinHeapNode* root = minHeap->array[0];

	/// Replace root node with last node
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	/// Update position of last node
	minHeap->pos[root->v] = minHeap->size-1;
	minHeap->pos[lastNode->v] = 0;

	/// Reduce heap size and heapify root
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

/// Function to decrease dist value of a given vertex v. This function
/// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
	/// Get the index of v in heap array
	int i = minHeap->pos[v];

	/// Get the node and update its dist value
	minHeap->array[i]->dist = dist;

	/// Travel up while the complete tree is not hepified.
	/// This is a O(Log n) loop
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
	{
		/// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		/// move to parent index
		i = (i - 1) / 2;
	}
}

bool isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

/// The algorithm used to determine the shortest path
void dijkstra(struct Graph* graph, int src, int dest)
{
	int V = graph->V;  /// Get the number of vertices in graph
	int dist[V];	   /// dist values used to pick minimum weight edge in cut
	int parent[V];

	struct MinHeap* minHeap = createMinHeap(V);

	/// Initialize min heap with all vertices. dist value of all vertices
	for (int v = 0; v < V; ++v)
	{
		dist[v] = INT_MAX;
		parent[src] = -1;
		minHeap->array[v] = newMinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}

	/// Make dist value of src vertex as 0 so that it is extracted first
	minHeap->array[src] = newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);

	/// initialization of the heap
	minHeap->size = V;
	/// In the following loop, min heap contains all nodes
	/// whose shortest distance is not yet finalized.
	while (!isEmpty(minHeap))
	{
		/// Extract the vertex with minimum distance value
		struct MinHeapNode* minHeapNode = extractMin(minHeap);

		int u = minHeapNode->v;
		/// Store the extracted vertex number
		/// Traverse through all adjacent vertices of u (the extracted
		/// vertex) and update their distance values
		struct AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->dest;
			/// If shortest distance to v is not finalized yet, and distance to v
			/// through u is less than its previously calculated distance
			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + pCrawl->weight;
				parent[v] = u;
				/// update distance value in min heap also
				decreaseKey(minHeap, v, dist[v]);
			}

			pCrawl = pCrawl->next;
		}
	}

	printf("%d --> %d \t%d\t %d ", src, dest, dist[dest], src);
	printPath(parent, dest);
}
