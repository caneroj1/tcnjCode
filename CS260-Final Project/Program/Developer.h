/*
 *  Developer.h
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#if ! defined (DEVELOPER_H)
#define DEVELOPER_H

#include "Piece.h"

class Developer : public Piece {
public:
	/****************************************
	 Parameterized Constructor 1
	 Postcondition: a Developer object is created
	 Parameters: int, int, an enum
	 
	 ****************************************/
	Developer(int, int, Colors=YELLOW);
	
	/****************************************
	 Parameterized Constructor 2
	 Postcondition: a CEO object is created
	 Parameters: int, int, int
	 
	 --the last int determines the team
	 ****************************************/
	Developer(int, int, int);
	
	/****************************************
	 Destructor
	 Postcondition: Developer object is destroyed
	 ****************************************/
	~Developer ();
	
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
	 Postcondition: a string representation of the Developer object is returned
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


#endif  // PIECE_H