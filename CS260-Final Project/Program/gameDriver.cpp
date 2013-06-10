// gameDriver.cpp
// Driver program to test a game loosely based on chess
// Programmed By: Monisha Pulimood for use in CSC 260
//                
// 
//
/////////////////


#include "GameBoard.h"

#include <iostream>
using namespace std;


//**************************************MAINTENENANCE INFORMATION**************************************
/*
 CHANGES: In this cpp file, I added functions that do all sorts of input checking with user entered values.
          Also, this the function to calculate if the game is a draw returns a boolean which indicates to the 
          program which processing path to take.
          The name of the input file was hardcoded in, but if the file is not found, the program will ask for a file.
 */
//*****************************************************************************************************

// You may edit this driver as long as the basic functionality and class / method names remain the same.
// I will be using this driver to test ALL submitted programs.

//**********************************************************************************************************************************
bool inValidRange (int);
void getValidInput (int&, int&, int&, int&);
bool userInCheck (int&);

//**********************************************************************************************************************************
int main (void)
{
    //initializes an ifstream
	ifstream initBoardStr;
    
    /* The name of the file is hard coded in initially. If the file opening operation fails
     the program goes into a loop where it asks the user for the name of the file to be read in.
     */
    
	string initBoardFile = "newBoard.txt";
	initBoardStr.open(initBoardFile.c_str());
    
    if (initBoardStr.fail()) {
        initBoardStr.clear();
        bool openSucc = true;
        do {
            cerr << "That file operation failed." << endl;
            cout << "Reopening. File Name: ";
            cin >> initBoardFile;
            initBoardStr.open(initBoardFile.c_str());
            if (initBoardStr.fail()) {
                initBoardStr.clear();
                openSucc = false;
            }
            else
                openSucc = true;
        } while (!openSucc);
    }
    
    GameBoard newBoard(initBoardStr); //initializes a new game board with the input data from the ifstream
	
	int option, gameEndOpt;
	int fromRow, toRow;
	int fromCol, toCol;

	bool gameEnd = false;
    
    while (!gameEnd) 
	{
        //output the current board
        
		cout << "The current board is:" << endl;
		cout << newBoard.object2string();
        
        //a function was added to validate if the user's input is correct.
        //if the input is incorrect, this code block will loop until a correct choice
        //is made by the user
        
        do
        {
            cout << "What do you want to do?" << endl;
            cout << "(1) Make a move" << endl;
            cout << "(2) End the game" << endl;
        } while(!userInCheck(option));
        
		switch (option)
		{
			case 1: // Make a move
				gameEnd = false;
                
                //this function was added to determine if the coordinates entered by the user are correct
                //if even one parameter is outside the range of a valid chess board, the user will need to
                //reenter correct coordinates
                
				getValidInput(fromRow, fromCol, toRow, toCol);
                
                //checks if a move at this location to the specified location can be conducted.
                
				if (newBoard.doMove (fromRow, fromCol, toRow, toCol))
					cout << "Move Succeeded\n";
				else
					cout << "*** Invalid Move ***\n";
				break;
			case 2: //End the game
			{
				gameEnd = true;
				bool tryEndAgain = true;
				while (tryEndAgain)
				{
					tryEndAgain = false;
                    
                    //this code block checks to see if the game is currently a draw with the addition of a new function
                    //if the game is not a draw, the user is asked the results of the game
                    //processing resumes as usual
                    
                    if (!newBoard.checkIfDraw())
                    {
                        do
                        {
                            cout << "How did the game end?" << endl;
                            cout << "(1) Green Won" << endl;
                            cout << "(2) Yellow Won" << endl;
                            cout << "(3) Green Resigned" << endl;
                            cout << "(4) Yellow Resigned" << endl;
                            cout << "(5) It's a Draw" << endl;
                            cout << "(6) OOPS! Continue Game" << endl;
                        }while (!userInCheck(gameEndOpt));
                    }
                    
                    //if the game is a draw, there will be no user input and the program automatically
                    //assigns the input value to 5
                    
                    if (newBoard.checkIfDraw()) {
                        gameEndOpt = 5;
                    }
                    
					switch (gameEndOpt) {
						case 1: // Green Won
							cout << "Green gains " << WIN << " points" << endl;
							break;
						case 2: // Yellow Won
							cout << "Yellow gains " << WIN << " points" << endl;
							break;
						case 3: // Green Resigns
							cout << "Yellow gains " << RES_WIN << " points" << endl;
							cout << "Green forfeits " << RES_LOSE << " points" << endl;
							break;
						case 4: // Yellow Resigns
							cout << "Green gains " << RES_WIN << " points" << endl;
							cout << "Yellow forfeits " << RES_LOSE << " points" << endl;
							break;
						case 5: // Draw
							cout << "Green gains " << DRAW << " points" << endl;
							cout << "Yellow gains " << DRAW << " points" << endl;
							break;
						case 6:   // Don't end game
							cout << "Continuing Game" << endl;
							gameEnd = false;
							break;
						default:
							cout << "Invalid game end option" << endl;
							tryEndAgain = true;
							break;
					} // end switch (gameEndOpt)
				} // while (tryEndAgain)
				break;
			}
			default:
				gameEnd = false;
				cout << "Invalid option" << endl;
				break;
		} // end switch (option)
	} // while (!gameEnd) 
} // end main

//**********************************************************************************************************************************
bool inValidRange (int val)
{
    /*
     this function checks to see if the value is
     within the appropriate range of a board
     */
    
	if (val >= 0 && val < 8) {
		return true;
	}
	else {
        cout << "That input needs to be in the range of 0 to 8, exclusive." << endl;
        return false;
    }
}

//**********************************************************************************************************************************
void getValidInput (int& fromRow, int& fromCol, int& toRow, int& toCol)
{
    /*
     this function checks all of the user input when inputting board coordinates
     if any of the values are outside the valid range of a board, they must be reentered
     the function inValidRange is called to determine if the value is correct
     */
    
    //input checks the fromRow
	bool inSuccess = false;
	do {
		cout << "Enter row of piece to move: ";
		cin >> fromRow;
		if (cin.fail()) {
            cerr << "That input is invalid." << endl;
			cin.clear();
            cin.ignore(80, '\n');
		}
		else {
			if(inValidRange(fromRow))
				inSuccess = true;
		}
	} while (!inSuccess);
	
    //input checks the fromCol
	inSuccess = false;
	do {
		cout << "Enter column of piece to move: ";
		cin >> fromCol;
		if (cin.fail()) {
            cerr << "That input is invalid." << endl;
			cin.clear();
            cin.ignore(80, '\n');
		}
		else {
			if(inValidRange(fromCol))
				inSuccess = true;
		}
	} while (!inSuccess);
	
    //input checks the toRow
	inSuccess = false;
	do {
		cout << "Enter row of place to move to: ";
		cin >> toRow;
		if (cin.fail()) {
            cerr << "That input is invalid." << endl;
			cin.clear();
            cin.ignore(80, '\n');
		}
		else {
			if(inValidRange(toRow))
				inSuccess = true;
		}
	} while (!inSuccess);
	
    //input checks the toCol
	inSuccess = false;
	do {
		cout << "Enter column of place to move to: ";
		cin >> toCol;
		if (cin.fail()) {
            cerr << "That input is invalid." << endl;
			cin.clear();
            cin.ignore(80, '\n');
		}
		else {
			if(inValidRange(toCol))
				inSuccess = true;
		}
	} while (!inSuccess);
}

bool userInCheck (int& input)
{
    //error checks any input
    //this is used to check whether the user enters the correct menu option
    bool inSuccess = false;
    
    do {
        cin >> input;
        if (cin.fail()) {
            cerr << "That input is invalid" << endl;
            cin.clear();
            cin.ignore(80, '\n');
        }
        else
            inSuccess = true;
    }while (!inSuccess);
    
    return inSuccess;
}
//**********************************************************************************************************************************