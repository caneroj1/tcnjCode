/*
 *  Supervisor.h
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#if ! defined (SUPERVISOR_H)
#define SUPERVISOR_H

#include "Piece.h"

class Supervisor : public Piece {
public:
	/****************************************
	 Parameterized Constructor 1
	 Postcondition: a Supervisor object is created
	 Parameters: int, int, an enum
	 ****************************************/
	Supervisor(int, int, Colors=YELLOW);
	
	/****************************************
	 Parameterized Constructor 2
	 Postcondition: a Supervisor object is created
	 Parameters: int, int, int
	 
	 --Assigns team by last int parameter
	 ****************************************/
	Supervisor(int, int, int);
	
	/****************************************
	 Destructor
	 Postcondition: CEO object is destroyed
	 ****************************************/
	~Supervisor ();
	
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
	 Postcondition: a string representation of the Supervisor object is returned
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