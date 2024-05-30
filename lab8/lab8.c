#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PI 3.14159265358979323846
typedef struct {
    int start;
    int finish;
    int weight;
} Edges;

typedef struct {
    int parent;
    int rank;
} Subset;

/*void bubbleSort(Edges* edges, int m) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edges temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}
*/

void printSVG(Edges* edges, int n, int m, int* min_start, int* min_finish) {
    FILE* file = fopen("kruskal.svg", "w");
    if (file == NULL) {
        printf("Errors open file");
        return;
    }
    int R = 150;
    int cx1 = 250;
    int cy = 320;
    int cx2 = 750;

    fprintf(file, "<svg widht = \"1000pt\" height= \"800pt\" \n viewBox=\"0 0 1000 800\" \n "
        "xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n ");
    fprintf(file, "<text x=\"500\" y=\"50\" font-size=\"40\" text-anchor=\"middle\">Kruskal</text>\n");
    fprintf(file, "<text  x =\"250\" y=\"70\" font-size=\"15\" text-anchor=\"middle\">The original graph</text>\n");
    fprintf(file, "<text  x =\"750\" y=\"70\" font-size=\"15\" text-anchor=\"middle\">Shortest route</text>\n");

    for (int i = 0; i < m; i++) {
        int start = edges[i].start;
        int finish = edges[i].finish;
        int weight = edges[i].weight;

        double angleStart = 2 * PI * (start -1) / n;
        double angleFinish = 2 * PI * (finish-1) / n;
        //для первого графа

        int xstart1 = cx1 + R * cos(angleStart);
        int ystart1 = cy + R * sin(angleStart);


        int xfinish1 = cx1 + R * cos(angleFinish);
        int yfinish1 = cy + R * sin(angleFinish);

        int weightX1 = (xstart1 + xfinish1) / 2 + 7.5;
        int weightY1 = (ystart1 + yfinish1) / 2 - 20; 

        //для второго графа
        /* int R = 150;
    int cx1 = 250;
    int cy = 320;
    int cx2 = 750;*/
        int xstart2 = cx2 + R * cos(angleStart);
        int ystart2 = cy + R * sin(angleStart);

        int xfinish2 = cx2 + R * cos(angleFinish);
        int yfinish2 = cy + R * sin(angleFinish);

        int weightX2 = (xstart2 + xfinish2) / 2 + 7.5;
        int weightY2 = (ystart2 + yfinish2) / 2 - 20; 


        fprintf(file, "<line x1 =\"%d\" y1 =\"%d\" x2 =\"%d\" y2 =\"%d\" style= \"stroke:red; stroke-width:5\"/>\n ", xstart1, ystart1, xfinish1, yfinish1);
        fprintf(file, "<text text-anchor=\"middle\" x=\"%d\" y=\"%d\" font-family=\"technic\" >%d</text>\n",  weightX1, weightY1, weight);

        if (start == min_start[i] && finish == min_finish[i]) {
            fprintf(file,
                "<line x1 =\"%d\" y1 =\"%d\" x2 =\"%d\" y2 =\"%d\" style= \"stroke:#00BFFF; stroke-width:5\"/>\n ", xstart2, \
                ystart2, xfinish2, yfinish2);

            fprintf(file, "<text text-anchor=\"middle\" x=\"%d\" y=\"%d\" font-family=\"technic\" >%d</text>\n", \
                weightX2, weightY2, weight);
        }


    }
    for (int i = 0; i < n; i++) {
        double angle = 2 * PI * i / n;
        int x1 = cx1 + R * cos(angle);
        int y = cy + R * sin(angle);
        int x2 = cx2 + R * cos(angle);

        //for 1
        fprintf(file, "<g id=\"node%d\" class=\"node\">\n", i + 1);
        fprintf(file, "<ellipse style=\"fill:#FFF5EE;stroke:black;stroke-width:2;\" cx=\"%d\" cy=\"%d\" rx=\"10\" ry=\"10\"/>\n"\
            , x1, y);
        fprintf(file, "<text text-anchor=\"middle\" x=\"%d\" y=\"%d\" font-family=\"technic\" font-size=\"15\">%d</text>\n", \
            x1, y + 5, i + 1);
        fprintf(file, "</g>\n");
        //for 2
        fprintf(file, "<g id=\"node%d\" class=\"node\">\n", i + 1);
        fprintf(file, "<ellipse style=\"fill:#FFF5EE;stroke:black;stroke-width:2;\" cx=\"%d\" cy=\"%d\" rx=\"10\" ry=\"10\"/>\n"\
            , x2, y);
        fprintf(file, "<text text-anchor=\"middle\" x=\"%d\" y=\"%d\" font-family=\"technic\" font-size=\"15\">%d</text>\n", \
            x2, y + 5, i + 1);
        fprintf(file, "</g>\n");
    }

    fprintf(file, "</svg>\n");


    fclose(file);
}

int find_the_root(Subset* sub, int i) {
    if (sub[i].parent != i) {
        sub[i].parent = find_the_root(sub, sub[i].parent); // Path Compression
    }
    return sub[i].parent;
}

void work_rank(Subset* subset, int x, int y) {
    int xroot, yroot;
    xroot = find_the_root(subset, x);
    yroot = find_the_root(subset, y);
    if (subset[xroot].rank < subset[yroot].rank) {
        subset[xroot].parent = yroot;
    }
    else if (subset[xroot].rank > subset[yroot].rank) {
        subset[yroot].parent = xroot;
    }
    else {
        subset[yroot].parent = xroot;
        subset[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    Edges* edge1 = (Edges*)a;
    Edges* edge2 = (Edges*)b;
    return edge1->weight - edge2->weight;
}

int input_errors_N_M(int N, int M) {
    if (N < 0 || N > 5000) {
        printf("bad number of vertices\n");
        return 0;
    }
    if (M < 0 || M > N * (N + 1) / 2) {
        printf("bad number of edges\n");
        return 0;
    }



    return -1;
}

int input_errors_S_F_W(int N, int S, int F, int W) {
    if (S < 1 || S > N || F < 1 || F > N) {
        printf("bad vertex\n");

        return 0;
    }


    if (W < 0 || W > INT_MAX) {
        printf("bad length\n");
        return 0;
    }

    return -1;
}


void Kruskal(Edges* edges, int n, int m, int* min_start, int* min_finish) {
    Edges* result = (Edges*)malloc(n * sizeof(Edges));
    int e = 0;
    int i = 0;
    qsort(edges, m, sizeof(Edges), compareEdges);

    Subset* subsets = (Subset*)malloc(n * sizeof(Subset));
    for (int v = 0; v < n; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    while (e < n - 1 && i < m) {
        Edges nextEdge = edges[i++];

        int x = find_the_root(subsets, nextEdge.start - 1);
        int y = find_the_root(subsets, nextEdge.finish - 1);

        if (x != y) {
            result[e++] = nextEdge;
            work_rank(subsets, x, y);

            min_start[e - 1] = nextEdge.start;
            min_finish[e - 1] = nextEdge.finish;
        }
    }

    if (e != n - 1) {
        printf("no spanning tree\n");
        free(result);
        free(subsets);
        return;
    }

    for (int j = 0; j < e; j++) {
        printf("%d %d\n", result[j].start, result[j].finish);
    }
    free(result);
    free(subsets);
}

int main(int argc, char* argv[]) {
    int N = 0, M = 0;
    if (scanf("%d %d", &N, &M) != 2 || !(input_errors_N_M(N, M))) {
        return 0;
    }

    Edges* edges = (Edges*)malloc(M * sizeof(Edges));
    int S = 0, F = 0, W = 0;
    for (int i = 0; i < M; i++) {
        if (scanf("%d %d %d", &S, &F, &W) != 3) {
            printf("bad number of lines\n");
            free(edges);
            return 0;
        }
        else if (!(input_errors_S_F_W(N, S, F, W))) {
            free(edges);

            return 0;
        }



        edges[i].start = S;
        edges[i].finish = F;
        edges[i].weight = W;
    }
    int* min_start = (int*)malloc(N * sizeof(int));
    int* min_finish = (int*)malloc(N * sizeof(int));
    Kruskal(edges, N, M, min_start, min_finish);
    if (argc == 2 && strcmp(argv[1], "-g") == 0) {
        printSVG(edges, N, M, min_start, min_finish);
        free(edges);
        free(min_start);
        free(min_finish);
        return 0;
    }
    free(edges);
    free(min_start);
    free(min_finish);
    return 0;
}
