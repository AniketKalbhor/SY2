#include <stdio.h>
#include <stdlib.h>
#define INFINITY 9999

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Node* a[10];

int findMinDist(int dist[10], int vset[10], int v) {
    int min = INFINITY;
    int index = -1;

    for (int i = 0; i < v; i++) {
        if (vset[i] == 0 && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }

    return index;
}

void display(int dist[10], int v) {
    printf("Vertex\tDistance from source\n");
    for (int i = 0; i < v; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

void Dijkstras(int v, int src) {
    int dist[10], vset[10];
    int u;

    for (int i = 0; i < v; i++) {
        dist[i] = INFINITY;
        vset[i] = 0;
    }

    dist[src] = 0;

    for (int i = 0; i < v - 1; i++) {
        u = findMinDist(dist, vset, v);
        if (u == -1) {
            break;
        }
        vset[u] = 1;

        struct Node* p = a[u];
        while (p != NULL) {
            int vert = p->vertex;
            int weight = p->weight;

            if (!vset[vert] && dist[u] + weight < dist[vert]) {
                dist[vert] = dist[u] + weight;
            }

            p = p->next;
        }
    }

    display(dist, v);
}

int main() {
    struct Node* p;
    struct Node* newV;
    int u, v, vnum, weight, src;
    char ch;

    printf("Enter the number of vertices\n");
    scanf("%d", &vnum);

    for (int i = 0; i < vnum; i++) {
        a[i] = NULL;
    }

    printf("Enter starting vertex\n");
    scanf("%d", &src);

    do {
        printf("Enter edge (u, v)\n");
        scanf("%d %d", &u, &v);
        printf("Enter weight\n");
        scanf("%d", &weight);

        if (u < 0 || u >= vnum || v < 0 || v >= vnum || weight < 0) {
            printf("Invalid input. Please try again.\n");
            continue;
        }

        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = v;
        newV->weight = weight;
        newV->next = a[u];
        a[u] = newV;

        // Add edge from v to u
        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = u;
        newV->weight = weight;
        newV->next = a[v];
        a[v] = newV;

        printf("Add new edge? (y/n)\n");
        scanf(" %c", &ch);
    } while (ch == 'y');

    // Display adjacency list
    printf("Adjacency List\n");
    for (int i = 0; i < vnum; i++) {
        printf("Vertex %d -> ", i);
        p = a[i];
        while (p != NULL) {
            printf("%d, %d\t", p->vertex, p->weight);
            p = p->next;
        }
        printf("\n");
    }

    // Run Dijkstra's algorithm
    Dijkstras(vnum, src);

    return 0;
}
