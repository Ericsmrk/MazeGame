#pragma once
//#include "PriorityQueue.h"
#include "Queue.h"
class Player{
public:
	//constructors (all constructore start in step by step mode)
	Player() : argi(-1), argj(-1), playerNum(0), tileVal('P'), autoMode(true), playerRoute(nullptr), Playercounter(1) {}; //all null
	Player(char x) : argi(-1), argj(-1), playerNum(0), tileVal(x), autoMode(true), playerRoute(nullptr), Playercounter(1) {};//sets char
	Player(int p) : argi(-1), argj(-1), playerNum(p), tileVal('P'), autoMode(true), playerRoute(nullptr), Playercounter(1) {};//sets playernm
	Player(int i, int j, int n) : argi(i), argj(j), playerNum(n), tileVal('P'), autoMode(true), playerRoute(nullptr), Playercounter(1) {};//sets i, j, num
	Player(int i, int j, char x) : argi(i), argj(j), playerNum(0), tileVal(x), autoMode(true), playerRoute(nullptr), Playercounter(1) {};//sets i, j, char
	Player(int i, int j, int n, char x) : argi(i), argj(j), playerNum(n), tileVal(x), autoMode(true), playerRoute(nullptr), Playercounter(1) {};//sets all but mode
	Player(int i, int j, int n, char x, bool m) : argi(i), argj(j), playerNum(n), tileVal(x), autoMode(m), playerRoute(nullptr), Playercounter(1) {};//sets all
	~Player();//destructor

	//setters
	void seti(int i) { argi = i; }
	void setj(int j) { argj = j; }
	void setPlayerNum(int n) { playerNum = n; }
	void setTileVal(char c) { tileVal = c; }
	void setAutoMode(bool tf) { autoMode = tf; }
	void setRoute(Queue* PRoute) { playerRoute = PRoute; }
	void setCounter(int c) { Playercounter = c; }
	void IncrementCounter() { Playercounter++; }
	
	//getters
	int geti() { return argi; }
	int getj() { return argj; }
	int getPlayerNum() { return playerNum; }
	char getTileVal() { return tileVal; }
	bool getMode() { return autoMode; }
	Queue* getPlayerRoute() { return playerRoute; }
	int getCounter() { return Playercounter; }

	//printers 
	void printPlayerInfo();
	void printRouteOfPlayer();


	//utilities
	Player* makeNewPlayer(int p);//passes the players number for identificaion
	void test();//used for doing some testing on this class

private:
	Queue* playerRoute;
	int Playercounter;
	int argi;
	int argj;
	int playerNum;
	char tileVal;
	bool autoMode;
};
//needstructs for charactersA character has the following properties
//i, j(position on the map)       
// tilevalue: the value of the map where the character is placed
