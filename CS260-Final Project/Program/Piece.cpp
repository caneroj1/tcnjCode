//  Piece.cpp
// 
// This is a "SKELETON" definition so you will need to add more code as 
//              appropriate
// Programmed By: Monisha Pulimood for use in CSC 260
//                
// DO: Add maintenance information 
/////////////////


#include "Piece.h"

//constructor
Piece::Piece (int inRow, int inCol, Colors inColor)
{
    setRow (inRow);
    setCol (inCol);
    player = inColor;
	pieceType = 0;
}

//destructor
Piece::~Piece ()
{
	;
}

//isRealPiece
//a piece is not a real piece
bool Piece::isRealPiece() const
{
    return false;
}

//string representation of a piece
string Piece::object2string () const
{
    return string ("  ");
}

//doMove
//this function is overrided in the child classes
bool Piece::doMove (int tRow, int rCol)
{
	;
}

//returns an int indicating what team this piece is on
int Piece::getColor ()
{
	return player;
}

//a mutator method to set the row of a piece
void Piece::setRow (int inRow)
{
	row = inRow;
}

//a mutator method to set the column of a piece
void Piece::setCol (int inCol)
{
	col = inCol;
}

//returns an int indicating what type of piece the piece is
int Piece::getItemType ()
{
	return pieceType;
}