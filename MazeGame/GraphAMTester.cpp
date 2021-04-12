#include <iostream>
#include <fstream>
#include "GraphAM.h"
using namespace std;

int main(){
	GraphAM* myGraph = new GraphAM(6);
	cout << "numV: " << myGraph->GetNumberVertices() << endl;
	cout << "EdgeIndex: " << myGraph->EdgeIndex(0, 1) << endl;
	cout << "setU 0->1 = 1: ";
	myGraph->SetUndirectedEdge(0, 1);
	cout << "\nsetU: 1->5 = 50: ";
	myGraph->SetUndirectedEdge(1, 5, 50);
	cout << "\nIsUndir: " << myGraph->IsUndirected() << endl;
	cout << "\nDispUndirEdges:";
	myGraph->DisplayUndirectedEdges();
	cout << "setU 0->2 = 1: ";
	myGraph->SetDirectedEdge(0, 2);
	cout << "\nsetU: 1->4 = 40: ";
	myGraph->SetDirectedEdge(1, 4, 40);
	cout << "\nIsUndir: " << myGraph->IsUndirected() << endl;
	cout << "HasSelfLoops: " << myGraph->HasSelfLoops() << endl;
	myGraph->Display();
	cout << "RemoveDirEdge 5->1 ";
	myGraph->RemoveDirectedEdge(5, 1);
	myGraph->SetUndirectedEdge(5, 5);
	cout << "HasSelfLoops: " << myGraph->HasSelfLoops() << endl;
	myGraph->Display();
	cout << "\nDispUndirEdges:";
	myGraph->DisplayUndirectedEdges();
	cout << "\nDispDirEdges:";
	myGraph->DisplayDirectedEdges();
	
	
	delete myGraph;
}