/*
 *  Manager.cpp
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#include "Manager.h"

//constructor
Manager::Manager (int rowIn, int colIn, Colors colorIn) : Piece (rowIn, colIn, colorIn)
{
	pieceType = 3;
}

//alternative constructor that determines team based on an int
Manager::Manager (int rowIn, int colIn, int colorIn)
{
	if (colorIn == 0)
		player = GREEN;
	if (colorIn == 1)
		player = YELLOW;
	setRow (rowIn);
    setCol (colIn);
	pieceType = 3;
}

//destructor
Manager::~Manager ()
{
	;
}

//the doMove function calculates this piece's valid range
//managers move like rooks
bool Manager::doMove (int tRow, int tCol)
{
	int rowDistance = abs(row - tRow);
	int colDistance = abs(col - tCol);
	
	if (rowDistance != 0 || colDistance != 0)
	{
		if (rowDistance == 0) {
			return true;
		}
		
		if (colDistance == 0) {
			return true;
		}
		
		else {
			return false;
		}
	}
	
	return false;

}

//returns a string representation of this object
string Manager::object2string () const
{
	string name;
	
    if (player == GREEN)
		name = "g";
    else if (player == YELLOW)
		name = "y";
    name = name + "M";
    return name;
}

//is real piece
bool Manager::isRealPiece () const
{
	return true;
}
