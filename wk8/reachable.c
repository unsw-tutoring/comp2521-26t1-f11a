#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Set.h"

/**
 
dfs:
    initialise stack and visited array

    push src onto the stack

    while stack is not empty:
        pop v off the stack

        push all of v's unvisited neighbours
 */

void dfs(Graph g, int v, bool *visited) {
    visited[v] = true;

    for (int w = 0; w < GraphNumVertices(g); w++) {
        if (GraphIsAdjacent(g, v, w) && !visited[w]) {
            dfs(g, w, visited);
        }
    }
}

Set reachable(Graph g, Vertex src) {
    bool *visited = calloc(GraphNumVertices(g), sizeof(bool));

    dfs(g, src, visited);

    Set s = SetNew();

    for (int w = 0; w < GraphNumVertices(g); w++) {
        if (visited[w]) SetInsert(s, w);
    }
    return s;
}
