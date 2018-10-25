
/* 情報工学科3年 学籍番号61610117 杉浦 圭祐 */
/* dijkstra.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NNODE       6
#define INF         INT_MAX

int LinkCost[NNODE][NNODE] = {
    {   0,   2,   5,   1, INF, INF },
    {   2,   0,   3,   2, INF, INF },
    {   5,   3,   0,   3,   1,   5 },
    {   1,   2,   3,   0,   1, INF },
    { INF, INF,   1,   1,   0,   2 },
    { INF, INF,   5, INF,   2,   0 }
};

/* 2つのノードが隣接しているかどうかを判定 */
int IsNeighbor(int node0, int node1);

/* ダイクストラのアルゴリズムの実行 */
void ShortestPathFirst(int u, int* dist, int* prev);

/* アルゴリズムの結果の表示 */
void PrintResult(int u, const int* dist, const int* prev);

int main(int argc, char** argv)
{
    int u;
    int dist[NNODE];
    int prev[NNODE];
    
    for (u = 0; u < NNODE; ++u) {
        ShortestPathFirst(u, dist, prev);
        PrintResult(u, dist, prev);
    }

    return EXIT_SUCCESS;
}

/* 2つのノードが隣接しているかどうかを判定 */
int IsNeighbor(int node0, int node1)
{
    return (LinkCost[node0][node1] < INF);
}

/* ダイクストラのアルゴリズムの実行 */
void ShortestPathFirst(int u, int* dist, int* prev)
{
    int nodeVisited[NNODE];
    int minDist;
    int v;
    int w;

    memset(nodeVisited, 0, sizeof(nodeVisited));
    nodeVisited[u] = 1;

    for (v = 0; v < NNODE; ++v) {
        if (IsNeighbor(v, u)) {
            dist[v] = LinkCost[u][v];
            prev[v] = u;
        } else {
            dist[v] = INF;
        }
    }

    while (1) {
        minDist = INF;
        w = -1;

        for (v = 0; v < NNODE; ++v) {
            if (!nodeVisited[v] && minDist > dist[v]) {
                minDist = dist[v];
                w = v;
            }
        }

        if (w == -1)
            break;

        nodeVisited[w] = 1;

        for (v = 0; v < NNODE; ++v) {
            if (!nodeVisited[v] && IsNeighbor(v, w)) {
                if (dist[v] > dist[w] + LinkCost[w][v]) {
                    dist[v] = dist[w] + LinkCost[w][v];
                    prev[v] = w;
                }
            }
        }
    }
}

/* アルゴリズムの結果を表示 */
void PrintResult(int u, const int* dist, const int* prev)
{
    int v;

    printf("root node: %c\n", 'A' + u);
    printf("\t");

    for (v = 0; v < NNODE; ++v)
        printf("[%c,%c,%d] ", 'A' + v, 'A' + prev[v], dist[v]);

    printf("\n");
}

