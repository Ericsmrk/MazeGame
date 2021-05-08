#include "Player.h"
#include <iostream>
using namespace std;

//prints the player info (playerNum,i,j,tileVal)
void Player::printPlayerInfo(){
	cout << "\nPlayer #" << getPlayerNum() << " at location (";
	cout << geti() << "," << getj() << ") is in terrain ";
	cout << getTileVal() << " and in ";
	cout << (getMode() ? "auto mode." : "step by step mode.\n");
	cout << "Player will take the following route displayed as Q\n";
	/*playerRoute->DisplayPQ();
	playerRoute->PopAndPrint(playerRoute);*/
	playerRoute->DisplayQueue();
}

void Player::printRouteOfPlayer(){
	playerRoute->DisplayQueue();
}

//allocate mem for a new player 
Player* Player::makeNewPlayer(int playerNumber){
	Player* player = new Player(playerNumber);
	return player;
}

//testing function
void Player::test(){
	cout << "TESTING PLAYER CLASS";
	Player* player = new Player(5, 5, 4, '@');
	player->printPlayerInfo();
	player->seti(11);
	player->setj(11);
	player->setTileVal('F');
	player->printPlayerInfo();
	cout << player->geti() << player->getj() << player->getTileVal();
}
