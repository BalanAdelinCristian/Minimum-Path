#ifndef Code

struct MinHeapNode
{
	int v;
	int dist;
	struct MinHeapNode *parent;
};

struct MinHeap
{
	int size;	  /// Number of heap nodes present currently
	int capacity; /// Capacity of min heap
	int *pos;	  /// This is needed for decreaseKey()
	struct MinHeapNode **array;
};

#endif // Code
