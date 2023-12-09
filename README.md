# Classic Minesweeper in my 2d Engine
<br>
This is just a quick project I wanted to work on to test some AI pathfinding algorithms. My initial idea is to use Dijkstra’s algorithm for clearing sections of the board. Since the idea is that we want to check each tile and determine if it is adjacent to a mine or not. Dijkstra’s algorithm should be ideal since that algorithm checks all possible paths. Generally you would then retrieve the reverse of the algo for a pathfinding system, but this game does not need to find a path, it just needs to touch all valid tiles on the game board.
<br>
All of the game logic is located in the GameBoard.cpp and header file. In here I set up the actual gameplay area, which is really just the clickable tiles. <br><br>
<h2 align='center'>The Technical stuff</h1>
<h3>Data Structures</h3>
I organized the tiles into an adjacency list. Each tile is adjacent to all immediate surrounding tiles vertically, horizontally and diagonally. The only tiles which do not have any adjacent tiles are the ones which contain mines. Using this data structure is a means of representing the grid as a graph, where the tiles are the nodes, or vertices. There is some directionality in this graph, namely tiles that do not contain mines have a traversable edge to mine tiles, but not the other way around. This is done for the purpose of counting the number of mines that are adjacent to a tile so we can print the correct number on the tile when it is clicked.
<h3>Algirithms</h3>
The main algirithm that is implemented in this project was stated at the top of this README, and it is Dijkstra's. Or rather, it is a variation. Since we are not concerned with finding the shortest path to any location, we just omit that part from the algorithm. We still traverse each node we can. During traversal we check to see if any particular node has any adjacent mines. If the tile we are inspecting does, then we do not continue following that route. This provides the expected behaviour that we see in classic minesweeper. 
      
