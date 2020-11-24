# COMP2113-Project


## Group 119

XIONG Yingchao 3035446796


## Game Description

You are in an amazing world.
There are 3 levels in total. You start from level 1.
Your goal is to get as many coins as possible.

'~' indicate your current location on the map.
Use 'w' (up) 'a' (left) 's' (down) 'd' (right) keys to move.
'#' is wall which cannot go through. Empty space is where you can go.
You can pick keys ('K'), use keys to open doors ('^'), add blood using '+'.

You can decide whether to fight with a monster.
When you fight with monsters, your blood decrease.
If you defeat the monster, you can collect corresponding no. of coins.
If your blood <= blood of monster, you die and lost the game.
Blood and coins of different monsters are different.

When you reach stairs '=', play zuma game. Then go to the higher level.
Zuma game: You first indicate how many balls in a row you want on the table.
The program will generate a random row of balls.
You then insert a ball of a color in a position. Any 3 balls together with the same color will be deleted.
You win zuma game when there is no ball on the table.
The game will calculate you points based on how many balls you want, how many balls you inserted and time taken.
If you get points > 0, you can get 2 coins in the main game.

In level 3, if you reach 'F', you can decide whether to finish the game.
If 'y', you achieved final success.
During the main game, you may press q to quit the game, game status will be stored.
When you excute the program again, you can continue the game or restart.
You may also press e to end the game, and you lost the game.


## Features to implement

#### 1. Generation of random game sets or events

    In the zuma game and, I use time(NULL) as seed to randomly generate a row of balls with different color and order, so that the player can have different rows each time.
    
#### 2. Data structures for storing game status

    Arrays, structures and linked list are used.
    In main game, I use 2-dimentional array to store the current game status (which is the map) of 3 different levels; we can access a specific location using coordinates (i, j).
    In the main game, I use structure to define data type to store the status of player and information of monsters.
    In the zuma game, we use linked list to store the row of balls left on the table; a ball point to the ball on the next, therefore, we can change the order and number of balls whatever we want and access the color sequentially.

#### 3. Dynamic memory management

    In the zuma game, we use linked list to store the game status. Since it can point to any other momory location, and we can know the order of a sequence of balls and can insert or delete any several balls into or from it.
    
#### 4. File input/output (e.g., for loading/saving game status)

   In the main game, you may choose to quit the game. The game status (including level, role information, location on the map, map setting) will be stored.
   If you excute the program again, you may choose to start the game from start. The main.cpp will use information stored in gameoriginal.txt, which is the initial setting of the game.
   You may also choose to continue the game. Then main.cpp will use information stored in gamestatus.txt, which contains the game status from your last excution.
   If you choose to continue the game when you play it in you first time, errors will be generated.
   
#### 5. Program codes in multiple files
    There are 2 major files: main.cpp and zuma.cpp, zuma.cpp is the main game, player can fight with monsters and collect coins, and go to a higher level after playing the zuma game. When the player goes to the stairs on the map, function in zuma.cpp will be called, and the player will play zuma game; after calling the function, flow of control goes back to main.cpp's main function, and the player goes to the next level.
    gameoriginal.txt is used to store the original setting of the game. If the player quit the game, gamestatus.txt will be created to store game status. And player can continue the game when he excute the program again.


## Compilation
    g++ -pedantic-errors -std=c++11 main.cpp zuma.cpp -o main


## Excution
    ./main
