/*
 *  President.cpp
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#include "President.h"

//constructor
President::President(int rowIn, int colIn, Colors colorIn) : Piece (rowIn, colIn, colorIn)
{
	pieceType = 1;
}

//alternative constructor that determines team based on an int
President::President(int rowIn, int colIn, int colorIn)
{
	if (colorIn == 0)
		player = GREEN;
	if (colorIn == 1)
		player = YELLOW;
	setRow (rowIn);
    setCol (colIn);
	pieceType = 1;
}

//destructor
President::~President ()
{
	;
}

//the doMove function calculates this piece's valid range of movement
//Presidents move like Kings
bool President::doMove(int tRow, int tCol)
{
    int rowDistance = abs(row - tRow);
    int colDistance = abs(col - tCol);
	if (rowDistance != 0 || colDistance != 0)
	{
		if (rowDistance > 1 || colDistance > 1) {
			return false;
		}
		
		else return true;
	}
	return false;
}

//determines if it is a real piece
bool President::isRealPiece () const
{
    return true;
}

//returns a string representation
string President::object2string () const
{
    string name;
	
    if (player == GREEN)
		name = "g";
    else if (player == YELLOW)
		name = "y";
    name = name + "P";
    return name;
}

