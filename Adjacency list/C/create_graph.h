#ifndef Graph
struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
	struct AdjListNode *prev;
};

/// A structure to represent an adjacency list
struct AdjList
{
	struct AdjListNode *head; /// pointer to head node of list
};

/// A structure to represent a graph.
struct Graph
{
	int V;
	struct AdjList* array;
};

#endif // Graph

