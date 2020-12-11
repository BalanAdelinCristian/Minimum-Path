from create_graph import *
from path import *

if __name__ == '__main__':

    g = Graph();


    start = 0;
    stop = 4;
    g.add_vertex(0);
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);
    g.add_vertex(5);
    g.add_vertex(6);
    g.add_vertex(7);
    g.add_vertex(8);

    g.add_edge(0, 1, 4);  
    g.add_edge(0, 7, 8);
    g.add_edge(1, 2, 8);
    g.add_edge(1, 7, 11);
    g.add_edge(2, 3, 7); 
    g.add_edge(2, 8, 2);
    g.add_edge(2, 5, 4);
    g.add_edge(3, 4, 9);
    g.add_edge(3, 5, 14); 
    g.add_edge(4, 5, 10);
    g.add_edge(5, 6, 2);
    g.add_edge(6, 7, 1);
    g.add_edge(6, 8, 6);
    g.add_edge(7, 8, 7);

    print(start, '''-->''', stop);
    dijkstra(g, g.get_vertex(start), g.get_vertex(stop)); 

    target = g.get_vertex(stop);
    path = [g.get_vertex(stop).get_id()];
    shortest(target, path);
    print(path[::-1]);