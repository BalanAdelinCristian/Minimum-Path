import heapq
maxint = 100000;

class Vertex:
    def __init__(self, node):
        self.id = node;
        self.adjacent = {};
        # Set distance to infinity for all nodes
        self.distance = maxint;
        # Mark all nodes unvisited        
        self.visited = False;  
        # Predecessor
        self.previous = None;

    # Adds a neighbor to a node
    def add_neighbor(self, neighbor, weight = 0):
        self.adjacent[neighbor] = weight;

    # Adds an edge between two nodes
    def get_connections(self):
        return self.adjacent.keys();  

    def get_id(self):
        return self.id;

    # Gets the weight of an edge
    def get_weight(self, neighbor):
        return self.adjacent[neighbor];

    def set_distance(self, dist):
        self.distance = dist;

    def get_distance(self):
        return self.distance;

    def set_previous(self, prev):
        self.previous = prev;

    # Sets the visit status
    def set_visited(self):
        self.visited = True;

    def __str__(self):
        return (self.id + [x.id for x in self.adjacent]);

class Graph:
    def __init__(self):
        self.vert_dict = {};
        self.num_vertices = 0;

    def __iter__(self):
        return iter(self.vert_dict.values());

    def add_vertex(self, node):
        self.num_vertices = self.num_vertices + 1;
        new_vertex = Vertex(node);
        self.vert_dict[node] = new_vertex;
        return new_vertex;

    def get_vertex(self, n):
        if(n in self.vert_dict):
            return self.vert_dict[n];
        else:
            return None;

    # Adds edges to graph
    def add_edge(self, frm, to, cost = 0):
        
        # Checks if the source vertex is present in graph
        if(frm not in self.vert_dict):
            self.add_vertex(frm);
        
        # Checks if the destination vertex is present in graph
        if(to not in self.vert_dict):
            self.add_vertex(to);

        # Adds the edge
        self.vert_dict[frm].add_neighbor(self.vert_dict[to], cost);
        self.vert_dict[to].add_neighbor(self.vert_dict[frm], cost);


    def get_vertices(self):
        return self.vert_dict.keys();

    def set_previous(self, current):
        self.previous = current;

    def get_previous(self, current):
        return self.previous;