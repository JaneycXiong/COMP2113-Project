#include <iostream>
#include <cctype>
#include <string>
#include <iomanip>
#include "zuma.h"

using namespace std;


//map design

char map[13][13];

char map1[13][13];

char map2[13][13];

char map3[13][13];


////initilize role information and monster information
struct gameRole{
  int blood;
  int bluekey;
  int coin;
};


struct gameRole role = {500,0,0};


struct monster
{
  int blood;
  int coin;
};


struct monster bat = {100,2};
struct monster wizzard = {300,3};
struct monster GreenHeadMonster = {20,1};
struct monster RedHeadMonster = {40,1};
struct monster Skeleton = {50,1};


// function prototype
bool bloodPK (monster);
void drawmap (char[13][13]);
void keyDown (gameRole &, char[13][13], char &, char &, int, int, int &, int &,
  int &, char &);
void keychange (char, int &, int &);
void print_role (gameRole);


//main function of the game
int main()
{
  //main game rules
  cout << "RULES" << endl;
  cout << "\nYou enter an amazing world.There are 3 levels in total." << endl;
  cout << "You start from level 1. '~' indicate your location on the map." << endl;
  cout << "Use w(up) a(left) s(down) d(right) keys to move." << endl;
  cout << "# is wall which cannot go through. Empty space is where you can go." << endl;
  cout << "\nYou can pick keys ('K'), use keys to open doors ('^'), add blood using '+'." << endl;
  cout << "\nMonster: bat 'B', wizzard 'E', green head monster 'G', red head monster 'R', skeleton 'S'." << endl;
  cout << "You can decide whether to fight with a monster." << endl;
  cout << "When you fight with monsters, your blood decrease." << endl;
  cout << "If you defeat the monster, you can collect corresponding no. of coins." << endl;
  cout << "If you die (blood < 0 after fighting), you can decide to play again or not." << endl;
  cout << "\nWhen you reach stairs '=', play zuma game. Then go to the higher level." << endl;
  cout << "\nIn level 3, if you reach 'E', you can decide whether to end the game." << endl;
  cout << "If 'y', you achieved final success, and if 'n', game continues." << endl;

  int level;
  char userKey;
  int keyi, keyj;

  char ifend = 'n';
  char play = 'y';

  // if the player doesn't want to play again after he dies, end the loop
  // if the player wants to play again then start the game from beginning
  while (play == 'y')
  {
    //need to reinitilize map and role after the player plays again

    level = 1;
    char die = 'n';
    int x = 11;
    int y = 6;

    gameRole role = {500, 0, 0};

    char map1[13][13] =
    {
      '1', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
      '#', '=', ' ', 'G', 'R', 'G', ' ', ' ', ' ', ' ', ' ', ' ', '#',
      '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
      '#', '+', ' ', ' ', '^', ' ', '#', ' ', 'K', ' ', '#', ' ', '#',
      '#', ' ', 'S', 'K', '#', ' ', '#', ' ', '+', ' ', '#', ' ', '#',
      '#', '#', '^', '#', '#', ' ', '#', '#', '#', '^', '#', ' ', '#',
      '#', 'K', ' ', ' ', '#', ' ', '^', ' ', 'W', ' ', '#', ' ', '#',
      '#', ' ', 'S', 'K', '#', ' ', '#', '#', '#', '#', '#', ' ', '#',
      '#', '^', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
      '#', ' ', ' ', ' ', '#', '#', '^', '#', '#', '#', '^', '#', '#',
      '#', '+', ' ', 'K', '#', 'K', ' ', 'K', '#', 'K', ' ', 'K', '#',
      '#', '+', ' ', 'B', '^', ' ', '~', ' ', '^', ' ', ' ', '+', '#',
      '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
    };

    char map2[13][13] =
    {
      '2', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
      '#', '~', ' ', 'K', '#', '+', ' ', ' ', '#', ' ', ' ', 'S', '#',
      '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '^', ' ', '#', ' ', '#',
      '#', '^', '#', '^', '#', '#', '#', '#', '#', ' ', '#', ' ', '#',
      '#', ' ', '#', ' ', ' ', ' ', '^', ' ', ' ', 'R', '#', ' ', '#',
      '#', ' ', '#', 'K', ' ', ' ', '#', 'K', ' ', ' ', '#', ' ', '#',
      '#', ' ', '#', '#', '#', '^', '#', '#', '#', '^', '#', ' ', '#',
      '#', ' ', '#', 'R', ' ', ' ', '#', '+', ' ', ' ', '#', ' ', '#',
      '#', '^', '#', '#', '#', ' ', '#', ' ', ' ', 'B', '^', ' ', '#',
      '#', 'W', ' ', ' ', '#', '+', '#', 'K', ' ', ' ', '#', ' ', '#',
      '#', ' ', ' ', 'K', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
      '#', ' ', '+', ' ', ' ', 'G', '^', ' ', ' ', ' ', ' ', '=', '#',
      '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
    };

    char map3[13][13] =
    {
      '3', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
      '#', '+', ' ', ' ', '#', 'R', ' ', ' ', '#', ' ', '^', ' ', '#',
      '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#',
      '#', ' ', '#', ' ', ' ', ' ', '#', 'G', ' ', ' ', '#', ' ', '#',
      '#', 'B', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
      '#', ' ', '#', ' ', '#', 'W', ' ', ' ', ' ', ' ', ' ', ' ', '#',
      '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#',
      '#', 'K', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#',
      '#', '#', '#', '^', '#', '#', '#', '#', '#', ' ', '#', 'K', '#',
      '#', ' ', '+', 'B', '#', '+', ' ', ' ', '^', ' ', '#', '#', '#',
      '#', 'S', ' ', ' ', '#', ' ', 'B', ' ', '#', '#', '#', ' ', '#',
      '#', ' ', 'E', ' ', '#', 'K', ' ', ' ', 'S', ' ', ' ', '~', '#',
      '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
    };

    // if the player dies ends the loop
    // each iteration take 1 userkey, to determine the direction
    while (die != 'y')
    {
      switch ( level )
      {
        // when the player is at different levels, use map1, map2, map3 as
        // corresponding array variables

        case 1:
          // take userkey as direction
          // change map1, role information, location of the role accordingly

          drawmap (map1);
          cout << "Input which direction to go: ";
          cin >> userKey;
          userKey = tolower(userKey);
          keychange (userKey, keyi, keyj);
          keyDown (role, map1, die, play, keyi, keyj, x, y, level, ifend);
          print_role(role);
          break;

        case 2:
          // take userkey as direction
          // change map2, role information, location of the role accordingly

          drawmap (map2);
          cout << "Input which direction to go: ";
          cin >> userKey;
          userKey = tolower(userKey);
          keychange (userKey, keyi, keyj);
          keyDown (role, map2, die, play, keyi, keyj, x, y, level, ifend);
          print_role(role);
          break;

        case 3:
          // take userkey as direction
          // change map, role information, location of the role accordingly

          drawmap (map3);
          cout << "Input which direction to go: ";
          cin >> userKey;
          userKey = tolower(userKey);
          keychange (userKey, keyi, keyj);
          keyDown (role, map3, die, play, keyi, keyj, x, y, level, ifend);
          print_role(role);
          break;
      }
    }

    play = tolower(play);
  }

  cout << "\nEND OF GAME" << endl;
  if (ifend == 'y') {
    cout << "Wellcome to the final SUCCESS" << endl;
  }
  cout << "You have been such a brave warrior!!!" << endl;
  cout << "You have defeated so many monsters!!!" << endl;

}


bool bloodPK(gameRole &role, monster mons)
{ // PK, determine if the player can defeat a certain monster
  role.blood = role.blood  - mons.blood;

  // cannot defeat, player die
  if(role.blood <= 0)
  {
    return false;
  }
  // can defeat, get some coins correspondingly
  else
  {
    role.coin = role.coin + mons.coin;
    return true;
  }

}


void drawmap(char map[13][13])
{
  //draw map line by line
  int i,j;
  for (i = 0; i < 13; i++){
    cout << endl;
    for (j = 0; j < 13; j++)
    {cout << setw(2) << map[i][j];}
  }
  cout << "\n" << endl;
}


void print_role(gameRole role)
{
  //print role information
  cout << "\nblood: " << role.blood << endl;
  cout << "bluekey: " << role.bluekey << endl;
  cout << "coin: " << role.coin << endl;
}


void keyDown (gameRole &role, char map[13][13], char &die, char &play, int keyi,
  int keyj, int &i, int &j, int &level, char &ifend)
{
  //take userkey as direction, change map, role location, role information

  char YorN;
  switch ( map[i + keyi][j + keyj] )
  {
    case ' ':
    // place to go is empty
      map[i][j] = ' ';
      map[i + keyi][j + keyj] = '~';
      i = i + keyi;
      j = j + keyj;
      break;

    case '=':
    // go upstairs
      int point;
      cout << "Welcome to zuma game!" << endl;
      zuma_main(point);
      if (point > 0) {
        role.coin += 2;
        cout << "You got 2 coins." << endl;
      }
      level += 1;
      i = i + keyi;
      j = j + keyj;

      break;

    case 'K':
    //key
      map[i][j] = ' ';
      map[i + keyi][j + keyj] = '~';
      role.bluekey++;
      i = i + keyi;
      j = j + keyj;
      break;

    case '^':
    // door need key to open
      if (role.bluekey > 0){
        map[i][j] = ' ';
        map[i + keyi][j + keyj] = '~';
        i = i + keyi;
        j = j + keyj;
        role.bluekey--;
      }
      else {
        cout << "You need to collect keys.";}

      break;

    case '+':
      //add blood
      role.blood += 100;
      map[i][j] = ' ';
      map[i + keyi][j + keyj] = '~';
      i = i + keyi;
      j = j + keyj;
      break;

    case 'B':
      //meet bat
      cout << "You meet the bat, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
        //PK with bat
        if (bloodPK(role, bat))
        {
          cout << "You defeated it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
        else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'W':
      //meet wizzard
      cout << "You meet the wizzard, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
      //PK with wizzard
        if (bloodPK(role, wizzard))
        {
          cout << "You defeated it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
        else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'R':
      //meet red head monster
      cout << "You meet the red head monster, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
        //PK with red monster
        if (bloodPK(role, RedHeadMonster))
        {
          cout << "You defeated it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
        else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'G':
      //meet green head monster
      cout << "You meet the green head monster, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
        //PK with green head monster
        if (bloodPK(role, GreenHeadMonster))
        {
          cout << "You defeated it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
      else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'S':
    //meet Skeleton
      cout << "You meet the Skeleton, fight it or not？";
      cin >> YorN;
      YorN = tolower(YorN);
      if (YorN == 'y') {
        //PK with Skeleton
        if (bloodPK(role, Skeleton))
        {
          cout << "You defeated it" << endl;
          map[i][j] = ' ';
          map[i + keyi][j + keyj] = '~';
          i = i + keyi;
          j = j + keyj;
        }
        else
        {
          die = 'y';
          cout << "You die, play again? ";
          cin >> play;
        }
      }
      break;

    case 'E':
    //check if the player wants to end the game
      cout << "Do you want to end the game and stop fighting with monsters? ";
      cin >> ifend;
      if (ifend == 'y') {
        die = 'y';
        play = 'n';
      }
      break;

  }
}


// determine how the user location change for each direction
// e.g. if go left, i-1, j doesn't change, then keyi = -1, keyj = 0
void keychange (char userKey, int &keyi, int &keyj)
{
  switch (userKey)
  {
    case 'a':
     keyi = 0;
     keyj = -1;
     break;

    case 'd':
      keyi = 0;
      keyj = 1;
      break;

    case 'w':
      keyi = -1;
      keyj = 0;
      break;

    case 's':
      keyi  = 1;
      keyj = 0;
      break;
  }

}
