//  Piece.h
// 
// This is a "SKELETON" definition so you will need to add more code as 
//              appropriate
// Programmed By: Monisha Pulimood for use in CSC 260
//                
// DO: Add maintenance information 
/////////////////

#if ! defined (PIECE_H)
#define PIECE_H

#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

//enumerated data type indicating the team each piece belongs to

enum Colors {GREEN, YELLOW};

//constant int variables used to indicate the type of piece

const int PRESIDENT = 1;
const int CEONUM = 2;
const int MANAGER = 3;
const int SUPERVISOR = 4;
const int TEAMLEADER = 5;
const int DEVELOPER = 6;


class Piece 
{
    
protected:
    int row; //the row of the piece
    int col; //the column of the piece
	int pieceType; //an int indicating what manner of piece the object is
    Colors player; //the team the piece is on
    
public:
	/****************************************
	 Parameterized Constructor 1
	 Postcondition: a Piece object is created
	 Parameters: int, int, an enum
	 ***************************************/
    Piece (int=0, int=0, Colors=YELLOW);
	
	/****************************************
	 setRow()
	 Precondition: the row of a piece needs to be set
	 Postcondition: the row is set
	 Parameters: int
	 Returns: void
	 ****************************************/
	void setRow (int);
	
	/****************************************
	 setCol()
	 Precondition: the col of a piece needs to be set
	 Postcondition: the col is set
	 Parameters: int
	 Returns: void
	 ****************************************/
	void setCol (int);
	
	/****************************************
	 getColor()
	 Precondition: the team needs to be known
	 Postcondition: an int indicating the color of the team is returned
	 Parameters: none
	 Returns: int
	 ****************************************/
	int getColor();
	
	/****************************************
	 Destructor
	 Postcondition: Piece object is destroyed
	 ****************************************/
	virtual ~Piece ();
	
	/****************************************
	 doMove()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move would be possible
	 Parameters: int, int
	 Returns: a bool
	 
	 --the first int indicates the desired row
	 --the second int indicates the desired column
	 ****************************************/
    virtual bool doMove(int, int);
	
	/****************************************
	 object2string()
	 Postcondition: a string representation of the Piece object is returned
	 Returns: a string 
	 ****************************************/
	virtual string object2string () const;
	
	/****************************************
	 isRealPiece
	 Postcondition: bool is returned indicating if this is a derived piece
	 Returns: a bool
	 ****************************************/
	virtual bool isRealPiece() const;
	
	/****************************************
	 getItemType
	 Precondition: the type of piece this is needs to be known
	 Postcondition: the type of piece is returned as an int
	 Parameters: none
	 Returns: int
	 
	 ****************************************/
	int getItemType();
	
};

#endif  // PIECE_H
