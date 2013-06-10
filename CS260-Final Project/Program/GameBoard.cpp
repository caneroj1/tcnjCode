// GameBoard.cpp
// 
// Includes sample methods for some classes that may used as is 
//              or modified as needed
// This is a "SKELETON" definition so you will need to add more code as 
//              appropriate -- DONE
// Programmed By: Monisha Pulimood for use in CSC 260
//                
//
/////////////////


//**************************************MAINTENENANCE INFORMATION**************************************
/*
 CHANGES: In this cpp file, I decomposed the move functions for each piece and initialized the game board
          to null before piece objects are created

                                                                                                     */
//*****************************************************************************************************

#include "GameBoard.h"
#include <sstream>
#include <iomanip>
#include <stdlib.h>

//*****************************************************************************************************************************

GameBoard::GameBoard (ifstream& initStr)
{
	/*
     This constructor calls the private function initBoard. This abstracts creation of the board away from the user. All they must
     worry about is the initial instantiation of the GameBoard object
     */
	
    initBoard(initStr);
}

//*****************************************************************************************************************************

//This method reads piece data from a file and creates the board based off of the input.

//File entries are of the form int(0-7) int(0-7) int (1-6) int(0-1)
//Entries are new line delimited

void GameBoard::initBoard (ifstream& initStr)
{
	int row = 0, col = 0, pieceType = -1;
	int play = 0;
	Colors player = YELLOW;
	
    
    //INITIALIZE ARRAY TO ALL NULL VALUES
    for (int i = 0; i < MROWS; i++) {
        for (int j = 0; j < MCOLS; j++)
        {
            board[i][j] = NULL;
        }
    }
    
    //reads Piece data for as long as there is input in the file
	while (!initStr.eof())
	{
        
        // Each line in the input file represents a piece
        // The first 2 values are for the row and column of the piece's 
        //       position
        // The third value is the type of piece (President, CEO, etc.)
        // The fourth value is the type of player - Green or Yellow
        
		initStr >> row; //read in the row
		initStr >> col; //read in the column
		initStr >> pieceType; //read in the pieceType
		initStr >> play; //read in an int. the int indicates the team of the piece
        
		if (play == 0) { //if the int is 0, the piece belongs on the green team
			player = GREEN;
		}
		
		if (play == 1) { //if the int is 1, the piece belongs on the red team
			player = YELLOW;
		}
        
		// This skeleton version assumes data entered are valid and so does no 
        //         input error checking
        
		//This code block relies on the user's creating of a file that is valid. Users must make the input file correctly
        
		switch (pieceType) {
			case PRESIDENT: // To handle President piece
                       // dynamically create and allocate a President object at 
                       // the location (row, col) on the board.
                board [row][col] = new President(row, col, player);
				break;
			
                //dynamically allocates the appropriate piece at the board location
			case MANAGER:
				board [row][col] = new Manager(row, col, player);
				break;
			case DEVELOPER:
				board [row][col] = new Developer(row, col, player);
				break;
			case CEONUM:
				board [row][col] = new CEO(row, col, player);
				break;
			case SUPERVISOR:
				board [row][col] = new Supervisor(row, col, player);
				break;
			case TEAMLEADER:
				board [row][col] = new TeamLeader(row, col, player);
				break;
            default:
				board [row][col] = NULL;
				break;
				
		} // end switch (pieceType)
	} // end while (!eof)
} // end initBoard()

//*****************************************************************************************************************************

bool GameBoard::checkIfDraw()
{
    
    //A game is a draw if both players have went 50 turns without capturing a piece or moving a developer
    if (turnsSinceDevMove == 100 || turnsSinceCapture == 100)
        return true;
    if (turnsSinceDevMove != 100 && turnsSinceCapture != 100)
        return false;
}

//*****************************************************************************************************************************

bool GameBoard::doMove (int fromRow, int fromCol, int toRow, int toCol)
{
    //This doMove function determines what type of piece the user wishes to move.
    //There will either only be correct pieces or null at the spaces the user wishes to move a piece.
    //This is due to the switch statement defaulting to creating a space that is null if the input data is correct in conjunction
    //with the initial initialization of the board to null.
    
	//IF THERE IS NO PIECE AT THE SPECIFIED LOCATION
	if (board[fromRow][fromCol] == NULL) {
		return false; //no piece can be moved if there is no piece there
	}
	   
    //determines what type of piece there is to be moved and returns true or false depending on if the piece can move to that spot
    
    //IF THE PIECE IS A DEVELOPER
    if (board[fromRow][fromCol]->getItemType() == DEVELOPER)
        return (moveDeveloper(fromRow, fromCol, toRow, toCol));
    
    //IF THE PIECE IS A CEO
    if (board[fromRow][fromCol]->getItemType() == CEONUM)
        return (moveCEO(fromRow, fromCol, toRow, toCol));
    
    //IF THE PIECE IS A MANAGER
    if (board[fromRow][fromCol]->getItemType() == MANAGER)
        return (moveManager(fromRow, fromCol, toRow, toCol));
    
    //IF THE PIECE IS A SUPERVISOR
    if (board[fromRow][fromCol]->getItemType() == SUPERVISOR)
        return (moveSupervisor(fromRow, fromCol, toRow, toCol));
    
    //IF THE PIECE IS A TEAMLEADER
    if (board[fromRow][fromCol]->getItemType() == TEAMLEADER)
        return (moveTeamLeader(fromRow, fromCol, toRow, toCol));
    
    //IF THE PIECE IS A PRESIDENT
    if (board[fromRow][fromCol]->getItemType() == PRESIDENT)
        return (movePresident(fromRow, fromCol, toRow, toCol));
}

//*****************************************************************************************************************************

string GameBoard::object2string () const
{
    //This is the function that displays the board
    //Creates as accurate a representation as possible for a command line implementation
    
    ostringstream os;
	os << setw(5) << " ";
    for (int j = 0; j < MCOLS; j++)
		os << setw(5) << j;
    os << endl;
    for (int i = 0; i < MROWS; i++) {
		os << setw(5) << i;
		for (int j = 0; j < MCOLS; j++)
		{
			if (board[i][j] != NULL) {
                os << setw(5) << board[i][j]->object2string();
			}
			if (board[i][j] == NULL) {
				os << setw(5) << " ";
			}
		}
		os << endl;
	}
    os << endl;
	
    return os.str();
}

//*****************************************************************************************************************************

bool GameBoard::moveDeveloper (int fromRow, int fromCol, int toRow, int toCol)
{
    //*****************************************************************************************************************************
	//DO MOVE FOR DEVELOPER
	//THE DEVELOPER MOVES LIKE A PAWN
	if (board[fromRow][fromCol]->getItemType() == DEVELOPER) {
		if (board[fromRow][fromCol]->doMove(toRow, toCol)) {
			//if the piece wants to move diagonally
			if (toCol != fromCol) {
				//if the piece is on green team, moving down, so the row must be greater
				if (board[fromRow][fromCol]->getColor() == 0 && toRow > fromRow)
				{
					if (board[toRow][toCol] == NULL) {
						return false;
					}
					if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
						
						//do the move
						delete board[toRow][toCol];
						board[toRow][toCol] = NULL;
						board[toRow][toCol] = new Developer(toRow, toCol, board[fromRow][fromCol]->getColor());
						delete board[fromRow][fromCol];
						board[fromRow][fromCol] = NULL;
                        
                        //RESET DEVELOPER COUNTER AND CAPTURE COUNTER
                        turnsSinceDevMove = 0;
                        turnsSinceCapture = 0;
                        
						return true;
					}
				}
				if (board[fromRow][fromCol]->getColor() == 0 && toRow < fromRow)
					return false;
				//if the piece is on yellow team, moving up, so the row must be lesser
				if (board[fromRow][fromCol]->getColor() == 1 && toRow < fromRow)
				{
					if (board[toRow][toCol] == NULL) {
						return false;
					}
					if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
						
						//do the move
						delete board[toRow][toCol];
						board[toRow][toCol] = NULL;
						board[toRow][toCol] = new Developer(toRow, toCol, board[fromRow][fromCol]->getColor());
						delete board[fromRow][fromCol];
						board[fromRow][fromCol] = NULL;
                        
                        //RESET DEVELOPER COUNTER AND CAPTURE COUNTER
                        turnsSinceDevMove = 0;
                        turnsSinceCapture = 0;
                        
						return true;
					}
				}
				if (board[fromRow][fromCol]->getColor() == 1 && toRow > fromRow)
					return false;
			}
			//if the piece is moving vertically
			if (toCol == fromCol) {
				//if the piece is moving up 1
				//if the piece is on green, moving down
				if (board[fromRow][fromCol]->getColor() == 0)
				{
                    if (toRow > fromRow)
                    {
                        if (board[toRow][toCol] == NULL) {
                            //do the move
                            board[toRow][toCol] = new Developer(toRow, toCol, board[fromRow][fromCol]->getColor());
                            delete board[fromRow][fromCol];
                            board[fromRow][fromCol] = NULL;
                            
                            //NO CAPTURE IS BEING MADE, DEVELOPER IS BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove = 0;
                            
                            return true;
                        }
                        if (board[toRow][toCol] != NULL) {
                            return false;
                        }
                    }
				}
				//if the piece is on yellow, moving up
				if (board[fromRow][fromCol]->getColor() == 1)
				{
                    if (toRow < fromRow)
                    {
                        if (board[toRow][toCol] == NULL) {
                            //do the move
                            board[toRow][toCol] = new Developer(toRow, toCol, board[fromRow][fromCol]->getColor());
                            delete board[fromRow][fromCol];
                            board[fromRow][fromCol] = NULL;
                            
                            //NO CAPTURE IS BEING MADE, DEVELOPER IS BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove = 0;
                            return true;
                        }
                        if (board[toRow][toCol] != NULL) {
                            return false;
                        }
                    }
				}
				//if the piece is moving up 2
				if (abs(toRow-fromRow) == 2)
				{
					//if on green team, therefore moving down
					if (board[fromRow][fromCol]->getColor() == 0) {
						if (board[fromRow][fromCol+1] == NULL) {
							if (board[toRow][toCol] == NULL) {
								//do the move
								board[toRow][toCol] = new Developer(toRow, toCol, board[fromRow][fromCol]->getColor());
								delete board[fromRow][fromCol];
								board[fromRow][fromCol] = NULL;
                                
                                //NO CAPTURE IS BEING MADE, DEVELOPER IS BEING MOVED
                                turnsSinceCapture++;
                                turnsSinceDevMove = 0;
								return true;
							}
						}
						if (board[fromRow][fromCol+1] != NULL)
							return false;
					}
					//if on yellow team, therefore moving up
					if (board[fromRow][fromCol]->getColor() == 1) {
						if (board[fromRow][fromCol-1] == NULL) {
							if (board[toRow][toCol] == NULL) {
								//do the move
								board[toRow][toCol] = new Developer(toRow, toCol, board[fromRow][fromCol]->getColor());
								delete board[fromRow][fromCol];
								board[fromRow][fromCol] = NULL;
                                
                                //NO CAPTURE IS BEING MADE, DEVELOPER IS BEING MOVED
                                turnsSinceCapture++;
                                turnsSinceDevMove = 0;
								return true;
							}
						}
						if (board[fromRow][fromCol-1] != NULL)
							return false;
					}
				}
			}
		}
		else return false;
	}
    //*****************************************************************************************************************************
}

bool GameBoard::moveCEO (int fromRow, int fromCol, int toRow, int toCol)
{
    //*****************************************************************************************************************************
	//DO MOVE FOR CEO
	//CEO MOVES LIKE QUEEN
    
    bool collisionOnPath = false;
    
	if (board[fromRow][fromCol]->getItemType() == CEONUM) {
		if (board[fromRow][fromCol]->doMove(toRow, toCol)) {
			//the move is valid
			// check if moving horizontally
			if (fromRow == toRow) {
				//if moving to the left
				if (toCol < fromCol) {
					for (int colNum = toCol + 1; colNum < fromCol; colNum++) {
						if (board[fromRow][colNum] != NULL && collisionOnPath == false) {
							collisionOnPath = true;
						}
					}
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
					if (collisionOnPath) {
						return false;
					}
				}
				//if moving to the right
				if (toCol > fromCol) {
					for (int colNum = fromCol + 1; colNum < toCol; colNum++) {
						if (board[fromRow][colNum] != NULL && collisionOnPath == false) {
							collisionOnPath = true;
						}
					}
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
					if (collisionOnPath) {
						return false;
					}
				}
			}
			//check if moving vertically
			if (fromCol == toCol) {
				//if moving UP
				if (toRow < fromRow) {
					for (int rowNum = toRow + 1; rowNum < fromRow; rowNum++) {
						if (board[rowNum][fromCol] != NULL && collisionOnPath == false) {
							collisionOnPath = true;
						}
					}
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
					if (collisionOnPath) {
						return false;
					}
				}
				//if moving DOWN
				if (toRow > fromRow) {
					for (int rowNum = fromRow + 1; rowNum < toRow; rowNum++) {
						if (board[rowNum][fromCol] != NULL && collisionOnPath == false) {
							collisionOnPath = true;
						}
					}
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
					if (collisionOnPath) {
						return false;
					}
				}
			}
			//check if moving diagonally
			//IF MOVING UP AND RIGHT
			if (toCol > fromCol && toRow < fromRow) {
				for (int rowNum = fromRow-1, colNum = fromCol+1; rowNum > toRow && colNum < toCol; rowNum--, colNum++) {
					if (board[rowNum][colNum] != NULL && collisionOnPath == false) {
						collisionOnPath = true;
					}
				}
				if (!collisionOnPath) {
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
				}
				if (collisionOnPath) {
					return false;
				}
			}
			//IF MOVING UP AND LEFT
			if (toCol < fromCol && toRow < fromRow) {
				for (int rowNum = fromRow-1, colNum = fromCol-1; rowNum > toRow && colNum < toCol; rowNum--, colNum--) {
					if (board[rowNum][colNum] != NULL && collisionOnPath == false) {
						collisionOnPath = true;
					}
				}
				if (!collisionOnPath) {
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
				}
				if (collisionOnPath) {
					return false;
				}
			}
			//IF MOVING DOWN AND RIGHT
			if (toCol > fromCol && toRow > fromRow) {
				for (int rowNum = fromRow+1, colNum = fromCol+1; rowNum > toRow && colNum < toCol; rowNum++, colNum++) {
					if (board[rowNum][colNum] != NULL && collisionOnPath == false) {
						collisionOnPath = true;
					}
				}
				if (!collisionOnPath) {
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
				}
				if (collisionOnPath) {
					return false;
				}
			}
			//IF MOVING DOWN AND LEFT
			if (toCol < fromCol && toRow > fromRow) {
				for (int rowNum = fromRow+1, colNum = fromCol-1; rowNum > toRow && colNum < toCol; rowNum++, colNum--) {
					if (board[rowNum][colNum] != NULL && collisionOnPath == false) {
						collisionOnPath = true;
					}
				}
				if (!collisionOnPath) {
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new CEO(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
				}
				if (collisionOnPath) {
					return false;
				}
			}
		}
		else return false;
	}
    //*****************************************************************************************************************************
}

bool GameBoard::moveManager (int fromRow, int fromCol, int toRow, int toCol)
{
    //*****************************************************************************************************************************
	//DO MOVE FOR MANAGER
	//MANAGER MOVES LIKE ROOK, ONLY HORIZONTALLY OR ONLY VERTICALLY
    
    bool collisionOnPath = false;
    
	if (board[fromRow][fromCol]->getItemType() == MANAGER) {
		if (board[fromRow][fromCol]->doMove(toRow, toCol)) {
			// check if moving horizontally
			if (fromRow == toRow) {
				//if moving to the left
				if (toCol < fromCol) {
					for (int colNum = toCol + 1; colNum < fromCol; colNum++) {
						if (board[fromRow][colNum] != NULL && collisionOnPath == false) {
							collisionOnPath = true;
						}
					}
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new Manager(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new Manager(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
					if (collisionOnPath) {
						return false;
					}
				}
				//if moving to the right
				if (toCol > fromCol) {
					for (int colNum = fromCol + 1; colNum < toCol; colNum++) {
						if (board[fromRow][colNum] != NULL && collisionOnPath == false) {
							collisionOnPath = true;
						}
					}
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new Manager(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new Manager(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
					if (collisionOnPath) {
						return false;
					}
				}
			}
			//check if moving vertically
			if (fromCol == toCol) {
				//if moving UP
				if (toRow < fromRow) {
					for (int rowNum = toRow + 1; rowNum < fromRow; rowNum++) {
						if (board[rowNum][fromCol] != NULL && collisionOnPath == false) {
							collisionOnPath = true;
						}
					}
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new Manager(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new Manager(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
					if (collisionOnPath) {
						return false;
					}
				}
				//if moving DOWN
				if (toRow > fromRow) {
					for (int rowNum = fromRow + 1; rowNum < toRow; rowNum++) {
						if (board[rowNum][fromCol] != NULL && collisionOnPath == false) {
							collisionOnPath = true;
						}
					}
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new Manager(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new Manager(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
					if (collisionOnPath) {
						return false;
					}
				}
			}
		}
		else return false;
	}
    //*****************************************************************************************************************************
}

bool GameBoard::moveSupervisor (int fromRow, int fromCol, int toRow, int toCol)
{
    //*****************************************************************************************************************************
	//DO MOVE FOR SUPERVISOR
	//SUPERVISOR MOVES LIKE JAGGER
    
    bool collisionOnPath = false;
    
	if (board[fromRow][fromCol]->getItemType() == SUPERVISOR) {
		if (board[fromRow][fromCol]->doMove(toRow, toCol)) {
			//check if moving diagonally
			//IF MOVING UP AND RIGHT
			if (toCol > fromCol && toRow < fromRow) {
				for (int rowNum = fromRow-1, colNum = fromCol+1; rowNum > toRow && colNum < toCol; rowNum--, colNum++) {
					if (board[rowNum][colNum] != NULL && collisionOnPath == false) {
						collisionOnPath = true;
					}
				}
				if (!collisionOnPath) {
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new Supervisor(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new Supervisor(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
				}
				if (collisionOnPath) {
					return false;
				}
			}
			//IF MOVING UP AND LEFT
			if (toCol < fromCol && toRow < fromRow) {
				for (int rowNum = fromRow-1, colNum = fromCol-1; rowNum > toRow && colNum < toCol; rowNum--, colNum--) {
					if (board[rowNum][colNum] != NULL && collisionOnPath == false) {
						collisionOnPath = true;
					}
				}
				if (!collisionOnPath) {
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new Supervisor(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new Supervisor(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
				}
				if (collisionOnPath) {
					return false;
				}
			}
			//IF MOVING DOWN AND RIGHT
			if (toCol > fromCol && toRow > fromRow) {
				for (int rowNum = fromRow+1, colNum = fromCol+1; rowNum > toRow && colNum < toCol; rowNum++, colNum++) {
					if (board[rowNum][colNum] != NULL && collisionOnPath == false) {
						collisionOnPath = true;
					}
				}
				if (!collisionOnPath) {
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new Supervisor(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new Supervisor(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
				}
				if (collisionOnPath) {
					return false;
				}
			}
			//IF MOVING DOWN AND LEFT
			if (toCol < fromCol && toRow > fromRow) {
				for (int rowNum = fromRow+1, colNum = fromCol-1; rowNum > toRow && colNum < toCol; rowNum++, colNum--) {
					if (board[rowNum][colNum] != NULL && collisionOnPath == false) {
						collisionOnPath = true;
					}
				}
				if (!collisionOnPath) {
					if (!collisionOnPath) {
						//if there is a piece on the final spot
						if (board[toRow][toCol] != NULL  && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
							//do the move
							delete board[toRow][toCol];
							board[toRow][toCol] = NULL;
							board[toRow][toCol] = new Supervisor(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture = 0;
                            turnsSinceDevMove++;
							return true;
						}
						//if piece is on same team
						if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
							return false;
						//if there is no piece on the final spot
						if (board[toRow][toCol] == NULL) {
							//do the move
							board[toRow][toCol] = new Supervisor(toRow, toCol, board[fromRow][fromCol]->getColor());
							delete board[fromRow][fromCol];
							board[fromRow][fromCol] = NULL;
                            
                            //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                            turnsSinceCapture++;
                            turnsSinceDevMove++;
							return true;
						}
					}
				}
				if (collisionOnPath) {
					return false;
				}
			}
		}
		else return false;
	}
    //*****************************************************************************************************************************
}

bool GameBoard::moveTeamLeader(int fromRow, int fromCol, int toRow, int toCol)
{
    //*****************************************************************************************************************************
	//DO MOVE FOR TEAM LEADER
	//TEAM LEADER MOVES LIKE KNIGHT
    
    bool collisionOnPath = false;
    
	if (board[fromRow][fromCol]->getItemType() == TEAMLEADER) {
		if (board[fromRow][fromCol]->doMove(toRow, toCol)) {
			//if the destination does not have a piece
			if (board[toRow][toCol] == NULL) {
				//do the move
				board[toRow][toCol] = new TeamLeader(toRow, toCol, board[fromRow][fromCol]->getColor());
				delete board[fromRow][fromCol];
				board[fromRow][fromCol] = NULL;
                
                //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                turnsSinceCapture++;
                turnsSinceDevMove++;
				return true;
			}
			//if the destination is filled
			if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
				//do the move
				delete board[toRow][toCol];
				board[toRow][toCol] = NULL;
				board[toRow][toCol] = new TeamLeader(toRow, toCol, board[fromRow][fromCol]->getColor());
				delete board[fromRow][fromCol];
				board[fromRow][fromCol] = NULL;
                
                //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                turnsSinceCapture = 0;
                turnsSinceDevMove++;
				return true;
			}
			//if piece is on same team
			if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
				return false;
		}
		else return false;
	}
	//*****************************************************************************************************************************
}

bool GameBoard::movePresident(int fromRow, int fromCol, int toRow, int toCol)
{
    //*****************************************************************************************************************************
	//DO MOVE FOR PRESIDENT
	//PRESIDENT MOVES LIKE KING
    
    bool collisionOnPath = false;
    
	if (board[fromRow][fromCol]->getItemType() == PRESIDENT) {
		if (board[fromRow][fromCol]->doMove(toRow, toCol)) {
			//if the destination does not have a piece
			if (board[toRow][toCol] == NULL) {
				//do the move
				board[toRow][toCol] = new President(toRow, toCol, board[fromRow][fromCol]->getColor());
				delete board[fromRow][fromCol];
				board[fromRow][fromCol] = NULL;
                
                //CAPTURE IS NOT BEING MADE, DEVELOPER IS NOT BEING MOVED
                turnsSinceCapture++;
                turnsSinceDevMove++;
				return true;
			}
			//if the destination is filled
			if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() != board[fromRow][fromCol]->getColor()) {
				//do the move
				delete board[toRow][toCol];
				board[toRow][toCol] = NULL;
				board[toRow][toCol] = new President(toRow, toCol, board[fromRow][fromCol]->getColor());
				delete board[fromRow][fromCol];
				board[fromRow][fromCol] = NULL;
                
                //CAPTURE IS BEING MADE, DEVELOPER IS NOT BEING MOVED
                turnsSinceCapture = 0;
                turnsSinceDevMove++;
				return true;
			}
			//if piece is on same team
			if (board[toRow][toCol] != NULL && board[toRow][toCol]->getColor() == board[fromRow][fromCol]->getColor())
            {
                cout << "COLOR PROBLEM" << endl;
				return false;
            }
		}
		else return false;
	}
    //*****************************************************************************************************************************
}


