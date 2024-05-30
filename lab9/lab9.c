#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
void write_to_html(int n, int** graph, long long int* distances, int* path) {
    FILE* file = fopen("solution.html", "w");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(file, "<html>\n<head><title>Алгоритм Дейкстры</title>");
    fprintf(file, "<style>body { font-family: Arial, sans-serif; margin: 20px; }");
    fprintf(file, "h1 { color: #333; text-align: center; }");
    fprintf(file, "table { border-collapse: collapse; margin: 20px auto; }");
    fprintf(file, "td { padding: 10px; text-align: center; border: 3px solid #ccc; }");
    fprintf(file, "td.vertex { background-color:#F5F5DC ; }"); // Цвет для вершины 1
    fprintf(file, "td.yellow { background-color: #d36e70; color: #333; }</style>");
    fprintf(file, "</head>\n<body>\n");

    fprintf(file, "<h1>Алгоритм Дейкстры</h1>\n");

    fprintf(file, "<h2>Таблица Смежности:</h2>\n");
    fprintf(file, "<table border='1'>\n");
    fprintf(file, "<tr><td></td>");
    for (int i = 0; i < n; i++) {
        fprintf(file, "<td class='vertex'>%d</td>", i + 1); 
    }
    fprintf(file, "</tr>\n");

    for (int i = 0; i < n; i++) {
        fprintf(file, "<td class='vertex'>%d</td>", i + 1);
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != -1) {
                if (path[j] == i) {
                    fprintf(file, "<td class='yellow'>%d</td>", graph[i][j]);
                }
                else {
                    fprintf(file, "<td>%d</td>", graph[i][j]);
                }
            }
            else {
                fprintf(file, "<td>0</td>");
            }
        }
        fprintf(file, "</tr>\n");
    }
    fprintf(file, "</table>\n");

    fprintf(file, "<h2>Кумулятивные весы путей:</h2>\n");
    fprintf(file, "<table>\n");
    for (int i = 0; i < n; i++) {
        fprintf(file, "<tr>");
        fprintf(file, "<td>%lld</td>", distances[i]);
        fprintf(file, "</tr>");
    }
    fprintf(file, "</table>\n");

    fprintf(file, "</body>\n</html>");
    fclose(file);
}

void dijkstra(int n, int s, int** graph, long long int* distances, int* path, int* Arr_Count) {
    // Инициализация массива посещенных вершин
    int* visited = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        distances[i] = LLONG_MAX;
    }

    distances[s - 1] = 0;

    for (int i = 0; i < n - 1; i++) {
        long long int min_dist = LLONG_MAX;
        int next = 0;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && distances[j] < min_dist) {
                min_dist = distances[j];
                next = j;
            }
        }

        visited[next] = 1;

        for (int k = 0; k < n; k++) {
            if (!visited[k] && graph[next][k] != -1) {
                long long int new_dist = distances[next] + graph[next][k];
                Arr_Count[k] += Arr_Count[next];
                if (new_dist < distances[k]) {
                    distances[k] = new_dist;
                    path[k] = next;
                }
            }
        }
    }
    free(visited);
}

int main(int argc, char* argv[]) {
    int n, s, f, m;
    const int MAX_NODES = 5000;


    if (scanf("%d", &n) != 1 || n < 0 || n > MAX_NODES) {
        printf("bad number of vertices\n");

        return 0;
    }
    int** graph = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            graph[i][j] = -1;
        }
    }

    if (scanf("%d %d", &s, &f) != 2 || s < 1 || s > n || f < 1 || f > n) {
        printf("bad vertex\n");
        for (int i = 0; i < n; i++) {
            free(graph[i]);
        }
        free(graph);
        return 0;
    }

    int MAX_EDGES = (n * (n - 1)) / 2;

    if (scanf("%d", &m) != 1 || m < 0 || m > MAX_EDGES) {
        printf("bad number of edges\n");
        for (int i = 0; i < n; i++) {
            free(graph[i]);
        }
        free(graph);
        return 0;
    }



    int start, end, weight;
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d %d", &start, &end, &weight) != 3 || start < 1 || start > n || end < 1 || end > n || weight < 0 || weight > INT_MAX) {

            printf("bad length\n");
            for (int i = 0; i < n; i++) {
                free(graph[i]);
            }
            free(graph);
            return 0;
        }

        graph[start - 1][end - 1] = weight;
        graph[end - 1][start - 1] = weight;
    }

    int* Arr_Count = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        Arr_Count[i] = 0;
    }
    Arr_Count[s - 1] = 1;

    long long int* dist = (long long int*)malloc(n * sizeof(long long int));
    int* path = (int*)malloc(n * sizeof(int));

    dijkstra(n, s, graph, dist, path, Arr_Count);

    for (int i = 0; i < n; i++) {
        if (dist[i] < LLONG_MAX) {
            if (dist[i] > INT_MAX) {
                printf("INT_MAX+ ");
            }
            else {
                printf("%lld ", dist[i]);
            }
        }
        else {
            printf("oo ");
        }
    }
    printf("\n");

    if (dist[f - 1] == LLONG_MAX) {
        printf("no path\n");
    }
    else {
        int* path_nodes = (int*)malloc(n * sizeof(int));
        int current = f - 1;
        int length = 0;

        while (current != s - 1) {
            path_nodes[length++] = current;
            current = path[current];
        }
        path_nodes[length++] = s - 1;

        if (dist[f - 1] > INT_MAX && Arr_Count[f - 1] > 1) {
            printf("overflow\n");

        }
        else {
            for (int i = 0; i < length; i++) {
                printf("%d ", path_nodes[i] + 1);


            }
        }
        if (argc > 1 && strcmp(argv[1], "-t") == 0) {
           
                write_to_html(n, graph, dist, path);
                printf("\nSolution saved in solution.html\n");
            }
            
        free(path_nodes);
    }
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);


    free(dist);
    free(path);
    free(Arr_Count);
    return 0;
}
