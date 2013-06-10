//  GameBoard.h
// Skeleton code for GameBoard class definition
// Programmed By: Monisha Pulimood for use in CSC 260
//                
// DO: Add maintenance information 
// This is a "SKELETON" definition so you will need to add documentation, 
//      attributes, methods and code as appropriate
//
/////////////////


#if !defined (GAMEBOARD_H)
#define GAMEBOARD_H

#include <iostream>
#include <fstream>

#include "Piece.h"
#include "President.h"
#include "Manager.h"
#include "Developer.h"
#include "CEO.h"
#include "Supervisor.h"
#include "TeamLeader.h"

using namespace std;

const int MROWS = 8;
const int MCOLS = 8;
const int WIN = 10; 
const int RES_LOSE = -2; 
const int RES_WIN = 7; 
const int DRAW = 5; 


class GameBoard 
{
	
private:
	// DO: Add attributes here
    // The 2-d array is called board
	
	/****************************************
	 initBoard
	 Precondition: a game board is needed
	 Postcondition: a game board is created
	 Parameters: an ifstream object used to read in board data from a file
	 Returns: void
	 ****************************************/
	void initBoard (ifstream&);
	
    
    int turnsSinceCapture; //counter to keep track of turns since capture
                           //if both players alternate correctly, this counter should be 100 since each player expends 50 turns
                           //without a capture
    
    int turnsSinceDevMove; //counter to keep track of turns since a Developer has moved
                           //if both players alternate correctly, this counter should be 100 since each player must go 50 turns
                           //without moving a Developer
    
	Piece* board[MROWS][MCOLS]; //the two-dimensional array that is the game board
	
public:
	/****************************************
	 GameBoard constructor
	 Postcondition: a gameboard is created
	 Parameters: an ifstream object
	 ****************************************/
    GameBoard (ifstream&);
	
	/****************************************
	 doMove()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move is successfully made
	 Parameters: int, int, int, int
	 Returns: a bool
	 
	 --the first int indicates the starting row
	 --the second int indicates the starting column
	 --the third int indicates the ending row
	 --the fourth int indicates the ending column
	 ****************************************/
	bool doMove(int, int, int, int);
	
	/****************************************
	 object2string()
	 Postcondition: a string representation of the GameBoard is returned
	 Returns: a string 
	 
	 --this outputs the entire board and the state of all of the pieces
	 --the game board is an 8x8 square
	 ****************************************/
    string object2string () const;
    // DO: Add methods here
    
    /****************************************
	 moveDeveloper()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move can be successfully made
	 Parameters: int, int, int, int
	 Returns: a bool
	 
	 --the first int indicates the starting row
	 --the second int indicates the starting column
	 --the third int indicates the ending row
	 --the fourth int indicates the ending column
	 ****************************************/
    bool moveDeveloper(int, int, int, int);
    
    /****************************************
	 moveCEO()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move can be successfully made
	 Parameters: int, int, int, int
	 Returns: a bool
	 
	 --the first int indicates the starting row
	 --the second int indicates the starting column
	 --the third int indicates the ending row
	 --the fourth int indicates the ending column
	 ****************************************/
    bool moveCEO(int, int, int, int);
    
    /****************************************
	 moveManager()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move can be successfully made
	 Parameters: int, int, int, int
	 Returns: a bool
	 
	 --the first int indicates the starting row
	 --the second int indicates the starting column
	 --the third int indicates the ending row
	 --the fourth int indicates the ending column
	 ****************************************/
    bool moveManager(int, int, int, int);
    
    /****************************************
	 moveSupervisor()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move can be successfully made
	 Parameters: int, int, int, int
	 Returns: a bool
	 
	 --the first int indicates the starting row
	 --the second int indicates the starting column
	 --the third int indicates the ending row
	 --the fourth int indicates the ending column
	 ****************************************/
    bool moveSupervisor(int, int, int, int);
    
    /****************************************
	 moveTeamLeader()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move can be successfully made
	 Parameters: int, int, int, int
	 Returns: a bool
	 
	 --the first int indicates the starting row
	 --the second int indicates the starting column
	 --the third int indicates the ending row
	 --the fourth int indicates the ending column
	 ****************************************/
    bool moveTeamLeader(int, int, int, int);
    
    /****************************************
	 movePresident()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move can be successfully made
	 Parameters: int, int, int, int
	 Returns: a bool
	 
	 --the first int indicates the starting row
	 --the second int indicates the starting column
	 --the third int indicates the ending row
	 --the fourth int indicates the ending column
	 ****************************************/
    bool movePresident(int, int, int, int);
    
    /****************************************
     checkIfDraw()
     Precondition: check if game is draw
     Postcondition: returns whether or not the game is a draw
     Parameters: none
     Returns: bool
     ****************************************/
    bool checkIfDraw();
};

#endif  // GAMEBOARD_H
