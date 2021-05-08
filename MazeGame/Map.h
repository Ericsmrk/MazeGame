#pragma once
#include "Matrix.h"
#include "GraphAM.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <string>

class Map {

public:
	//constructors
	Map() : rows(0), cols(0), targeti(-1), targetj(-1), CharMap(nullptr), cMap(nullptr), player1(nullptr), player1Counter(1), player2(nullptr), player2Counter(1), player3(nullptr), player3Counter(1), player4(nullptr), player4Counter(1), numberOfPlayers(0), autoMode(false), edgeWeightsAM(nullptr), tunnelNetwork(nullptr), mapGraph(nullptr), mapAMforGraph(nullptr), ValMap(nullptr), targetVertex(-1) {};
	Map(int n, int m);

	//setters
	void setRows(int n) { rows = n; }
	void setCols(int m) { cols = m; }
	void setTerrain(int i, int j, char c) { CharMap->SetChar(i, j, c); }
		//method to set the position of the target	(call when see X in file) 
	void setTarget(char& x, int i, int j, int targVcounter);
	void setNumberOfPlayers(int n) { numberOfPlayers = n; }//set # of players
	void setMode(bool m) { autoMode = m; }
	Map* loadMapFromFile(int choice);//method to load the the map from a file
	void setEdgeWeightsMatrix();
	void incP1Counter() { player1Counter++; }
	void incP2Counter() { player2Counter++; }
	void incP3Counter() { player3Counter++; }
	void incP4Counter() { player4Counter++; }
	void incPlayerCounter(int p);

	//getters
	int getRows() { return rows; }
	int getCols() { return cols; }
	char getTerrain(int i, int j);
	int getTargeti() { return targeti; }
	int getTargetj() { return targetj; }
	int getNumberOfPlayers() { return numberOfPlayers; }
	bool getMode() { return autoMode; }
	Player* getPlayer(int playerNumber);
	Matrix* getMountainMap(int n, int m);
	Matrix* getMap() { return CharMap; }
	Matrix* getEdgeWeightsMatrix() { return edgeWeightsAM; }
	//returns the correct value for visiting a terrain (terrains = (# _ F T))
	double getCostToAMbyRules(char terrain);
	GraphAM* getMapGraph() { return mapGraph; }
	int getTargetVertex() { return targetVertex; }
	double getVertex(int i, int j);
	int getP1Counter() { return player1Counter; }
	int getP2Counter() { return player2Counter; }
	int getP3Counter() { return player3Counter; }
	int getP4Counter() { return player4Counter; }
	int getPlayerCounter(int p);

	//printers
	void displayRowsAndCols();
	void showMap() { CharMap->DisplayCharMatrix(); }//method to display the map
	void showTargetCoordinates();//displays targeti, targetj
	void showNumberOfPlayers();
	void printPlayerInfo(int pNum);
	void printAllPlayerInfo();
	void showEdgeWeightsMatrix();
	void printNeighboorStatus(int i, int j);
	void showAllTileValues(); //checks under where all of the players are too
	
	//utilities
	//method to set the number of characters on the map and their locations
	void createMapStartState(int debug);
	//method to make a graph out of the map
	void makeMapGraph();
	bool checkNeighboorUp(int i, int j);
	bool checkNeighboorDown(int i, int j);
	bool checkNeighboorLeft(int i, int j);
	bool checkNeighboorRight(int i, int j);
	char getPlayersTileVal(int i, int j, char terrain);
	//show a n by m matrix filled with the vertex numbers for reference
	void displayVertexNumberMap(int n, int m);
	void setPlayerRoutes();
	void movePlayerOverrideRoute(int dir, int playerN);
	bool movePlayer(int playerN, int debug);
	void makValMatrix();

private:
	int rows;				
	int cols;
	int targeti;
	int targetj;
	int targetVertex;
	Player* player1;
	Player* player2;
	Player* player3;
	Player* player4;
	int player1Counter;
	int player2Counter;
	int player3Counter;
	int player4Counter;
	int numberOfPlayers;
	bool autoMode;
	Map* cMap;					//the world map
	Matrix* CharMap;			//the matrix structure of the map
	Matrix* ValMap;			//the matrix structure of the map
	Matrix* edgeWeightsAM;		//the cost to go between terrains
	Matrix* mapAMforGraph;//adjacency matrix for all the weights between cells 
	GraphAM* tunnelNetwork;		//a graph that is produced as a tunnel network
	GraphAM* mapGraph;	//the graph created with charmap as vertices
};

