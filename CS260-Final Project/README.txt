Joe Canero
CSC260
Dr. Pulimood
Final Exam

——————————————————————————————————PROGRAM CHANGES——————————————————————————————————

			***CHANGES IN DRIVER***
In your driver, I added some functions to check for proper input. 



——————————————————————————————————PROGRAM INFO——————————————————————————————————

This program simulates a chess board, albeit one with a unique naming convention: all of the piece names are derived from the corporate hierarchy. This program is not fully encompassing in terms of scope; the only game condition it actively monitors is one form of a draw: if both players have spent 50 times without capture OR moving a Developer. This program does not monitor checks or checkmates, for it relies on the honor of the users to accurately report the status of the game.


——————————————————————————————————HOW TO PLAY——————————————————————————————————

A new board is automatically loaded when the program begins, and then play commences. The program prompts whether a move will be inputted or if the game is over. If a move is to be inputted, the program prompts for the row and column of the piece to be moved, and then the row and column of the destination to be moved to. If the move is valid, it will be depicted by a change in the outputted game board. If the move is invalid, the program will display an error message.

——————————————————————————————————ERROR HANDLING——————————————————————————————————

This program showcases many forms of error handling.

The program checks to see if the file hardcoded in can be opened, and if it cannot be opened, the program prompts the user for a new file.

User input is checked for validity and correctness. If the input is incorrect, an error message is displayed, and then the prompt for that data item continues until it is entered correctly.

When moving a piece, there are a variety of checks that come into play to determine if the move can actually be carried out. The program checks to see if the initial coordinates indicate a valid piece. If that array position is null, the move is invalid. If that array position does contain a piece, that piece’s move calculation function is called. In that function, it checks to see if the destination coordinates are valid for that piece’s acceptable movement range. If they are not, the move cannot be carried out and the move is therefore invalid. If the coordinates are valid, the game board then checks the state of the board to see if the move is possible. If there is another piece directly blocking the to-be-moved piece’s path, the move cannot be carried out; therefore, it is invalid. If there are no pieces in the way, it checks to see if the endpoint contains a piece. If the endpoint contains a piece, this indicates a capture. And if a capture is to be carried out, it must be on a piece from the opposite team; thus the game board checks to see if the to-be-captured piece is of a different team. If the teams are different, the piece is captured. If the teams are identical, the capture cannot be carried out; therefore, the move is invalid. If the endpoint does not contain a piece, the to-be-moved piece is placed there successfully.

Only the Developer piece has different movement rules: a Developer can move 2 spaces if and only if that move is that piece’s first; a Developer can only move forward if the destination place is empty; a Developer can only capture a piece if that piece is in a row ahead of the developer and immediately adjacent to the piece’s column. This is the only situation in which the Developer can capture or move diagonally.

——————————————————————————————————FINAL NOTES——————————————————————————————————

Thank you and enjoy.