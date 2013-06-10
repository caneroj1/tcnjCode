/*
 *  TeamLeader.cpp
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#include "TeamLeader.h"

//constructor
TeamLeader::TeamLeader (int rowIn, int colIn, Colors colorIn) : Piece (rowIn, colIn, colorIn)
{
	pieceType = 5;
}

//alternative constructor that determines team based on an int
TeamLeader::TeamLeader (int rowIn, int colIn, int colorIn)
{
	if (colorIn == 0)
		player = GREEN;
	if (colorIn == 1)
		player = YELLOW;
	setRow (rowIn);
    setCol (colIn);
	pieceType = 5;
}

//destructor
TeamLeader::~TeamLeader ()
{
	;
}

//the doMove function calculates this piece's valid range of movement
//teamLeaders move like knights
bool TeamLeader::doMove (int tRow, int tCol)
{
	int rowDistance = abs(row - tRow);
	int colDistance = abs(col - tCol);
	
	if (rowDistance != 0 && colDistance != 0)
	{
		if (rowDistance == 2 && colDistance == 1) {
			return true;
		}
		
		if (rowDistance == 1 && colDistance == 2) {
			return true;
		}
		else {
			return false;
		}
	}
	
	return false;
}

//returns a string representation of this object
string TeamLeader::object2string () const
{
	string name;
	
    if (player == GREEN)
		name = "g";
    else if (player == YELLOW)
		name = "y";
    name = name + "T";
    return name;
	
}

//is real piece
bool TeamLeader::isRealPiece() const
{
	return true;
}

//TeamLeader Destructor Beam Cannon. Up Down Y Combo