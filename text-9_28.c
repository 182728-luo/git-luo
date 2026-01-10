#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 32767
typedef struct Graph
{
	char* vexs;
	int** arcs;
	int vexNum;
	int arcNum;
}Graph;
typedef struct Edge {
	char vex;
	int weight;
}Edge;
Edge* initEdeg(Graph* G, int index)
{
	Edge* edge = (Edge*)malloc(sizeof(Edge) * G->vexNum);
	for (int i = 0; i < G->vexNum; i++)
	{
		edge[i].vex = G->vexs[index];
		edge[i].weight = G->arcs[index][i];
	}
	return edge;
}
int getMinEdge(Edge* edge, Graph* G)
{
	int index;
	int min = MAX;
	for (int i = 0; i < G->vexNum; i++)
	{
		if (edge[i].weight != 0 && min > edge[i].weight)
		{
			min = edge[i].weight;
			index = i;
		}
	}
	return index;
}
void prim(Graph* G, int index)
{
	int min;
	Edge* edge = initEdeg(G, index);
	for (int i = 0; i < G->vexNum - 1; i++)
	{
		min = getMinEdge(edge, G);
		printf("v%c --> v%c, weight = %d\n", edge[min].vex, G->vexs[min], edge[min].weight);
		edge[min].weight = 0;
		for (int j = 0; j < G->vexNum; j++)
		{
			if (G->arcs[min][j] < edge[j].weight)
			{
				edge[j].weight = G->arcs[min][j];
				edge[j].vex = G->vexs[min];
			}
		}
	}
}
Graph* initGraph(int vexNum)
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->vexs = (char*)malloc(sizeof(char) * vexNum);
	G->arcs = (int**)malloc(sizeof(int*) * vexNum);
	for (int i = 0; i < vexNum; i++)
	{
		G->arcs[i] = (int*)malloc(sizeof(int) * vexNum);
	}
	G->vexNum = vexNum;
	G->arcNum = 0;
	return G;
}
void createGraph(Graph* G, char* vexs, int* arcs)
{
	for (int i = 0; i < G->vexNum; i++)
	{
		G->vexs[i] = vexs[i];
		for (int j = 0; j < G->vexNum; j++)
		{
			G->arcs[i][j] = *(arcs + i * G->vexNum + j);
			if (G->arcs[i][j] != 0 && G->arcs[i][j] != MAX)
			{
				G->arcNum++;
			}
		}
	}
	G->arcNum /= 2;
}


void DFS(Graph* G, int* visited, int index)
{
	printf("%c ", G->vexs[index]);
	visited[index] = 1;
	for (int i = 0; i < G->vexNum; i++)
	{                                             ///////A  B  C  D  E
		if (G->arcs[index][i] > 0 && G->arcs[index][i] != MAX && !visited[i])/////A 0, 1, 1, 1, 0,
			/////B 1, 0, 1, 1, 1,
			/////C 1, 1, 0, 0, 0,
			/////D 1, 1, 0, 0, 1,
			/////E 0, 1, 0, 1, 0
		{
			DFS(G, visited, i);
		}
	}
}
int main()
{
	Graph* G = initGraph(6);
	int arcs[6][6] = {
		0,6,1,5,MAX,MAX,
		6,0,5,MAX,3,MAX,
		1,5,0,5,6,4,
		5,MAX,5,0,MAX,2,
		MAX,3,6,MAX,0,6,
		MAX,MAX,4,2,6,0
	};
	/*int* visited = (int*)calloc(5,sizeof(int) * G->vexNum);*/
	int* visited = (int*)calloc(6, sizeof(int));
	createGraph(G, "123456", (int*)arcs);
	DFS(G, visited, 0);
	printf("\n");
	prim(G, 0);
	return 0;
}