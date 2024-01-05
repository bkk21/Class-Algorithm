#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

#define SWAP(a,b) {typeof(a) tmp; tmp=a; a=b; b=tmp;}

#define VERTICES 1000
#define INF 10000L
static int WG[VERTICES][VERTICES];

typedef struct
{
    int u, v; //(u,v)
    int w; //weight
} EDGE;

typedef struct {
    int v; //vertex
    int dist; //distance from Strating Point
} VQueue;

EDGE * readGraph(char *GRile, int *m, int *n);
int min_vertex(VQueue * Q, int endQ);
void print_path(int, int, int []);
char *city[]={
    "서울", "천안", "논산", "대전", "광주", "원주", "대구", "강릉", "포항", "부산"
};

void ShortPath(int p, int n)
{
    int i, u, v, vmin, pre[1000], endQ, weight;
    int Dvmin;
    VQueue *Q; //Vertex not in Treee; Q = set V - set T
    Q = (VQueue *) malloc (n * sizeof(VQueue));

    for( v = 0; v < n; v++)
    {
        Q[v].v = v;
        Q[v].dist = WG[p][v]; // (p, v)
        pre[v] = p;
    }

    Q[p].dist = 0;
    SWAP(Q[p], Q[n-1]);
    endQ = n - 1;

    while (endQ > 0) {
        vmin = min_vertex(Q, endQ);
        endQ--;

        Dvmin = Q[endQ].dist; // D[vmin]

        for(i = 0; i < endQ; i++) {
            int Dst;
            v = Q[i].v;
            Dst = Dvmin + WG[vmin][v];

            if (Dst < Q[i]. dist){
                Q[i].dist = Dst;
                pre[v] = vmin;
            }
        }
    }

    for (v = 0; v < n; v++) {
        if (v == p ) continue;
        print_path(p, v, pre);
        printf("\n");
    }
}

void print_path(int p, int v, int pre[])
{
    if (p == v ) {
        printf("%s", city[v]);
        return;
    }

    print_path(p, pre[v], pre);
    printf("->%s", city[v]);
}

EDGE *readGraph(char *GFile, int *m, int *n)
{
    FILE *fp;
    int i = 0;
    EDGE *Edges;
    if((fp = fopen(GFile, "r")) != NULL)
    {
        fscanf(fp, "%d%d", m, n);
        Edges = (EDGE *) malloc(sizeof(EDGE) * (*m));

        while (i < *m)
        {
            fscanf(fp, "%d%d%d", &Edges[i].u, &Edges[i].v, &Edges[i].w);
            i++;
        } 
    }
    else {
            perror("error : can't read file ");
    }
    return Edges;
}

int min_vertex(VQueue * Q, int endQ)
{
    int i, min_dist, imin;
    min_dist = INF;
    for(i = 0; i < endQ; i++)
        if(Q[i].dist < min_dist) {
            imin = i ;
            min_dist = Q[i].dist;
        }
    
    SWAP(Q[imin], Q[endQ-1]);
    return Q[endQ-1].v;
}

void main (int argc, char *argv[])
{
    int nedge, nvert, i, j, u, v, weight;
    EDGE *edgeG;

    edgeG = readGraph(argv[1], &nedge, &nvert);

    for(i = 0; i < nvert; i++)
        for(j = 0; j <nvert; j++)
            WG[i][j] = (i == j) ? 0 : INF;

    for(i = 0; i < nedge; i++) {
        u = edgeG[i].u;
        v = edgeG[i].v;
        WG[u][v] = WG[v][u] = edgeG[i].w;
    }
    ShortPath(0, nvert);
}