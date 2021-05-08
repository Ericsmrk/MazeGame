<!-- PROJECT LOGO -->
<br />
<p align="center">
 
  </a>

  <h1 style="font-size:300%;" align="center" >!!MAP GAME!!</h1>

  <p align="center">
     This is a game that I completed by myself during the Spring 2021 semester 
     at California State University, Fresno
    <br />
    <a href="https://youtu.be/Q8T7BwmamM8"><strong>View Demo</a>
  </p>
</p>

<!-- ABOUT THE PROJECT -->
## About The Project
This is a game that I completed by myself during the Spring 2021 semester at California State University, Fresno

## Built With

* C++

<!-- Classes and Algorithms -->
## Classes and Algorithms (what it contains)

CLASSES (all functions have comments at the head)
  - GraphAM 
    * standard graph funtcionality for use with an adjacency matrix
    * can build a directed or undirected graph
    * Dijkstras Algorithm for finding a shortest path between two vertices
    * Kruskals algorithm using a minimum spanning tree (ALGO)
    * Breadth First Search with 2 modes (ALGO)
      - show all paths 
      - show from start to finish vertexes 
    * Depth First Search (ALGO)
    * standard insert/delete/print/get/set
  - Map (main functionality for game found here)
    * Builds a map using a graph which uses a matrix
    * Loads map from a text file
    * finds shortest path for each player to the goal
    * runs sshortest path algorithms
    * moves players automaticly!
    * provides ability to move player on own
    * standard insert/delete/print/get/set
  - Matrix
    * functionality to work with char and int matrices
    * standard insert/delete/print/get/set
    * standard matrix operations for dealing with a 2d graph
  - Player
    * seven different constructors
    * standard insert/delete/print/get/set for class private variables
    * Make a player for the game (includes i, j, tile value, player number)
    * set a players mode
    * Print the shortest path a player can go to get to target (it's in a Queue ADT)
  - Priority Queue
    * Heap operations
      - build a min heap
      - decrease key
      - get parent/left/right
      - min heapify algorithm
    * standard insert/delete/print/get/set
  - Queue
    * standard insert/delete/print/get/set

WORLDS
  - 5 worlds that can be chosen
  - one world for debugging

<!-- HOW TO USE MAP GAME -->
## How to use
1. load game by clicking on MazeGame.sln
2. choose debug mode or regular mode by pressing 1 or 0

	If you choose debug mode  
	- choose a map by pressing 1, 2, 3, 4, or 5  
	- choose how many players by pressing 1, 2, 3, or 4  
	- pick between auto mode(press Y) or step by step mode(press N)  
	- watch the magic  
	- hit ctrl-c at the end of game to exit (have errors to fix I guess)  
	
	If you choose regular mode  
	- choose a map by pressing 1, 2, 3, 4, or 5  
	- choose how many players by pressing 1, 2, 3, or 4  
	- pick between auto mode(press Y) or step by step mode(press N)  
	
	If you choose auto mode  
	- watch the magic  
	- hit ctrl-c at the end of game if crashes to exit (have errors to fix I guess)  
	Note: some times at the end of the game the actual quit game procedure works  
	- if no error chose 'q' to quit or 'c' for credits and quit  
	
	
	If you choose step by step mode mode  
	- (in this mode you control player one and the computer controles the other players)  
		- first hit the letter s to show the map and move down then...  
		- repeatedly hit one of the following keys to move character or quit  
		- Up hit w  
		- Down hit s  
		- Left hit a  
		- Right hit d   
		OR press q at any time to go to the quit menu  
		- watch the magic  
			- choose 'q' to quit or 'c' for credits and quit  


NOTE: this program uses dijkstras algorithm to move player toward the target ( $ sign )  

<!-- LICENSE -->
## License
MIT License

<!-- CONTACT -->
## Contact

Eric Smrkovsky - (EricSmrkovsky@mail.fresnostate.edu) - email
<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* California State University Fresno, Computer Science Department [http://www.fresnostate.edu/csm/csci/]()
* Dr Hubert Cecotti, Assistant Professor in Computer Science [https://sites.google.com/site/hubertcecotti/home]()
<!-- * []() -->

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/EricSmrk/repo.svg?style=for-the-badge
[contributors-url]: https://github.com/NavSanya/AsthmaTravels/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo/network/members
[stars-shield]: https://img.shields.io/github/stars/github_username/repo.svg?style=for-the-badge
[stars-url]: https://github.com/github_username/repo/stargazers
[issues-shield]: https://img.shields.io/github/issues/github_username/repo.svg?style=for-the-badge
[issues-url]: https://github.com/github_username/repo/issues
[license-shield]: https://img.shields.io/github/license/github_username/repo.svg?style=for-the-badge
[license-url]: https://github.com/github_username/repo/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/github_username
