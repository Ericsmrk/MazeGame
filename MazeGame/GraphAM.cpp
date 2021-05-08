//Lab 9 CSCI 115 Spring 2021
//Eric Smrkovsky
#include "GraphAM.h"
#include "Queue.h"
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

//Sets the current pointer to -1 showing that it hasn't been accessed yet
void GraphAM::SetCurrentVertex(int u){
	current[u] = -1;
}

//Returns true if there is an adjacent vertex
//Also changes the value of current for u to the vertex found or sets to -1 
bool GraphAM::GetNextAdjacent(int u, int& vout){
	int v = current[u] + 1;
	vout = -1;
	bool found = false;
	while (!found && v < numVertices) {
		if (ExistEdge(u, v)) {
			found = true;
			vout = v;//changes the v value found outside the scope of this func
		}
		v++;
	}
	current[u] = vout;
	return found;
}

//Calls the FSP_BFS algorithm to find the shortest path between start and goal
void GraphAM::FindShortestPathBFS(int startV, int goalV) {
	ColorNode* color = nullptr;
	int* distance = nullptr;
	int* pi = nullptr;
	FSP_BFS(startV, goalV, color, distance, pi);
	delete[] color;
	delete[] distance;
	delete[] pi;
}

//This is an altered version of BFS algorithm found on page 595 in ITA
//It puts the shortest path between start and goal into a queue 
void GraphAM::FSP_BFS(int startV, int goalV, ColorNode*& color, 
												int*& distance,	int*& pi){
	if (!(startV >= 0 && startV < numVertices))
		cout << "\nError: Start vertex does not exist in graph...\n";
	else {
		Queue* Q = new Queue(numVertices);
		color = new ColorNode[numVertices];
		distance = new int[numVertices];
		pi = new int[numVertices];
		for (int u = 0; u < numVertices; u++) {
			color[u] = setColor(0);//sets to unvisited
			distance[u] = 0;
			pi[u] = 0;
		}
		color[startV] = setColor(1);//sets to visited
		distance[startV] = 0;
		pi[startV] = -1;
		Q->Enqueue(startV);
		while (!Q->IsEmpty()) {
			int u = Q->Dequeue();
			for (int v = 0; v < numVertices; v++) {
				if (ExistEdge(u, v) && color[v] == setColor(0)) {
					color[v] = setColor(1);
					distance[v] = distance[u] + 1;
					pi[v] = u;
					Q->Enqueue(v);
				}
			}
			color[u] = setColor(2);
		}
		delete Q;
		//cout << endl;
		int d = distance[goalV]; //get distance of goal state
		//cout << "\nD: " << distance[goalV];
		pathQ = new Queue(d+1);
		int backTracker = pi[goalV]; //log the goal vertex
		pathQ->Enqueue(goalV);		//insert goal vertex

		//Traverse graph backwards from goal state to start state logging PI's
		for (int i = 0; i <= distance[goalV]; i++) {
			pathQ->Enqueue(backTracker);
			backTracker = pi[backTracker];
		}

		//show results 
		pathQ->DisplayQueue();
	}
}

//Performs Kruskal's algorithm (very different from algo in ITA 3rd
void GraphAM::MSTKruskal(int debug){
	GraphAM KeptEdgesG(numVertices);   //create graph to display kept edges
	Matrix EdgesM(numVertices, numVertices, 0); //make a matrix full of 0's
	int total = -1;		//for holding sum of all weights
	char lets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	//initialize all values of matrix to data from input graph
	for (int i = 0; i < numVertices; i++)
		for (int j = i + 1; j < numVertices; j++) {
			EdgesM.SetVal(i, j, EdgeWeight(i, j));//populate matrx with weights
			if(EdgeWeight(i, j) != 0)
				total++;		
		}

	//get first smallest weight 
	EdgesM.GetMin();//At smallest weight, collect i, j, val and set weight to 0
	KeptEdgesG.SetUndirectedEdge(EdgesM.GetArgi(), EdgesM.GetArgj(), EdgesM.GetMinValue());//Set the same index with val from matrix

	cout << "\n\n  Collected Weights\n";
	EdgesM.DisplayIntMatrix();

	if (debug) {//DEBUG STUFF
		cout << "\n\n  Collected Weights\n";
		EdgesM.DisplayIntMatrix();
		cout << "\n  Edge count: " << total;
		cout << "\nMST...\n";
		KeptEdgesG.DisplayConvertToChar();
	}

	cout << "\n\n    Undirected edges in MST with weights...\n";

	//get the rest of the smallest weights
	for (int i = 0; i < total; i++) {
		bool flag = true;
		
		EdgesM.GetMin();//At smallest weight, collect i, j, val and set weight
		KeptEdgesG.SetUndirectedEdge(EdgesM.GetArgi(), EdgesM.GetArgj(), EdgesM.GetMinValue());//Set the same index with val from matrix
		
		//if we find a cycle we undo the addition of the edge
		if (!IsAcyclic(EdgesM.GetArgi(), KeptEdgesG)) {
			KeptEdgesG.RemoveUndirectedEdge(EdgesM.GetArgi(), EdgesM.GetArgj());
			flag = false;
		}

		//shows output if edge remains
		if (flag) {//'lets' takes the integer value and converts to proper let
			cout << "(" << lets[EdgesM.GetArgi()] << " <--> ";
			cout << lets[EdgesM.GetArgj()];
			cout << ")  ,  W: " << EdgesM.GetMinValue() << endl;
		}
	}

	if (debug) {//debug stuff
		cout << "\n\n  Collected Weights\n";
		EdgesM.DisplayIntMatrix();
		cout << "\n  Edge count: " << total;
		cout << "\nMST...\n";
		cout << "Final MST Graph and edges\n";
		KeptEdgesG.DisplayConvertToChar();
		KeptEdgesG.DisplayDirectedEdges();
	}

	//show final graph
	cout << "\nMST...\n";
	cout << "Final MST Graph\n";
	KeptEdgesG.DisplayConvertToChar();
}

//helper function that performs the recursion when checking for cycles in a graph
void GraphAM::Acyclic(int u, GraphAM& G, int* color, int* pi, int* back, int parent) {
	color[u] = 1;
	G.SetCurrentVertex(u);
	int v = G.GetNumberVertices();
	//traverse through the graph
	while (G.GetNextAdjacent(u, v)) {
		if (G.ExistEdge(u, v) && v != u && v != parent)
			//if we havent visited the vertex recurse and continur traversal
			if (color[v] == 0) {
				pi[v] = 0;
				Acyclic(v, G, color, pi, back, u);
			}
			else
				back[v] = u;
	}
	//now we are done visiting u
	color[u] = 2;
}

//Checks that there is not a cycle in the graph
bool GraphAM::IsAcyclic(int u, GraphAM& G){
	//allocate mem for pointers
	int* color = new int[numVertices];
	int* back = new int[numVertices];
	int* pi = new int[numVertices];

	//asign values to pinters
	for (int i = 0; i < numVertices; i++) {
		color[i] = 0;
		back[i] = -1;
		pi[i] = -1;
	}
	Acyclic(u, G, color, pi, back, -1);//calls helper function
	int i = 0;
	bool acyclic = true;
	bool found = false;
	//traverses graph and if a cycle is found from backtrack with pi ret false
	while (i < numVertices && !found) {
		if (back[i] == u && pi[i] != u) {
			found = true;
			acyclic = false;
		}
		i++;
	}
	delete[] color;
	delete[] back;
	return acyclic;
}

//Calls the BFS algorithm and prints the results
void GraphAM::BreadthFirstSearch(int start) {
	cout << "\n\nNow running Breadth First Search (start is V=";
	cout << start << ")...\n\n";
	ColorNode* color = nullptr;
	int* distance = nullptr;
	int* pi = nullptr;
	BFS(start, color, distance, pi);
	cout << "Start: V#  ,  End: V#  ,  Distance from start to end  ,  ";
	cout << "\nPI: End vertex found from PI vertex";
	cout << "\n---------------------SHORTEST PATHS-------------------------\n";
	for (int u = 0; u < numVertices; u++) {
		cout << "      Start: " << start << "  ,  End: " << u << "  ,";
		cout << "  Distance: " << distance[u] << "  PI: " << pi[u] << endl;
	}
	delete[] color;
	delete[] distance;
	delete[] pi;
}

//BFS algorithm follow sudocode on page 595 in ITA closely
void GraphAM::BFS(int start, ColorNode*& color, int*& distance, int*& pi){
	if (!(start >= 0 && start < numVertices))
		cout << "\nError: Start vertex does not exist in graph...\n";
	else {
		Queue* Q = new Queue(numVertices);
		color = new ColorNode[numVertices];
		distance = new int[numVertices];
		pi = new int[numVertices];
		for (int u = 0; u < numVertices; u++){
			color[u] = setColor(0);//sets to unvisited
			distance[u] = 0;
			pi[u] = 0;
		}
		color[start] = setColor(1);//sets to visited
		distance[start] = 0;
		pi[start] = -1;
		Q->Enqueue(start);
		while (!Q->IsEmpty()) {
			int u = Q->Dequeue();
			for (int v = 0; v < numVertices; v++) {
				if (ExistEdge(u, v) && color[v] == setColor(0)) {
					color[v] = setColor(1);
					distance[v] = distance[u] + 1;
					pi[v] = u;
					Q->Enqueue(v);
				}
			}
			color[u] = setColor(2);
		}
		delete Q;
	}
}

//DFS algorithm sudocode on page 604 in ITA
void GraphAM::DFS(ColorNode* &color, int* &discovery, 
							  int* &finished, int* &pi) {
	color = new ColorNode[numVertices];
	discovery = new int[numVertices];
	finished = new int[numVertices];
	pi = new int[numVertices];
	for (int u = 0; u < numVertices; u++) {
		color[u] = setColor(0);
		discovery[u] = 0;
		finished[u] = 0;
		pi[u] = 0;
	}
	for (int u = 0; u < numVertices; u++) {
		if (color[u] == setColor(0))
			DFSVisit(u, color, discovery, finished, pi);
	}
}

//Calls the DFS algorithm and prints the results
void GraphAM::DepthFirstSearch(){
	cout << "\n\nNow running Depth First Search (start is V=0)...\n\n";
	//set all to nullptr
	ColorNode* color = nullptr;
	int* discovery = nullptr;
	int* finished = nullptr;
	int* pi = nullptr;
	DFS(color, discovery, finished, pi);
	cout << "\n\nV: (Discovered, Finished)   PI: Parent of V (node was";
	cout << " discovered after visiting PI)\n------------------------------\n";
	for (int u = 0; u < numVertices; u++)//show data for each vertices
		cout << u << ": (" << discovery[u] << ", " << finished[u] 
						  << ")  PI: " << pi[u] << endl;
	//delete all allocated memory
	delete[] color;
	delete[] discovery;
	delete[] finished;
	delete[] pi;
}

//Recursively visit each node and changes it's colors accordingly
void GraphAM::DFSVisit(int u, ColorNode* color, //sudocode on page 604 in ITA 
							int* discovery, int* finished, int* pi){
	int v;
	color[u] = setColor(1); //set to visited
	cout << "\nNow visiting " << u << " ";
	discovery[u] = ++time;//time is a private variable of the class
	SetCurrentVertex(u);//sets to -1
	while (GetNextAdjacent(u, v)) {
		if (v != -1 && color[v] == setColor(0)) {
			pi[v] = u;
			cout << "Traveling on EDGE " << EdgeIndex(u, v) << " from " << u;
			cout << " to " << v << ".";
			DFSVisit(v, color, discovery, finished, pi);
		}
	}
	color[u] = setColor(2); //set to finished
	finished[u] = ++time;
}

//Sets the color of the verticies 0=unvisited, 1=visited, 2=finished
ColorNode GraphAM::setColor(int num){
	if(num == 0)
		return ColorNode::Unvisited;
	if (num == 1)
		return ColorNode::Visited;
	if (num == 2)
		return ColorNode::Finished;
}

//Display an MST
void GraphAM::DisplayMST(int* parent){
	cout << "MST Edge Weight" << endl;
	for (int i = 1; i < numVertices; i++) {
		cout << "(" << parent[i] << "-> " << i << ") w=";
		cout << EdgeWeight(i, parent[i]) << endl;
	}
}

//Dijkstras shortest path algorithm ALL WEIGHTS MUST BE >=0
void GraphAM::Dijkstra(int startVertex, double*& shortPathEstimate, int*& prevIndex){
	shortPathEstimate = new double[numVertices];
	prevIndex = new int[numVertices];
	PriorityQueue* PQ = new PriorityQueue(numVertices);
	Queue* Q = new Queue(numVertices);
	
	//initialize the destinations array and the previous index array 
	for (int u = 0; u < numVertices; u++) {
		shortPathEstimate[u] = DBL_MAX;
		prevIndex[u] = -1;
	}
	shortPathEstimate[startVertex] = 0;

	//initialize PQ with short path estimates for each vertex
	for (int u = 0; u < numVertices; u++)
		PQ->Push(u, shortPathEstimate[u]);
	//PQ->DisplayPQ();	//uncomment to show

	//while the Q is not full to capacity
	while (!Q->IsFull()) {
		MyData out = PQ->Pop();
		//PQ->DisplayPQ();	//uncomment to show
		Q->Enqueue(out.index);
		int u = out.index;
		//cout << "Use: " << out.index << "with d:" << out.value << endl;
		SetCurrentVertex(u);
		
		//while there exists an adjacent vertex do relaxation
		int v;
		while (GetNextAdjacent(u, v)) {
			double weight = EdgeWeight(u, v);
			//if path for v is larger that path for (u + u->v weight) keep
			if (shortPathEstimate[v] > shortPathEstimate[u] + weight) {
				shortPathEstimate[v] = shortPathEstimate[u] + weight;
				prevIndex[v] = u; //set the pi value
				PQ->DecreaseKey(v, shortPathEstimate[v]);
			}
		}
		//Q->DisplayQueue();
		//PQ->DisplayPQ();
	}
	delete PQ;
	delete Q;
}

//Display the shortest path
void GraphAM::DisplayShortestPathsFound(double* d, int* pi){
	for (int i = 0; i < numVertices; i++) {
		cout << "Vertex: i: " << i << "  ,  d: " << d[i];
		cout << "  , pi: " << pi[i] << endl;
	}
}

//calls dijkstras algorithm with target vertex and destination vertex
Queue* GraphAM::DijkstrasRoute(int startV, int destV){
	int n = GetNumberVertices();
	double* shortestPath = nullptr;
	int* listOfPrevIndexes = nullptr;
	Dijkstra(startV, shortestPath, listOfPrevIndexes);

	//cout << "TargetIndex: " << destV << endl;
	int distance = shortestPath[destV]; //get distance of goal state
	Queue* DijkstrasPathQ = new Queue(n);//
	int backTracker = listOfPrevIndexes[destV]; //log the goal vertex
	DijkstrasPathQ->Enqueue(destV);

	//Traverse graph backwards from goal state to start state logging PI's
	for (int i = 1; i <= n + 1 && backTracker != -1; i++) {
		DijkstrasPathQ->Enqueue(backTracker);
		backTracker = listOfPrevIndexes[backTracker];
	}
	return DijkstrasPathQ;
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

//Displays graph in a nice way
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

//Displays the graph as a 2d matrix with no spaces 
void GraphAM::DisplayGraphNoSpace(){
	int k = 0;
	for (int u = 0; u < numVertices; u++) {
		cout << u << "| ";
		for (int v = 0; v < numVertices; v++, k++)
			cout << edgeWeights[k];
		cout << endl;
	}
}

//Displays graph in a nice way and converts vertices to chars
void GraphAM::DisplayConvertToChar() {
	int k = 0;
	char lets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	cout << " V->| ";
	for (int v = 0; v < numVertices; v++)
		cout << lets[v] << "   ";
	cout << "\n   U|-----------------------------------------\n";
	for (int u = 0; u < numVertices; u++) {
		cout << "   " << lets[u] << "| ";
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
				cout << u << "<--" << v << " :: " << EdgeWeight(v, u) << endl;
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
