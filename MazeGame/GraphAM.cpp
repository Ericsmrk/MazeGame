#include "GraphAM.h"
#include <iostream>
using namespace std;

//Simple display array function for double type
void GraphAM::ShowArray(double arr[], int size){
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
}

//Simple display array function for integer type
void GraphAM::ShowArray(int arr[], int size) {
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
}

//Constructor for graph object, creates a n * n matrix for edges and array of 
//size n for the graphs vertices // numVertices == n
GraphAM::GraphAM(int n) { 
	numVertices = n;
	int Msize = numVertices * numVertices;
	edgeWeights = new double[Msize];//create array dynamically 
	for (int i = 0; i < Msize; i++)//initialize all edges to zero
		edgeWeights[i] = 0;
	current = new int[numVertices];//create array dynamically 
	for (int i = 0; i < numVertices; i++)//initialize all elements to zero
		current[i] = 0;
	//Show for debugging purposes
	/*cout << "edgeWeights: ";
	ShowArray(edgeWeights, Msize);
	cout << "current: ";
	ShowArray(current, numVertices);*/
}

//Basic destructor
GraphAM::~GraphAM(){
	cout << "destructor";
	delete[] edgeWeights;
	delete[] current;
}

//Returns the out degree of a vertex (number of paths out of a vertex)
int GraphAM::GetDegree(int u){
	int numPaths = 0;
	for (int v = 0; v < numVertices; v++)
		if (ExistEdge(u, v))
			numPaths++;
	return numPaths;
}

//Returns the index of the edge travelled on when going from source to dest
int GraphAM::EdgeIndex(int u, int v){ //source == u, dest == v
	return u * numVertices + v;
}

//Returns true if the edge exists in the graph
bool GraphAM::ExistEdge(int u, int v){
	double weight = EdgeWeight(u, v);
	return (weight == 0 ? 0 : 1);
}

//Returns the weight (or cost) of going from u to v on the graph
double GraphAM::EdgeWeight(int u, int v){
	int index = EdgeIndex(u, v);
	return edgeWeights[index];
}

//Set the weight of an edge that can only go from u to v to the value w
void GraphAM::SetDirectedEdge(int u, int v, double w){
	edgeWeights[EdgeIndex(u, v)] = w;
}

//Set the weight of an edge that can only go from u to v to the value 1
void GraphAM::SetDirectedEdge(int u, int v){
	edgeWeights[EdgeIndex(u, v)] = 1;
}

//Set the weight of an edge that go from u to v or v to u //to the value w
void GraphAM::SetUndirectedEdge(int u, int v, double w){
	edgeWeights[EdgeIndex(u, v)] = w;
	edgeWeights[EdgeIndex(v, u)] = w;
}

//Set the weight of an edge that go from u to v or v to u //to the value 1
void GraphAM::SetUndirectedEdge(int u, int v){
	edgeWeights[EdgeIndex(u, v)] = 1;
	edgeWeights[EdgeIndex(v, u)] = 1;
}

//Set the weight of an edge that go from u to v or v to u //to the value 0
void GraphAM::RemoveDirectedEdge(int u, int v){
	edgeWeights[EdgeIndex(u, v)] = 0;
}

//Set the weight of an edge that can only go from u to v to the value 0
void GraphAM::RemoveUndirectedEdge(int u, int v){
	edgeWeights[EdgeIndex(u, v)] = 0;
}

//Returns true if any path fron u to u exists
bool GraphAM::HasSelfLoops(){
	for(int v = 0; v < numVertices; v++)
		if(edgeWeights[EdgeIndex(v, v)] != 0)
			return true;
	return false;
}

//Returns true if ALL edges that go v to u have same w of edge that go u to v
bool GraphAM::IsUndirected(){
	int v = 0;
	for (int u = 0; u < numVertices; u++)
		for (int v = u; v < numVertices; v++)
			if (edgeWeights[EdgeIndex(u, v)] != edgeWeights[EdgeIndex(v, u)])
				return false;
	return !HasSelfLoops();
}

void GraphAM::Display(){
	int k = 0;
	cout << " V->| ";
	for (int v = 0; v < numVertices; v++)
		cout << v << "   ";
	cout << "\n   U|-----------------------------------------\n";
	for (int u = 0; u < numVertices; u++) {
		cout << "   " << u << "| ";
		for (int v = 0; v < numVertices; v++, k++)
				cout << edgeWeights[k] << "   ";
		cout << endl;
	}

}

//Displays all of the undirected edges to the user
void GraphAM::DisplayDirectedEdges(){
	cout << "\nu   v\n------------\n";
	for(int u = 0; u < numVertices; u++)
		for (int v = 0; v < numVertices; v++) {
			if (ExistEdge(u, v))
				cout << u << "-->" << v << " :: " << EdgeWeight(u, v) << endl;
			if (ExistEdge(v, u))
				cout << u << "<--" << v << " :: " << EdgeWeight(u, v) << endl;
		}
}

//Displays all of the undirected edges to the user
void GraphAM::DisplayUndirectedEdges(){
	if (IsUndirected()) {
		cout << "\nu   v\n------------\n";
		for (int u = 0; u < numVertices; u++)
			for (int v = 0; v < numVertices; v++)
				if (ExistEdge(u, v)) {
					cout << u << "<-->" << v << " :: " << EdgeWeight(u, v);
					cout << endl;
				}
	}
	else {
		cout << "Note: Cannot display as undirected graph, graph has\n";
		cout << "directed edges.. call function for directed graph instead.\n";
	}
}
