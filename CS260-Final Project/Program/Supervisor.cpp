/*
 *  Supervisor.cpp
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#include "Supervisor.h"

//constructor
Supervisor::Supervisor (int rowIn, int colIn, Colors colorIn) : Piece (rowIn, colIn, colorIn)
{
	pieceType = 4;
}

//alternative constructor that determines team based on an int
Supervisor::Supervisor (int rowIn, int colIn, int colorIn)
{
	if (colorIn == 0)
		player = GREEN;
	if (colorIn == 1)
		player = YELLOW;
	setRow (rowIn);
    setCol (colIn);
	pieceType = 4;
}

//destructor
Supervisor::~Supervisor ()
{
	;
}

//the doMove function calculates this piece's valid range of movement
//supervisors move like bishops
bool Supervisor::doMove (int tRow, int tCol)
{
	int rowDistance = abs(row - tRow);
	int colDistance = abs(col - tCol);
	
	if (rowDistance != 0 && colDistance != 0)
	{
		if (rowDistance == colDistance) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}     

//returns a string represenation of this object
string Supervisor::object2string () const
{
	string name;
	
    if (player == GREEN)
		name = "g";
    else if (player == YELLOW)
		name = "y";
    name = name + "S";
    return name;

}

//is a real piece
bool Supervisor::isRealPiece () const
{
	return true;
}