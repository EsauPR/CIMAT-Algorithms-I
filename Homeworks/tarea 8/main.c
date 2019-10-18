/**
    ANSI C standard: c11
    Purpose: Finding Strongly Connected Components with Kosaraju's algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000

int G[MAX_NODES][MAX_NODES];
int GT[MAX_NODES][MAX_NODES];
int VISITED[MAX_NODES];

int STACK[MAX_NODES];
int NNODES;
int STACK_SIZE;
int NSCC = 0;

/* Kosaraju DFS algorithm */
void kosaraju_DFS(int node, int inverse) {
    if (!inverse) {
        VISITED[node] = 1;
    } else {
        VISITED[node] = NSCC;
    }

    for (int i = 0; i < NNODES; i++) {
        if (!inverse) {
            if (G[node][i] && !VISITED[i]) {
                kosaraju_DFS(i, inverse);
            }
        } else {
            if (GT[node][i] && !VISITED[i]) {
                kosaraju_DFS(i, inverse);
            }
        }
    }

    if (!inverse) {
        STACK[STACK_SIZE++] = node;
    }
}

/* Kosaraju algorithm */
void kosaraju() {
    // First pass of DFS
    for (int i = 0; i < NNODES; i++){
        if(!VISITED[i]) {
            kosaraju_DFS(i, 0);
        }
    }
    // Second pass of DFS
    memset(VISITED, 0, sizeof(int) * NNODES);
    for (int i = NNODES - 1; i >= 0; i--) {
        if (!VISITED[STACK[i]]) {
            NSCC ++;
            kosaraju_DFS(STACK[i], 1);
        }
    }
}

/* Print the total a componets assigned to each node */
void print_components() {
    printf("NSCC: %d\n", NSCC);
    for (int i = 0; i < NNODES; ++i) {
        printf("Node %d -> Componet: %d\n", i, VISITED[i]);
    }
}

int main(int argc, char const *argv[]) {
    int nconnections;
    scanf("%d %d", &NNODES, &nconnections);

    int u,v;
    for (int i = 0; i < nconnections; i++) {
        scanf("%d %d", &u, &v);
        G[u][v] = 1;
        GT[v][u] = 1;
    }

    kosaraju();
    print_components();

    return 0;
}
