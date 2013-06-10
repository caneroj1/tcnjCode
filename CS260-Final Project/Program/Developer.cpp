/*
 *  Developer.cpp
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#include "Developer.h"

//constructor
Developer::Developer (int rowIn, int colIn, Colors colorIn) : Piece (rowIn, colIn, colorIn)
{
	pieceType = 6;
}

//alternative constructor that determines team based on an int
Developer::Developer (int rowIn, int colIn, int colorIn)
{
	if (colorIn == 0)
		player = GREEN;
	if (colorIn == 1)
		player = YELLOW;
	setRow (rowIn);
    setCol (colIn);
	pieceType = 6;
}

//destructor
Developer::~Developer ()
{
	;
}

//doMove calculates this piece's valid range of movement
//Developers move like Pawns
bool Developer::doMove (int tRow, int tCol)
{
	int colDistance = abs(col - tCol);
	
	if (player == GREEN) { 
		int rowDistance = tRow - row; //compute the distance between the developer's row and the destination row
									  //since green developers on top of the game board, the distance must be positive
		if (colDistance == 1) {
			if (rowDistance == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		if (colDistance == 0) { //if the piece is moving vertically
			if (row == 1) { //if the piece is in its starting location
				if (rowDistance == 2) { //it can move 2 spaces
					return true;
				}
				if (rowDistance == 1) { //or 1
					return true;
				}
			}
			else {
				if (rowDistance == 2) { //if it isn't in its starting location, it cannot move 2
					return false;
				}
				if (rowDistance == 1) { //only 1
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	
	if (player == YELLOW) {
		int rowDistance = row - tRow; //compute the distance between the developer's row and the destination row
									  //since yellow developers are on top of the game board, the distance must be positive
		if (colDistance == 1) {
			if (rowDistance == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		if (colDistance == 0) {
			if (row == 6) {
				if (rowDistance == 2) {
					return true;
				}
				if (rowDistance == 1) {
					return true;
				}
			}
			else {
				if (rowDistance == 2) {
					return false;
				}
				if (rowDistance == 1) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
    
    return false;
}

//returns a string representation
string Developer::object2string () const
{
	string name;
	
    if (player == GREEN)
		name = "g";
    else if (player == YELLOW)
		name = "y";
    name = name + "D";
    return name;

}

//is a real piece
bool Developer::isRealPiece() const
{
	return true;
}