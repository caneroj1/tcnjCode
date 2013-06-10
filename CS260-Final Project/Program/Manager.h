/*
 *  Manager.h
 *  
 *
 *  Created by Joseph Canero on 12/7/12.
 *  CSC260
 *  Dr. Pulimood
 *  Final Exam Program
 */

#if ! defined (MANAGER_H)
#define MANAGER_H

#include "Piece.h"

class Manager : public Piece {
public:
	/****************************************
	 Parameterized Constructor 1
	 Postcondition: a Manager object is created
	 Parameters: int, int, an enum
	 ****************************************/
	Manager(int, int, Colors=YELLOW);
	
	/****************************************
	 Parameterized Constructor 2
	 Postcondition: a Manager object is created
	 Parameters: int, int, int
	 
	 --Assigns team by last int parameter
	 ****************************************/
	Manager(int, int, int);
	
	/****************************************
	 Destructor
	 Postcondition: Manager object is destroyed
	 ****************************************/
	~Manager ();
	
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
	 Postcondition: a string representation of the Manager object is returned
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