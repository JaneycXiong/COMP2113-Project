#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "zuma.h"
using namespace std;


// define Ball, which is a linked list
struct Ball {
  char color;
  Ball *next;
};


// function prototype
void generate (Ball *&head, int);
void zuma_game (Ball *&head, char, int, int &);
void ballinsert (Ball *&, char);
void balldelete (Ball *&, int);
void balldeletehead (Ball *&head);
bool candelete(Ball *&head);
void printball (Ball *&head);



void zuma_main(int &point) {

  //print zuma game rules
  cout << "RULES \n" << endl;
  cout << "There is a randomly generated row of balls on the table. " << endl;
  cout << "you can determine the number of balls in the row. \n" << endl;
  cout << "You can insert 1 ball at once, and choose the color and position.\n" << endl;
  cout << "Each insertation, you may first input the color" << endl;
  cout << "You may choose color between R, Y, B, G, W.\n" << endl;
  cout << "Then you may input the position to insert the ball" << endl;
  cout << "For example, 0 means to insert the ball after the first 0 balls.\n" << endl;
  cout << "When there are 3 or more balls in the same color together,"
  << " they'll be deleted.\n" << endl;
  cout << "Use as few balls and as little time as possible to get high scores." << endl;

  // generate a random row of balls
  Ball *head = NULL;
  int numball;
  cout << "How many balls would you want on the table" << endl;
  cin >> numball;
  generate(head, numball);

  char c;
  int pos, numinsert;
  int len = numball;

  // start the game and record start time
  char ifstart;
  cout << "Press Y to start the game ";
  cin >> ifstart;
  ifstart = toupper(ifstart);
  while (ifstart != 'Y') {
    cout << "Press Y to start the game ";
    cin >> ifstart;
  }

  time_t starttime = time(NULL);


  cout << "The row of balls on the table: ";
  printball(head);

  while (head != NULL)
  {
    //record the color and position that the player wants to insert a ball

    cout << "Please input the color" << endl;
    cin >> c;
    c = toupper(c);
    while ( !(c == 'R' || c == 'Y' || c == 'B' || c == 'G' || c == 'W') ) {
      cout << "Please input a valid color." << endl;
      cin >> c;
      c = toupper(c);
    }

    cout << "Please input the position " << endl;
    cin >> pos;
    while ( pos > len || pos < 0) {
      cout << "Please input a valid position." << endl;
      cin >> pos;
    }

    //excute zuma game for each insertation and record no. of balls inserted
    zuma_game(head, c, pos, len);
    numinsert += 1;

    }

  // calculate how many points the player got
  time_t endtime = time(NULL);
  time_t timeused = endtime - starttime;
  point = 30 + numball*10 + (numball/numinsert*10) - timeused;
  cout << "You got " << point << " points!" << endl;
  cout << "You win! Welcome to the next game!" << endl;

}

void generate (Ball *&head, int numball) {
  for (int i = 1; i <= numball; ++i) {
    srand( i*i*time(NULL) );
    int n = rand() % 5;
    char b;
    n = n % 5;
    switch (n) {
      case 0:
        b = 'R';
        break;
      case 1:
        b = 'Y';
        break;
      case 2:
        b = 'B';
        break;
      case 3:
        b = 'G';
        break;
      case 4:
        b = 'W';
        break;
    }
    Ball *p = new Ball;
    p->color = b;
    p->next = head;
    head = p;
  }
}


void zuma_game (Ball *&head, char c, int pos, int &len)
{
  //insert a ball at specified position
  Ball * after = head;
  for (int i = 1; i < pos; ++i) {
      after = after->next;
  }

  ballinsert (after, c);

  len += 1;

  int nodel;
  Ball *delafter = head;
  while (candelete(head))
  {
    delafter = head;

    while ( (delafter != NULL) && (delafter->next != NULL) &&
    (delafter->next->next != NULL))
    {

      if (head->color == head->next->color &&
        head->next->color == head->next->next->color)
        // if the first several balls are the same color

      {
        Ball *count = head;
        nodel = 0;
        while (count != NULL && count->color == head->color) {
          nodel += 1;
          count = count->next;
        }

        for (int i = 0; i < nodel; ++i) {
          balldeletehead (head);
        }

        len = len - nodel;
        delafter = head;
      }

      else if (delafter->next->next->next != NULL &&
        delafter->next->color == delafter->next->next->color &&
        delafter->next->next->color == delafter->next->next->next->color)
        //if several balls in the middle are the same color

      {
        Ball *count = delafter;
        nodel = 0;
        while (count->next !=  NULL && count->next->color == delafter->next->color)

        {
          nodel += 1;
          count = count->next;
        }

        balldelete (delafter, nodel);
        len = len - nodel;

      }

      else
        //if no balls are the same color move delafter to the next one in the row
        delafter = delafter->next;
    }
  }

  cout << '\n';
  cout << "The row of balls on the table: ";
  printball(head);
  cout << "\n";
 }


// insert a ball
void ballinsert(Ball *&after, char c)
{
  Ball *p = new Ball;
  p->color = c;
  p->next = after->next;
  after->next = p;
}

// delete several balls
void balldelete(Ball *&after, int nodel)
{
  Ball *p = after;
  for (int i = 0; i < nodel; ++i) {
    if (p != NULL) {
      p = p->next;
    }
  }
  if (p != NULL) {
    after->next = p->next;
  }
  else
    after->next = NULL;
  delete p;
}


//delete the head of balls
void balldeletehead(Ball *&head)
{
	if (head != NULL) {
		Ball * p = head;
		head = head->next;
		delete p;
	}
}


//test if there are any balls can be deleted
bool candelete(Ball *&head)
{
  bool x = 0;
  Ball *delafter = head;
  while ( (delafter != NULL) && (delafter->next != NULL) &&
  (delafter->next->next != NULL))
  {

    if (head->color == head->next->color &&
      head->next->color == head->next->next->color)
      {
        x = 1;
        break;
      }

    else if (delafter->next->next->next != NULL &&
      delafter->next->color == delafter->next->next->color &&
      delafter->next->next->color == delafter->next->next->next->color)
      {
        x = 1;
        break;
      }

    else
    {
      delafter = delafter->next;
    }

  }
  return x;
}


//print the row of balls
void printball(Ball *&head)
{
  if (head == NULL) {
    cout << "there is no ball left";
  }
  else {
    Ball *current = head;
  	while (current != NULL) {
  		if (current->next != NULL) {
  			cout << current->color << " ";
  		}
  		else {
  			cout << current->color;
  		}
  		current = current->next;
  	}
  }

  cout << endl;
}
