/*
 *  President.h
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#if ! defined (PRESIDENT_H)
#define PRESIDENT_H

#include "Piece.h"

class President : public Piece
{
public:
	/****************************************
	 Parameterized Constructor 1
	 Postcondition: a President object is created
	 Parameters: int, int, an enum
	 ****************************************/
	President(int, int, Colors=YELLOW);
	
	/****************************************
	 Parameterized Constructor 2
	 Postcondition: a President object is created
	 Parameters: int, int, int
	 
	 --Assigns team by last int parameter
	 ****************************************/
	President(int, int, int);
	
	/****************************************
	 Destructor
	 Postcondition: President object is destroyed
	 ****************************************/
	~President ();
	
	/****************************************
	 doMove()
	 Precondition: a move wants to be made
	 Postcondition: a bool is returned indicating whether the move would be possible
	 Parameters: int, int
	 Returns: a bool
	 
	 --the first int indicates the desired row
	 --the second int indicates the desired column
	 ****************************************/
	bool doMove (int, int);
	
	/****************************************
	 object2string()
	 Postcondition: a string representation of the President object is returned
	 Returns: a string 
	 ****************************************/
	string object2string () const;
	
	/****************************************
	 isRealPiece
	 Postcondition: bool is returned indicating if this is a derived piece
	 Returns: a bool
	 
	 ****************************************/
	bool isRealPiece() const;
};
#endif