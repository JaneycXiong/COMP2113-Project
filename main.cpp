#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>
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

gameRole role;

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
void keyDown (gameRole &, char[13][13], char &, int, int, int &, int &,
  int &, char &);
void keychange (char, int &, int &);
void print_role (gameRole);
void change_map (char[13][13]);
void changeback_map (char map[13][13]);


//main function of the game
int main()
{
  //print main game rules
  cout << "RULES" << endl;
  cout << "\nYou are in an amazing world." << endl;
  cout << "There are 3 levels in total. You start from level 1." << endl;
  cout << "~ indicate your current location on the map." << endl;
  cout << "Use w(up) a(left) s(down) d(right) keys to move." << endl;
  cout << "# is wall which cannot go through. Empty space is where you can go." << endl;
  cout << "\nYou can pick keys ('K'), use keys to open doors ('^'), add blood using '+'." << endl;
  cout << "\nYou can decide whether to fight with a monster." << endl;
  cout << "When you fight with monsters, your blood decrease." << endl;
  cout << "If you defeat the monster, you can collect corresponding no. of coins." << endl;
  cout << "If your blood <= blood of monster, you die and lost the game." << endl;
  cout << "\n" << setw(23) << "Monster" << setw(7) << "blood" << setw(6) << "coin" << endl;
  cout << setw(23) << "bat 'B'" << setw(7) << "100" << setw(6) << "2" << endl;
  cout << setw(23) << "wizzard 'E'" << setw(7) << "200" << setw(6) << "3" << endl;
  cout << setw(23) << "green head monster 'G'" << setw(7) << "20" << setw(6) << "1" << endl;
  cout << setw(23) << "Red head monster 'R'" << setw(7) << "40" << setw(6) << "1" << endl;
  cout << setw(23) << "skeleton 'S'" << setw(7) << "50" << setw(6) << "1" << endl;
  cout << "\nWhen you reach stairs '=', play zuma game. Then go to the higher level." << endl;
  cout << "\nIn level 3, if you reach 'F', you can decide whether to finish the game." << endl;
  cout << "If 'y', you achieved final success, and if 'n', game continues.\n" << endl;
  cout << "During the main game, you may press q to quit the game, game status will be stored." << endl;
  cout << "You may also press e to end the game, and you lost the game.\n" << endl;


  int level;
  int x, y;

  int a;
  cout << "Press 1 to start the game from beginning. Press 2 to continue the game." << endl;
  cin >> a;
  while (a != 1 && a != 2) {
    cout << "Press 1 to start the game from beginning. Press 2 to continue the game." << endl;
    cin >> a;
  }

  ifstream fin;

  if (a == 1) {
    fin.open("gameoriginal.txt");
    if (fin.fail()){
     cout<<"Error in file opening!"<<endl;
     exit(1);
    }
  }
  else if (a == 2) {
    fin.open("gamestatus.txt");
    if (fin.fail()){
     cout<<"Error in file opening!"<<endl;
     exit(1);
    }
  }

  fin >> level >> x >> y >> role.blood >> role.bluekey >> role.coin;
  for (int i = 0; i < 13; ++i) {
    for (int j = 0; j < 13; ++j) {
      fin >> map1[i][j];
    }
  }
  for (int i = 0; i < 13; ++i) {
    for (int j = 0; j < 13; ++j) {
      fin >> map2[i][j];
    }
  }
  for (int i = 0; i < 13; ++i) {
    for (int j = 0; j < 13; ++j) {
      fin >> map3[i][j];
    }
  }
  fin.close();

  change_map(map1);
  change_map(map2);
  change_map(map3);

  char userKey;
  int keyi, keyj;
  char die = 'n';
  char iffin = 'n';

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
        if (userKey == 'q' || userKey == 'e')
        {
          die = 'y';
        }
        else
        {
          keychange (userKey, keyi, keyj);
          keyDown (role, map1, die, keyi, keyj, x, y, level, iffin);
          print_role(role);
        }
        break;

      case 2:
        // take userkey as direction
        // change map2, role information, location of the role accordingly

        drawmap (map2);
        cout << "Input which direction to go: ";
        cin >> userKey;
        userKey = tolower(userKey);
        if (userKey == 'q' || userKey == 'e')
        {
          die = 'y';
        }
        else
        {
          keychange (userKey, keyi, keyj);
          keyDown (role, map2, die, keyi, keyj, x, y, level, iffin);
          print_role(role);
        }
        break;

      case 3:
        // take userkey as direction
        // change map, role information, location of the role accordingly

        drawmap (map3);
        cout << "Input which direction to go: ";
        cin >> userKey;
        userKey = tolower(userKey);
        if (userKey == 'q' || userKey == 'e')
        {
          die = 'y';
        }
        else
        {
          keychange (userKey, keyi, keyj);
          keyDown (role, map3, die, keyi, keyj, x, y, level, iffin);
          print_role(role);
        }
        break;
    }
  }

  if (userKey == 'q') {
    changeback_map(map1);
    changeback_map(map2);
    changeback_map(map3);

    ofstream fout;
    fout.open("gamestatus.txt");

    if ( fout.fail() ) {
      cout << "Error in file opening!" << endl;
      exit(1);
    }

    fout << level << " " << x << " " << y << " " << role.blood << " "
    << role.bluekey << " " << role.coin << endl;
    fout << endl;

    for (int i = 0; i < 13; ++i) {
      for (int j = 0; j < 13; ++j) {
        fout << map1[i][j] << " ";
      }
      fout << endl;
    }
    fout << endl;

    for (int i = 0; i < 13; ++i) {
      for (int j = 0; j < 13; ++j) {
        fout << map2[i][j] << " ";
      }
      fout << endl;
    }
    fout << endl;

    for (int i = 0; i < 13; ++i) {
      for (int j = 0; j < 13; ++j) {
        fout << map3[i][j] << " ";
      }
      fout << endl;
    }

    cout << "The game status has been stored." << endl;
  }

  else {
    cout << "\nEND OF GAME" << endl;
    if (iffin == 'y') {
      cout << "You achieved the final SUCCESS!" << endl;
      cout << "You have won " << role.coin << " coins!" << endl;
    }
    else {
      cout << "You lose the game!" << endl;
      cout << "But you have been such a brave warrior!!!" << endl;
    }

  }

  return 0;
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


void keyDown (gameRole &role, char map[13][13], char &die, int keyi,
  int keyj, int &i, int &j, int &level, char &iffin)
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
        }
      }
      break;

    case 'F':
    //check if the player wants to end the game
      cout << "Do you want to finish the game and stop fighting with monsters? ";
      cin >> iffin;
      iffin = tolower(iffin);
      if (iffin == 'y') {
        die = 'y';
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


void change_map (char map[13][13]) {
  for (int i = 0; i < 13; ++i) {
    for (int j = 0; j < 13; ++j) {
      if (map[i][j] == '*') {
        map[i][j] = ' ';
      }
    }
  }
}


void changeback_map (char map[13][13]) {
  for (int i = 0; i < 13; ++i) {
    for (int j = 0; j < 13; ++j) {
      if (map[i][j] == ' ') {
        map[i][j] = '*';
      }
    }
  }
}
