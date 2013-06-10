/*
 *  CEO.cpp
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#include "CEO.h"

//constructor, calls the super constructor
CEO::CEO (int rowIn, int colIn, Colors colorIn) : Piece (rowIn, colIn, colorIn)
{
	pieceType = 2;
}

//alternative constructor that uses an int to determine team
CEO::CEO (int rowIn, int colIn, int colorIn)
{
	if (colorIn == 0)
		player = GREEN;
	if (colorIn == 1)
		player = YELLOW;
	setRow (rowIn);
    setCol (colIn);
	pieceType = 2;
}

//destructor
CEO::~CEO ()
{
	;
}

//the doMove function calculates this piece's valid range of movement
//CEO's move like a Queen: any amount of open space in a vertical, horizontal, or diagonal fashion
bool CEO::doMove (int tRow, int tCol)
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
		
		if (rowDistance == colDistance) {
			return true;
		}
	}
	
	return false;
}

//returns this object's string representation
string CEO::object2string () const
{
	string name;
	
    if (player == GREEN)
		name = "g";
    else if (player == YELLOW)
		name = "y";
    name = name + "C";
    return name;
}

//indicates whether this is a real piece 
bool CEO::isRealPiece() const
{
	return true;
}