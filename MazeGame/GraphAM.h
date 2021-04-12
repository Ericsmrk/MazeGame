#pragma once
class GraphAM{

public:
	GraphAM() : numVertices(0), edgeWeights(nullptr), current(nullptr) {};
	GraphAM(int n);
	~GraphAM();
	int GetNumberVertices() { return numVertices; }
	int GetDegree(int u);//source == u, dest == v, w == weight value 
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
	void DisplayDirectedEdges();
	void DisplayUndirectedEdges();
	void ShowArray(double Arr[], int size);
	void ShowArray(int Arr[], int size);

private:
	int numVertices;		//number of vertices
	double* edgeWeights;	//weights of each edge		
	int* current;		
};

