#include "GraphAM.h"
#include "Map.h"
#include "Matrix.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>
#include<windows.h>
using namespace std;

//Prototypes
void displayTitle();
void displayInstructions();
void getWorldChoice(int& );
int getNumberOfPlayers();
bool getGameMode();
void dijkstraTestforDebugMap(GraphAM* G, Map* map);
void autoModeGame(int, Map*);


int main()
{
	cout << "Hit 1 for debug mode 0 for regular mode...";
	int debug = 0;
	cin >> debug;
	if (debug != 1)
		debug = 0;
	
	int worldChoice = -1;
	//int worldChoice = 4;//set to 1-4 for debug mode
 	int numberOfPlayers = 1;//set to 1 for debug mode
	bool autoMode = true; //set to false for debug mode
	Map m;


	displayTitle();							  //display title
								//Menu to select levels, exit the program, ...
	getWorldChoice(worldChoice);			  //select the map
	Map* map = m.loadMapFromFile(worldChoice);//load the map
	map->setEdgeWeightsMatrix();
	map->makeMapGraph();
	GraphAM* mapGraph = map->getMapGraph();   //get the pointer to the map graph
	numberOfPlayers = getNumberOfPlayers(); //get number of players from user
	map->setNumberOfPlayers(numberOfPlayers); //sets the # of players for game 
	autoMode = getGameMode();				  //get the game mode from user
	map->setMode(autoMode);			  //ask user if they want auto mode
	cout << "\nYou chose " << numberOfPlayers << " players and to play in ";
	cout << (autoMode ? "auto mode..." : "step by step mode...");
	cout << "\n\n\n";
	
	map->createMapStartState(0);
	map->setPlayerRoutes();//uses dijkstra <-follow the code
	if (debug) {
		map->printAllPlayerInfo();//debug
		map->showEdgeWeightsMatrix();//debug
		map->displayVertexNumberMap(5, 5); //debug
		map->showMap();					  //display the loaded map
		map->showTargetCoordinates();//debug
	}
	bool finish = false;
	bool winnerFound = false;
	displayInstructions();					  //display instructions
	
	//run step by step mode
	while (!finish && !autoMode)// && !winnerFound)
	{
		char input;
		cin >> input;
		cout << "\n\n\n\n\n";
		//system("cls"); // clear the commandline (to refresh the screen)
		cout << "\n\n\n\nYou are in step by step mode!!\n\n\n\n";
		switch (input)
		{
		case 'q': finish = true; break;
		case 'w':
			system("cls"); // clear the commandline (to refresh the screen)
			cout << "\n\n\n\n\n";
			map->movePlayerOverrideRoute(0, 1);  //dir, playerN
			for (int i = 2; i <= numberOfPlayers; i++) {
				winnerFound = map->movePlayer(i, debug);  //dir, playerN
			}
			map->showMap();					  //display the loaded map
			break;
		case 's':
			system("cls"); // clear the commandline (to refresh the screen)
			cout << "\n\n\n\n\n";
			map->movePlayerOverrideRoute(1, 1);  //dir, playerN
			for (int i = 2; i <= numberOfPlayers; i++) {
				winnerFound = map->movePlayer(i, debug);  //dir, playerN
			}
			map->showMap();					  //display the loaded map
			break;
		case 'a':
			system("cls"); // clear the commandline (to refresh the screen)
			cout << "\n\n\n\n\n";
			map->movePlayerOverrideRoute(2, 1);  //dir, playerN
			for (int i = 2; i <= numberOfPlayers; i++) {
				winnerFound = map->movePlayer(i, debug);  //dir, playerN
			}
			map->showMap();					  //display the loaded map
			break;
		case 'd':
			system("cls"); // clear the commandline (to refresh the screen)
			cout << "\n\n\n\n\n";
			map->movePlayerOverrideRoute(3, 1);  //dir, playerN
			for (int i = 2; i <= numberOfPlayers; i++) {
				winnerFound = map->movePlayer(i, debug);  //dir, playerN
			}
			map->showMap();					  //display the loaded map
			break;
		}

	}

	//this runs automode
	while (!winnerFound && autoMode)// && !winnerFound)
	{
		int numIterations = 75;
			cout << "\n\n\n\n\n";
			system("cls"); // clear the commandline (to refresh the screen)
		
		for (int i = 0; i <= numIterations; i++) {
			cout << "\n\n\n\n\n";
			for (int i = 1; i <= numberOfPlayers; i++) {
				winnerFound = map->movePlayer(i, debug);  //i = playerN
			}
			map->showMap();					  //display the loaded map
			Sleep(300);
			system("cls"); // clear the commandline (to refresh the screen)
		}
		winnerFound = true;
	}
	cout << "	Good Game!   \n\n\n";
	cout << "Press c for credits or q to quit";
	char input2;
	cin >> input2;
	switch (input2) {
	case 'q': finish = true; break;
	case 'c': {
		cout << "This game was created by Eric Smrkovsky in 2021!";
		finish = true; break;
	}
}

	/*For the mapand its display, you may consider two possibilities :
	1 matrix to store the map
		1 array of characters to know their position(only store their position)
		1 matrix to display the map and the characters on the screen

		At each step, you copy the map in the display matrix, then you place the characters at their proper location, and you display the display matrix.

		or
		1 matrix to store the map
		1 array of characters to know their position(only store their position, the tile value)

		At each step, you put back the tile value at the proper location, then move the character, copy the tile value in the new locationand save it, then display the character.Here you will display the map.
		(you need to backup the space that is replaced by the character and update it each time it moves)*/
	
		
	
	//create a graph based on the map, and the cost of the types of vertices(plain, desert, ...)
		//here we have another matrix that represents the cost of going between each terrain type
		
	
	
	
	//get key press
			//while (not escape)
			//{
				//run shortest path algorithm, with the target as the source, the output provides an array PI for the predecessors
					//for each character
					//{
					//get their position i,j
					//convert i,j to a vertex u in the graph
					//get the vertex v = PI[u]
					//transform v to i1,j1
					//update the position of the character to i1,j1(update also what is on the map at i,j by getting back the proper tile)
					//}

						//if you pressed w / a / s / d, move the target

							//display the map
			//}
	//}
}

//Display the title screen
void displayTitle(){
	cout << "\n\n\n\n		CSCi 115 Project: MapGame\n\n\n\n";
}

//Display instructions to the user
void displayInstructions(){
	cout << "	Instructions: w / a / s / d to move the players q to quit\n";
}

//User chooses the map  
void getWorldChoice(int& choice){
	int count = 0;
	while (!(choice > 0 && choice < 6)) {
		cout << "\nChoose a map(1-5): ";
		cin >> choice;
		if (count == 4) {
			cout << "After five bad choices let's go with 1\n";
			choice = 1;
		}
		count++;
	}
}

//get number of players from the user (1-4)
int getNumberOfPlayers(){
	int choice = 0;
	int count = 0;
	while (!(choice > 0 && choice < 5)) {
		cout << "\nHow many players?(1-4): ";
		cin >> choice;
		if (count == 3) {
			cout << "Defaulting to 1 player... \n";
			choice = 1;
		}
		count++;
	}
	return choice;
}

//ask user if they want automatic mode or not
bool getGameMode(){
	bool choice = false;
	char input = 'n';
	cout << "\nAuto mode? (Y/N)";
	cin >> input;
	if (input == 'y' || input == 'Y')
		choice = true;

	return choice;
}

void dijkstraTestforDebugMap(GraphAM* mapGraph, Map* map){
	int n = mapGraph->GetNumberVertices();
	cout << "N: " << n << endl;
	double* shortestPath = nullptr;
	int* listOfPrevIndexes = nullptr;
	//CHANGE 0 TO STARTv
	mapGraph->Dijkstra(0, shortestPath, listOfPrevIndexes);
	map->showMap();
	mapGraph->ShowArray(shortestPath, n);
	mapGraph->DisplayShortestPathsFound(shortestPath, listOfPrevIndexes);
	//cout << endl;

	int targetIndex = map->getTargetVertex();
	cout << "TargetIndex: " << targetIndex << endl;
	int distance = shortestPath[targetIndex]; //get distance of goal state
	//cout << "\nD: " << distance[goalV];
	PriorityQueue* DijkstrasPathPQ = new PriorityQueue(n);
	int backTracker = listOfPrevIndexes[targetIndex]; //log the goal vertex
	DijkstrasPathPQ->Push(0, targetIndex);		//insert goal vertex

	//Traverse graph backwards from goal state to start state logging PI's
	for (int i = 1; i <= n+1 && backTracker != -1; i++) {
		DijkstrasPathPQ->Push(i, backTracker);
		backTracker = listOfPrevIndexes[backTracker];
	}

	//show results 
	DijkstrasPathPQ->DisplayPQ();
	cout << "NumE: " << DijkstrasPathPQ->GetNumberOfElements() << endl;


	cout << DijkstrasPathPQ->Pop().value << endl;
	cout << DijkstrasPathPQ->Pop().value << endl;
	cout << DijkstrasPathPQ->Pop().value << endl;
	cout << DijkstrasPathPQ->Pop().value << endl;
	cout << DijkstrasPathPQ->Pop().value << endl;
	cout << DijkstrasPathPQ->Pop().value << endl;
	cout << DijkstrasPathPQ->Pop().value << endl;

	cout << "NumE: " << DijkstrasPathPQ->GetNumberOfElements() << endl;

}

//run the game in automode
void autoModeGame(int numberOfPlayers, Map* map){
	bool finish = false;
	while (!finish)
	{
		char input;
		cin >> input;
		cout << "\n\n\n\n\n";
		system("cls"); // clear the commandline (to refresh the screen)
		switch (input)
		{
		case 'q': finish = true; break;
		case 'w':
			system("cls"); // clear the commandline (to refresh the screen)
			cout << "\n\n\n\n\n";
			for (int i = 1; i <= numberOfPlayers; i++) {
				map->movePlayerOverrideRoute(0, i);  //dir, playerN
			}
			//map->movePlayerOverrideRoute(0, 1);  //dir, playerN
			map->showMap();					  //display the loaded map
		case 's':
			system("cls"); // clear the commandline (to refresh the screen)
			cout << "\n\n\n\n\n";
			for (int i = 1; i <= numberOfPlayers; i++) {
				map->movePlayerOverrideRoute(1, i);  //dir, playerN
			}
			//map->movePlayerOverrideRoute(1, 1);  //dir, playerN
			map->showMap();					  //display the loaded map
		case 'a':
			system("cls"); // clear the commandline (to refresh the screen)
			cout << "\n\n\n\n\n";
			for (int i = 1; i <= numberOfPlayers; i++) {
				map->movePlayerOverrideRoute(2, i);  //dir, playerN
			}
			//map->movePlayerOverrideRoute(2, 1);  //dir, playerN
			map->showMap();					  //display the loaded map
		case 'd':
			system("cls"); // clear the commandline (to refresh the screen)
			cout << "\n\n\n\n\n";
			for (int i = 1; i <= numberOfPlayers; i++) {
				map->movePlayerOverrideRoute(3, i);  //dir, playerN
			}
			//map->movePlayerOverrideRoute(3, 1);  //dir, playerN
			map->showMap();					  //display the loaded map
		}
	}
}
