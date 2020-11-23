# COMP2113-Project


## Group 119

XIONG Yingchao 3035446796


## Game Description

You enter an amazing world. There are three levels in the game. You can go to the next level after playing the zuma game.
You start from level 1. Use the w(up) a(left) s(down) d(right) keys to move the role, it can pick keys ('K'), use keys to open doors ('^'), add blood using '+', and fight with monsters. There are bat 'B', wizzard 'E', green head monster 'G', red head monster 'R', skeleton 'S'.
When you fight with monsters, your blood decreases. If you defeat the monster, you can collect corresponding no. of coins. If you die (blood < 0 after fight with monsters), you can decide to play again or not.
When you reach stairs, you will enter zuma game. To play zuma game insert a ball at once into a row of balls, any more than 3 balls together will be deleted. When there is no ball left, you win and go to the higher level.
In the 3rd level, if you reach 'E', you can decide whether to end the game. If 'y', you achieved final success, and if 'n', game continues. 


## Features to implement

1. Generation of random game sets or events

    In the zuma game and, I use time(NULL) as seed to randomly generate a row of balls with different color and order, so that the player can have different rows each time.
    
2. Data structures for storing game status

    Arrays, structures and linked list are used.
    In main game, I use 2-dimentional array to store the current game status (which is the map) of 3 different levels; we can access a specific location using coordinates (i, j).
    In the main game, I use structure to define data type to store the status of player and information of monsters.
    In the zuma game, we use linked list to store the row of balls left on the table; a ball point to the ball on the next, therefore, we can change the order and number of balls whatever we want and access the color sequentially.

3. Dynamic memory management

    In the zuma game, we use linked list to store the game status. Since it can point to any other momory location, and we can know the order of a sequence of balls and can insert or delete any several balls into or from it.
    
4. File input/output (e.g., for loading/saving game status)

    In the main.cpp, 
    The game first output rules of the game.
    Input: direction, using 'a' 'd' 'w' 's' to represent
    After each direction indicated by the player, status of map and role will change, the function will print the current map and current information of role (blood, bluekeys, and coins)
    If the player meet a monster, the game will ask whether to fight with it or not. Player then input 'y' or 'n'. After the battle, the game will print result (win or die). If win, game continues. If lose, game ask whether to play again. Player then input 'y' or 'n', if 'y', start game all over again; if 'n', game ends.
    When player meet'E', he also input 'y' or 'n' to indicate whether quit the game. If quit, the game then print "end of games".
   
    In the zuma.cpp,
    The game first output rules of the game.
    The first input is how many balls you want for a row
    Then player input 'Y' to start the game. The game will print the original randomly generated row of balls,
    Then user input the color and position to insert a ball. Then game output the row of balls left on the table after insertation and deletion (if applicable).
    When there is no balls left of the table, game print how many points and coins the player get from zuma game.
    
5. Program codes in multiple files
    There are 2 major files: main.cpp and zuma.cpp, zuma.cpp is the main game, player can fight with monsters and collect coins, and go to a higher level after playing the zuma game. When the player goes to the stairs on the map, function in zuma.cpp will be called, and the player will play zuma game; after calling the function, flow of control goes back to main.cpp's main function, and the player goes to the next level.


## Compilation
    g++ -pedantic-errors -std=c++11 main.cpp zuma.cpp -o main


## Excution
    ./main
