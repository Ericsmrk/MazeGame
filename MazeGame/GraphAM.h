//Lab 9 CSCI 115 Spring 2021
//Eric Smrkovsky
#pragma once
#include "Queue.h"
#include "PriorityQueue.h"
#include "Matrix.h"

enum class ColorNode {
	Visited, 
	Unvisited,
	Finished
};

class GraphAM{

public:
	GraphAM() : time(0), numVertices(0), edgeWeights(nullptr), current(nullptr), pathQ(nullptr), shortestPath(nullptr), listOfPrevIndexes(nullptr) {};
	GraphAM(int n);
	~GraphAM();
	int GetNumberVertices() { return numVertices; }
	int GetDegree(int u);//source == u, dest == v, w == weight value 
	int GetCurrentVertex(int u) { return current[u]; }
	int EdgeIndex(int u, int v);
	bool ExistEdge(int u, int v);
	double EdgeWeight(int u, int v);
	void SetDirectedEdge(int u, int v, double w);//sets to w
	void SetDirectedEdge(int u, int v);			 //sets to 1	
	void SetUndirectedEdge(int u, int v, double w); //sets to w
	void SetUndirectedEdge(int u, int v);			//sets to 1	
	void RemoveDirectedEdge(int u, int v);			//sets to zero
	void RemoveUndirectedEdge(int u, int v);		//sets to zero
	bool HasSelfLoops();
	bool IsUndirected();
	void Display();
	void DisplayGraphNoSpace();
	void DisplayConvertToChar();
	void DisplayDirectedEdges();
	void DisplayUndirectedEdges();
	void ShowArray(double Arr[], int size);
	void ShowArray(int Arr[], int size);
	//above functions tested with 'test1()' function in main
	void SetCurrentVertex(int u);
	bool GetNextAdjacent(int u, int &vout);
	ColorNode setColor(int num); //0=unvisited, 1=visited, 2=finished
	void DisplayMST(int* parent);

	//Search->Dijkstra
	void Dijkstra(int startVertex, double*& destinationVertex, int*& pi);
	void DisplayShortestPathsFound(double* d, int* p);
	Queue* DijkstrasRoute(int startV, int destV);
	
	//Search->DepththFirstSearch	
	void DepthFirstSearch();
	void DFSVisit(int u, ColorNode* color, int* discovery, int* finished, 
														   int* pi);
	void DFS(ColorNode*& color, int*& discovery, int*& finished, int*& pi);

	//Search->BreadthFirstSearch	
	void BreadthFirstSearch(int start);
	void BFS(int start, ColorNode*& color, int*& distance, int*& pi);
	void FindShortestPathBFS(int startV, int GoalV);
	void FSP_BFS(int startV, int goalV, ColorNode*& color, int*& distance,
														   int*& pi);
	//MST->Kruskal
	void MSTKruskal(int debug);	//improve note: start adding debugging when pos
	void Acyclic(int u, GraphAM& G, int* color, int* pi, int* back, int parent);
	bool IsAcyclic(int u, GraphAM& G);

	



private:
	int numVertices;		//number of vertices
	double* edgeWeights;	//weights of each edge		
	int* current;			//for traversals
	int time;				//keep track of timesteps id DFS algorithm
	Queue* pathQ;	//holds list of vertices to visit for shortest path 

	//for dijkstra
	double* shortestPath;
	int* listOfPrevIndexes;
};

