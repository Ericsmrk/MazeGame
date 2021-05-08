#include "Map.h"
#include <iostream>
using namespace std;

//Create the map using Matrix class and initializes all values to '#'
Map::Map(int n, int m){
	rows = n;
	cols = m;
	//create default matrix of size n by m for the map
	CharMap = new Matrix(n, m, '#'); 
	cMap = nullptr;
}

//Displays the number of rows and colums
void Map::displayRowsAndCols(){
	cout << "Rows: " << rows << "  ,  Cols: " << cols << endl;
}

//Loads the a map from a file and return a pointer to it
Map* Map::loadMapFromFile(int choice){
	string rows_s;		//row size (converts to int)
	string cols_s;		//column size (converts to int)
	int n = 0;
	int m = 0;
	string temp;		//string for getting each line
	string filename;// = "Worlds/World1.txt";
	ifstream map;

	//assign the file to be opened depending on user choice
	if (choice == 0) filename = "Worlds/Debug.txt";
	if (choice == 1) filename = "Worlds/World1.txt";
	if (choice == 2) filename = "Worlds/World2.txt";
	if (choice == 3) filename = "Worlds/World3.txt";
	if (choice == 4) filename = "Worlds/World4.txt";
	if (choice == 5) filename = "Worlds/World5.txt";

	map.open(filename, ios::in);	//get ready to read file
	
	//check that file was opened sucsessfully
	if (map.fail())
		cout << "\nError opening file\n";
	
	//file opened is a sucsess
	else {
		getline(map, rows_s);		//get row size from file
		getline(map, cols_s);		//get col size from file
		n = stoi(rows_s);//convert row size to int
		m = stoi(cols_s);//convert col size to int	
	}
	
	cMap = new Map(n, m);	//create a map populated with all mountains	

	//create map of size n by m from file
	int GoalVertexCounter = -1;
	for (int i = 0; i < n; i++) {
		getline(map, temp);
		for (int j = 0; j < m; j++) {
			//determin X here
			GoalVertexCounter++;
			cMap->setTarget(temp[j], i, j, GoalVertexCounter);
			cMap->setTerrain(i, j, temp[j]);
		}
	}
	return cMap;
}

//populate the EdgeWeights Matrix with weights
void Map::setEdgeWeightsMatrix(){
	int rs = 4;
	int cs = 4;

	//All weights start at 99
	edgeWeightsAM = new Matrix(rs, cs, 99); 

	//if a # do nothing, it's already set to 99 otherwise set F=77, _=22, T=5
	for (int i = 0; i < rs; i++) {
		for (int j = 0; j < cs; j++) {
			if(j == 1)
				edgeWeightsAM->SetVal(i, j, 22);
			if(j == 2)
				edgeWeightsAM->SetVal(i, j, 77);
			if(j == 3)
				edgeWeightsAM->SetVal(i, j, 5);
		}
	}
}

char Map::getTerrain(int i, int j) {
	char t = CharMap->GetChar(i, j);// getTerrain(i, j);
	//if (t == '1' || t == '2' || t == '3' || t == '4')
		//t = getPlayersTileVal(i, j, t);
	//else
		//t = CharMap->GetChar(i, j); 
	return CharMap->GetChar(i, j); 
}


//sets the target cell in the map to '$' and logs it's i and j into the class 
void Map::setTarget(char& x, int i, int j, int t){
	if (x == 'X') {
		targetVertex = t;
		x = '$';
		targeti = i;
		targetj = j;
	}
}

//Display the targets i and j coodinates for debugging purposes
void Map::showTargetCoordinates(){
	cout << "Targeti: " << targeti << "  ,  Targetj: " << targetj << "\n";
}

//show the number of players
void Map::showNumberOfPlayers(){
	cout << numberOfPlayers;
}

//show the specified players iformation
void Map::printPlayerInfo(int pNum){
	if (pNum == 1)
		if (player1 != nullptr) {
			player1->printPlayerInfo();
			cout << endl;
		}
		else
			cout << "Player1 is not being used\n";
	if (pNum == 2)
		if (player2 != nullptr) {
			player2->printPlayerInfo();
			cout << endl;
		}
		else
			cout << "Player2 is not being used\n";
	if (pNum == 3)
		if (player3 != nullptr)		{
			player3->printPlayerInfo();
			cout << endl;
		}
		else
			cout << "Player3 is not being used\n";
	if (pNum == 4)
		if (player4 != nullptr) {
			player4->printPlayerInfo();
			cout << endl;
		}
		else
			cout << "Player4 is not being used\n";
}

//print all of the players information that are on the map
void Map::printAllPlayerInfo(){
	printPlayerInfo(1);
	printPlayerInfo(2);
	printPlayerInfo(3);
	printPlayerInfo(4);
}

//show the EdgeWeights matrix
void Map::showEdgeWeightsMatrix(){
	string s = "#_FT";
	cout << "\n		  EdgeWeights (i->j)";
	cout << "\n		   #  _  F  T  \n";
	for (int i = 0; i < 4; i++) {
		cout << "	       " << s[i] << "| ";
		cout << edgeWeightsAM->GetVal(i, 0) << " ";
		cout << edgeWeightsAM->GetVal(i, 1) << " ";
		cout << edgeWeightsAM->GetVal(i, 2) << " ";
		cout << edgeWeightsAM->GetVal(i, 3) << " \n";
	}
}

//prints a cells neighboor status (if up/down/left/right exists)
void Map::printNeighboorStatus(int i, int j) {
	cout << "\nNeighboors for (" << i << "," << j << ") are...";
	cout << "\nUp neighboor is " <<	checkNeighboorUp(i, j);
	cout << "\nDown neighboor is " << checkNeighboorDown(i, j);
	cout << "\nLeft neighboor is " << checkNeighboorLeft(i, j);
	cout << "\nRight neighboor is " << checkNeighboorRight(i, j) << endl;
}
//show All Tile Values on map and shows under all of the players too
void Map::showAllTileValues(){
	char t = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			t = getTerrain(i, j);
			cout << "T: ";
			if (t == '1' || t == '2' || t == '3' || t == '4')
				t = getPlayersTileVal(i, j, t);
			cout << t << endl;
		}
	}
}

//method to set the number of characters on the map and their locations
void Map::createMapStartState(int debug){
	
	//get locations
	int gap = cols / numberOfPlayers; //using this to spread out starting locs
	//each players start at  (0,p#loc) on map (if cols = 20 vals are 1,6,11,16 
	int p1loc = gap%numberOfPlayers;//makes it so they don't start in corner
	int p2loc = (gap % numberOfPlayers) + gap;
	int p3loc = (gap % numberOfPlayers) + (gap * 2);
	int p4loc = (gap % numberOfPlayers) + (gap * 3);

	if (debug) {
		cout << "P1: " << p1loc;
		cout << " , P2: " << p2loc;
		cout << " , P3: " << p3loc;
		cout << " , P4: " << p4loc;
	}

	//get the tile values of the locations on the map
	char p1TileVal = getTerrain(0, p1loc);
	char p2TileVal = getTerrain(0, p2loc);
	char p3TileVal = getTerrain(0, p3loc);
	char p4TileVal = getTerrain(0, p4loc);

	//allocate mem for players and set values Player(i,j,pnum,tileloc,mode)
	player1 = new Player(0, p1loc, 1, p1TileVal, autoMode);
	setTerrain(0, p1loc, '1');
	if (numberOfPlayers > 1) {
		player2 = new Player(0, p2loc, 2, p2TileVal, autoMode);
		setTerrain(0, p2loc, '2');
		if (numberOfPlayers > 2) {
			player3 = new Player(0, p3loc, 3, p3TileVal, autoMode);
			setTerrain(0, p3loc, '3');
			if (numberOfPlayers > 3) {
				player4 = new Player(0, p4loc, 4, p4TileVal, autoMode);
				setTerrain(0, p4loc, '4');
			}
		}
	}
}

//returns the correct value for visiting a terrain (terrains = (# _ F T))
double Map::getCostToAMbyRules(char terrain) {
	string symbols = "#_FT";
	int cost = 0;
	if (terrain == '#')
		cost = 99;
	if (terrain == '_')
		cost = 22;
	if (terrain == 'F')
		cost = 77;
	if (terrain == 'T')
		cost = 5;
	if (terrain == '$')
		cost = 2;
	return cost;
}

//return the vertex number 
//double Map::getVertex(int i, int j){
//	if (ValMap != nullptr)
//		return  ValMap[i][j];
//	else
//		return 0;
//	
//}

//makes a graph out of the map
void Map::makeMapGraph() {

	mapGraph = new GraphAM(rows * cols);
	mapAMforGraph = new Matrix(rows * rows, cols * cols, 0);

	int n = rows;
	int m = cols;
	double cost = 0;
	char t = 0;
	char dest = 0;
	string symbols = "#_FT";

	bool foundATunnel = false;
	int tunneli = -1;
	int tunnelj = -1;

	//for each map(i,j) if up/down/left/right neighboor is valid
	//then we check the edge cost of going in that direction and apply a 
	//proper cost depending on the edgeWeight value
	//to each edge going to each valid neighboor
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			t = getTerrain(i, j);
			if (checkNeighboorUp(i, j)) {//checks i-1,j
				if (t == '1' || t == '2' || t == '3' || t == '4')
					dest = getPlayersTileVal(i, j, t);
				else
					dest = getTerrain(i - 1, j);
				if (dest == 'T' && !foundATunnel) {
					tunneli = i;
					tunnelj = j;
				}
				if (dest == 'T' && foundATunnel) {
					mapGraph->SetUndirectedEdge((tunneli * n) + tunnelj, (i * m) + j, 2);
					foundATunnel = false;
				}
				else {
					cost = getCostToAMbyRules(dest);
					mapGraph->SetUndirectedEdge((i * n) + j, ((i - 1) * m) + j, cost);
				}
			}
			if (checkNeighboorDown(i, j)) {//checks i+1,j
				if (t == '1' || t == '2' || t == '3' || t == '4')
					dest = getPlayersTileVal(i, j, t);
				else
					dest = getTerrain(i + 1, j);
				if (dest == 'T' && !foundATunnel) {
					tunneli = i;
					tunnelj = j;
				}
				if (dest == 'T' && foundATunnel) {
					mapGraph->SetUndirectedEdge((tunneli * n) + tunnelj, (i * m) + j, 2);
					foundATunnel = false;
				}
				else {
					cost = getCostToAMbyRules(dest);
					mapGraph->SetUndirectedEdge((i * n) + j, ((i + 1) * m) + j, cost);
				}
			}
			if (checkNeighboorLeft(i, j)) {//checks i,j-1
				if (t == '1' || t == '2' || t == '3' || t == '4')
					dest = getPlayersTileVal(i, j, t);
				else
					dest = getTerrain(i, j - 1);
				if (dest == 'T' && !foundATunnel) {
					tunneli = i;
					tunnelj = j;
				}
				if (dest == 'T' && foundATunnel) {
					mapGraph->SetUndirectedEdge((tunneli * n) + tunnelj, (i * m) + j, 2);
					foundATunnel = false;
				}
				else {
					cost = getCostToAMbyRules(dest);
					mapGraph->SetUndirectedEdge((i * n) + j, (i * m) + (j - 1), cost);
				}
			}
			if (checkNeighboorRight(i, j)) {//checks i,j+1
				if (t == '1' || t == '2' || t == '3' || t == '4')
					dest = getPlayersTileVal(i, j, t);
				else
					dest = getTerrain(i, j + 1);
				if (dest == 'T' && !foundATunnel) {
					tunneli = i;
					tunnelj = j;
				}
				if (dest == 'T' && foundATunnel) {
					mapGraph->SetUndirectedEdge((tunneli * n) + tunnelj, (i * m) + j, 2);
					foundATunnel = false;
				}
				else {
					cost = getCostToAMbyRules(dest);
					mapGraph->SetUndirectedEdge((i * n) + j, (i * m) + (j + 1), cost);
				}
			}
		}
	}
	//mapGraph->DisplayGraphNoSpace();
	//mapGraph->DisplayDirectedEdges();
}

//returns true if the neighbor to the north exists
bool Map::checkNeighboorUp(int i, int j){
	bool flag = true;
	if (i - 1 < 0)
		flag = false;
	return flag;
}

//returns true if the neighbor to the south exists
bool Map::checkNeighboorDown(int i, int j){
	bool flag = true;
	if (i + 1 > rows-1)
		flag = false;
	return flag;
}

//returns true if the neighbor to the west exists
bool Map::checkNeighboorLeft(int i, int j){
	bool flag = true;
	if (j - 1 < 0)
		flag = false;
	return flag;
}

//returns true if the neighbor to the east exists
bool Map::checkNeighboorRight(int i, int j){
	bool flag = true;
	if (j + 1 > cols-1)
		flag = false;
	return flag;
}

//if the map position is occupied by a player, get it's tile value
char Map::getPlayersTileVal(int i, int j, char terrain){
	char val = 0;
	if (terrain == '1')
		 val = player1->getTileVal();
	if (terrain == '2')
		val = player2->getTileVal();
	if (terrain == '3')
		val = player3->getTileVal();
	if (terrain == '4')
		val = player4->getTileVal();
	return val;
}

//show a n by m matrix filled with the vertex numbers for reference
void Map::displayVertexNumberMap(int n, int m){
	cout << "\n";
	int count = 0;
	for (int i = 0; i < n; i++) {
		cout << "     ";
		for (int j = 0; j < m; j++)
			cout << count++ << " ";
		cout << endl;
	}
}

//set the route of each player using Dijkstras algorithm
void Map::setPlayerRoutes(){
	int p1Start = -1;
	int p2Start = -1;
	int p3Start = -1;
	int p4Start = -1;
	int target = getTargetVertex();
	//these use player i*rows+j to find vertex position on graph for
	//starting locations. Then using dijkstras, we set a route for each player
	if (player1 != nullptr) {
		p1Start = player1->geti() * rows + player1->getj();
		player1->setRoute(mapGraph->DijkstrasRoute(p1Start, target));
	}
	if (player2 != nullptr) {
		p2Start = player2->geti() * rows + player2->getj();
		player2->setRoute(mapGraph->DijkstrasRoute(p2Start, target));
	}
	if (player3 != nullptr) {
		p3Start = player3->geti() * rows + player3->getj();
		player3->setRoute(mapGraph->DijkstrasRoute(p3Start, target));
	}
	if (player4 != nullptr) {
		p4Start = player4->geti() * rows + player4->getj();
		player4->setRoute(mapGraph->DijkstrasRoute(p4Start, target));
	}
}

//returns a pointer to the player
Player* Map::getPlayer(int playerNumber){
	if (playerNumber == 1)
		return player1;
	if (playerNumber == 2)
		return player2;
	if (playerNumber == 3)
		return player3;
	if (playerNumber == 4)
		return player4;
	else
		return player1;
}

//Create a map of mountains using Matrix class and return pointer to it
Matrix* Map::getMountainMap(int n, int m){
	Matrix* aMap = new Matrix(n, m, '#'); //create default matrix of size n by m
	return aMap;
}

//move the player one step toward the destination
void Map::movePlayerOverrideRoute(int dir, int playerN) {
	// 0=up, 1 = down, 2 = l, 3 = r
	Player* p = getPlayer(playerN);
	Queue* playerRoute = p->getPlayerRoute();
	Matrix* mat = new Matrix(rows, cols);
	mat->SetValMatrixToIndexes();
	int pNum = p->getPlayerNum();
	bool done = false;
	//cout << "TV: " << p->getTileVal();
	int temp = -1;
	
		if (dir == 0) {//(i-1,j)  UP
			setTerrain(p->geti(), p->getj(), p->getTileVal());//change mapChar to tileChar
			p->seti((p->geti()) - 1);			//update players i, j
			p->setTileVal(getTerrain(p->geti(), p->getj()));//set tileChar to new mapChar 
			setTerrain(p->geti(), p->getj(), pNum);//change mapChar to playerNum
		}
		if (dir == 1) {//(i+1,j)  DOWN
			setTerrain(p->geti(), p->getj(), p->getTileVal());//change mapChar to tileChar
			p->seti((p->geti()) + 1);		//update players i, j
			p->setTileVal(getTerrain(p->geti(), p->getj()));//set tileChar to new mapChar 
			setTerrain(p->geti(), p->getj(), pNum);//change mapChar to playerNum
		}
		if (dir == 2) {//(i,j-1)  LEFT
			setTerrain(p->geti(), p->getj(), p->getTileVal());//change mapChar to tileChar
			p->setj((p->getj()) - 1);		//update players i, j
			p->setTileVal(getTerrain(p->geti(), p->getj()));//set tileChar to new mapChar 
			setTerrain(p->geti(), p->getj(), pNum);//change mapChar to playerNum
		}
		if (dir == 3) {//(i,j+1)   RIGHT
			setTerrain(p->geti(), p->getj(), p->getTileVal());//change mapChar to tileChar
			p->setj((p->getj()) + 1);		//update players i, j
			p->setTileVal(getTerrain(p->geti(), p->getj()));//set tileChar to new mapChar 
			setTerrain(p->geti(), p->getj(), pNum);//change mapChar to playerNum
		}
	/*	if (getTerrain(p->geti(), p->getj()) == '$')
			done = true;
	}*/
}

//THIS ONLY WORKS WHEN i GO right WHY
//move the player one step toward the destination
bool Map::movePlayer(int playerN, int debug) {
	Player* p = getPlayer(playerN);     //get relevent player
	Queue* playerRoute = p->getPlayerRoute();//make q of player route from dijkstra
	MyType* q = playerRoute->getQ();     //to Access q data
	Matrix* mat = new Matrix(rows, cols);//matrix for vertexes
	mat->SetValMatrixToIndexes();		//populate vertext matrix
	int pNum = p->getPlayerNum();
	int qSize = playerRoute->GetSize();

	if (debug)
		p->printRouteOfPlayer();
	//int counter = p->getCounter();
	int counter = getPlayerCounter(pNum);
	//cout << "cou: " << counter << "  ,  " << q[qSize - (counter + 1)];
	bool done = false;
	bool winnerFound = false;
	while (!winnerFound) {
		for (int i = 0; i < rows; i++)//add another check
			for (int j = 0; j < cols; j++) {

				if (int(q[qSize - (counter+1)]) == mat->GetVal(i, j)) {
					if (debug) {
						cout << "\nStart: " << int(q[qSize - (counter)]);
						cout << "\nDest: " << int(q[qSize - (counter + 1)]);
						cout << "\nVertex#: " << mat->GetVal(i, j) << " /i,j=" << i << "," << j;
						cout << "\nPTileVal: " << p->getTileVal();
					}
					setTerrain(p->geti(), p->getj(), p->getTileVal());//change mapChar to tileChar
					p->seti(i);
					p->setj(j);		//update players i, j
					p->setTileVal(getTerrain(i, j));//set tileChar to new mapChar 
					setTerrain(p->geti(), p->getj(), pNum);//change mapChar to playerNum
					done = true;
					if (getTerrain(i, j)) {
						//cout << "    Player " << pNum << " is the WINNER!!!\n";
						winnerFound = true;
					}

				}
			}
	}
	incPlayerCounter(pNum);
	//p->IncrementCounter();
	return winnerFound;
}

//make a matrix for finding vertexes
void Map::makValMatrix(){
	Matrix* ValMap = new Matrix(rows, cols, 0);
	ValMap->SetValMatrixToIndexes();
}

//get the right player counter
int Map::getPlayerCounter(int p){
	if (p == 1) 
		return getP1Counter();
	if (p == 2)
		return getP2Counter();
	if (p == 3)
		return getP3Counter();
	if (p == 4)
		return getP4Counter();	
}

//increment the players counter
void Map::incPlayerCounter(int p){
	if (p == 1)
		incP1Counter();
	if (p == 2)
		incP2Counter();
	if (p == 3)
		incP3Counter();
	if (p == 4)
		incP4Counter();
}
