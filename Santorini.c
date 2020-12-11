#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BOLDBLACK "\033[1m\033[30m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define RESET "\033[0m"

void startingPosition(int gameBoard[][7], int pPos[], int cPos[]) {

	/* determines the desired starting position of the player and intializes CPU position
	*  gameBoard[] is an array of the current game board state
	*  pPos[] is an array of the player's position
	*  cPos[] is an array of the CPU's position
	*/



	//prompt user for starting position
	printf("Choose your starting position! (x y)" "\n");
        scanf("%d %d", &pPos[0], &pPos[1]);
        while(pPos[0] > 6 || pPos[0] < 1) {
                printf("please choose an integer between 1-6!" "\n");
                printf("Choose your starting position! (x y)" "\n");
                scanf("%d %d", &pPos[0], &pPos[1] );
        }
	
	//CPU starts either one row above or below player depending on player location
	if(pPos[0] == 6) {
		cPos[0] = pPos[0] - 1;
	} else { 
		cPos[0] = pPos[0] + 1;
	}
	cPos[1] = pPos[1];
}

bool isValidMove(int checkPos[], int pPos[], int cPos[]) {

	// checks to see if the player's desired move is valid

	/* checkPos[] is an array of the player's desired next move
	*  pPos[] is an array of the player's current position
	*  cPos[] is an array of the CPU's current position	
	*/ 

	//check if move is where the player already is
	if(checkPos[0] == pPos[0] && checkPos[1] == pPos[1]) {
		printf("invalid move: player already there!" "\n");
		return false;
	}
        
	//check if move is where opponent is
	if(checkPos[0] == cPos[0] && checkPos[1] == cPos[1]) {
                printf("invalid move: opponent already there!" "\n");
		return false;
        }
	
	//check if move is out of bounds
	if(checkPos[0] > 6 || checkPos[0] < 1 || checkPos[0] < 1 || checkPos[1] > 6) {
		printf("invalid move: out of bounds!" "\n");
		return false;
	}

	//check if move is within one space of current space
	if(abs(checkPos[0] - pPos[0]) > 1 || abs(checkPos[1] - pPos[1]) > 1) {
		printf("invalid move: can't move that far!" "\n");
		return false;
	}
	return true;

}

void userMovePrompt (int pPos[], int cPos[]) { 

	/*
	* prompts the user to determine the player's next move. Uses isValidMove as a
	* helper method.
	*
	* pPos is an array of the player's current coordinates
	* cPos is an array of the CPU's current coordinates
	*/

        int tempPos[2]; // holds value of desired next move
        bool isValid;   // true if the next move is a valid one

	//find the intended coordinates of next player move
        printf("Choose your next move! (x y)" "\n");
        scanf("%d %d", &tempPos[0], & tempPos[1]);
        isValid = isValidMove(tempPos, pPos, cPos);

        if(isValid == true) {
        pPos[0] = tempPos[0];
	pPos[1] = tempPos[1];
        return;
        } else {
        userMovePrompt(pPos, cPos);
	}

}

bool isGameOver(int gameBoard[][7]) {

	//Checks if either player has won
	//gameBoard is an array of the current game board state

	//iterate through board and check for 0's and 4's
	int numFour = 0; int numZero = 0;
	for(int i = 1; i < 7; ++i) {
		for(int j = 1; j < 7; ++j) {
			if(gameBoard[i][j] == 4) {
				++numFour;
			}
			if(gameBoard[i][j] == 0) {
				++numZero;
			}
		}
	}
	
	//print player and CPU Score
	printf("Player Score: %i" "\n", numFour);
	printf("Computer Score: %i" "\n", numZero);

	//check if there are 10 4's (Player wins) or 10 0's (CPU wins)
	if(numFour >= 10) {
		printf("Game Over: Player Wins!" "\n");
		return true;
	} else if(numZero >= 10) {
		printf("GameOver: Computer Wins!" "\n");
		return true;
	} else {
		return false;
	}

}
       
void updateBoardPlayer(int gameBoard[][7], int pPos[], int cPos[]) {

	/* updates the building levels based on player's position
	*  gameBoard is the game board's current state
	*  pPos is the player's current coordinates
	*  cPos is the CPU's current coordinates
	*/

	int i, j; // hold the pPos values temporarily to iterate across the board

	//level up all of the vertical buildings
	for(i = pPos[0] + 1; i < 7; ++i) {
		if(i == cPos[0] && pPos[1] == cPos[1]) {
			break;
		}
		if(gameBoard[i][pPos[1]] < 4) {
			gameBoard[i][pPos[1]] = gameBoard[i][pPos[1]] + 1;
		}
	}

	for(i = pPos[0] - 1; i > 0; --i) {
                if(i == cPos[0] && pPos[1] == cPos[1]) {
                        break;
                }
                if(gameBoard[i][pPos[1]] < 4) {
                        gameBoard[i][pPos[1]] = gameBoard[i][pPos[1]] + 1;
                }
        }

	//level up horizontal buildings
	for(j = pPos[1] + 1; j < 7; ++j) {
		if(j == cPos[1] && pPos[0] == cPos[0]) {
			break;
		}
		if(gameBoard[pPos[0]][j] < 4) {
			gameBoard[pPos[0]][j] = gameBoard[pPos[0]][j] + 1;
		}
	}

        for(j = pPos[1] - 1; j > 0; --j) {
                if(j == cPos[1] && pPos[0] == cPos[0]) {
                        break;
                }
                if(gameBoard[pPos[0]][j] < 4) {
                        gameBoard[pPos[0]][j] = gameBoard[pPos[0]][j] + 1;
                }
        }

	//level up buildings bottom right diagonal
	for(i = pPos[0] + 1, j = pPos[1] + 1; i < 7 && j < 7; ++i, ++j) {
		if(i == cPos[0] && j == cPos[1]) {
			break;
		}
		if(gameBoard[i][j] < 4) {
			gameBoard[i][j] = gameBoard[i][j] + 1;
		}
	}

	//level up buildings top left diagonal
        for(i = pPos[0] - 1, j = pPos[1] - 1; i > 0 && j > 0; --i, --j) {
                if(i == cPos[0] && j == cPos[1]) {
                        break;
                }
                if(gameBoard[i][j] < 4) {
                        gameBoard[i][j] = gameBoard[i][j] + 1;
                }
        }

	//level up buildings top right diagonal
        for(i = pPos[0] + 1, j = pPos[1] - 1; i < 7 && j > 0; ++i, --j) {
                if(i == cPos[0] && j == cPos[1]) {
                        break;
                }
                if(gameBoard[i][j] < 4) {
                        gameBoard[i][j] = gameBoard[i][j] + 1;
                }
        }

	//level up buildings bottom left diagonal
        for(i = pPos[0] - 1, j = pPos[1] + 1; i > 0 && j < 7; --i, ++j) {
                if(i == cPos[0] && j == cPos[1]) {
                        break;
                }
                if(gameBoard[i][j] < 4) {
                        gameBoard[i][j] = gameBoard[i][j] + 1;
                }
        }
}

void moveCPU(int gameBoard[][7], int pPos[], int cPos[]) {

	/* AI Strategy: seeks out largest value in its octagon, first checking top left space
	*  gameBoard is the game board's current state
	*  pPos is the coordinates of the player's position
	*  cPos is the coordinates of the CPU's position
	*/

	//stores coordinates of 8 surrounding squares
	int coords[8][2] = {
		{cPos[0] - 1, cPos[1] - 1},
		{cPos[0], cPos[1] - 1},
		{cPos[0] + 1, cPos[1] - 1},
		{cPos[0] + 1, cPos[1]},
		{cPos[0] + 1, cPos[1] + 1},
		{cPos[0] - 1, cPos[1] + 1},
		{cPos[0], cPos[1] + 1},
		{cPos[0] - 1, cPos[1]}
	};

	//array of the scores of the towers within its octagon
	int vals[8] = {
		gameBoard[cPos[0] - 1][cPos[1] - 1],
		gameBoard[cPos[0]][cPos[1] - 1],
		gameBoard[cPos[0] + 1][cPos[1] - 1],
                gameBoard[cPos[0] + 1][cPos[1]],
                gameBoard[cPos[0] + 1][cPos[1] + 1],
		gameBoard[cPos[0] - 1][cPos[1] + 1],
                gameBoard[cPos[0]][cPos[1] + 1],
		gameBoard[cPos[0] - 1][cPos[1]],
        };

	//check to see if player is already there, or if at edge
	for(int i = 0; i < 8; ++i) {
		int checkPos[2] = {coords[i][0], coords[i][1]};
		if(checkPos[0] == pPos[0] && checkPos[1] == pPos[1]) {
			vals[i] = -1;
		}
		if(checkPos[0] < 1 || checkPos[1] < 1 || checkPos[0] > 6 || checkPos[1] > 6) {
			vals[i] = -1;
		}
	}

	//determine which square has the highest number
	int maxVal = 0;
	int position = 0;
	for(int k = 0; k < 8; ++k) {
		if(vals[k] > maxVal) {
			maxVal = vals[k];
			position = k;
		}
	}

	cPos[0] = coords[position][0];
	cPos[1] = coords[position][1];
	
}

void updateBoardCPU(int gameBoard[][7], int pPos[], int cPos[]) {

        /* updates the building levels based on CPU's position
        *  gameBoard is the game board's current state
        *  pPos is the player's current coordinates
        *  cPos is the CPU's current coordinates
        */

        int i, j; //hoold values of cPos temporarily to iterate across the board

        //level down all of the vertical buildings
        for(i = cPos[0] + 1; i < 7; ++i) {
                if(i == pPos[0] && cPos[1] == pPos[1]) {
                        break;
                }
                if(gameBoard[i][cPos[1]] > 0) {
                        gameBoard[i][cPos[1]] = gameBoard[i][cPos[1]] - 1;
                }
        }

        for(i = cPos[0] - 1; i > 0; --i) {
                if(i == pPos[0] && cPos[1] == pPos[1]) {
                        break;
                }
                if(gameBoard[i][cPos[1]] > 0) {
                        gameBoard[i][cPos[1]] = gameBoard[i][cPos[1]] - 1;
                }
        }

        //level down horizontal buildings
        for(j = cPos[1] + 1; j < 7; ++j) {
                if(j == pPos[1] && cPos[0] == pPos[0]) {
                        break;
                }
                if(gameBoard[cPos[0]][j] > 0) {
                        gameBoard[cPos[0]][j] = gameBoard[cPos[0]][j] - 1;
                }
        }

        for(j = cPos[1] - 1; j > 0; --j) {
                if(j == pPos[1] && cPos[0] == pPos[0]) {
                        break;
                }
                if(gameBoard[cPos[0]][j] > 0) {
                        gameBoard[cPos[0]][j] = gameBoard[cPos[0]][j] - 1;
                }
        }

        //level down buildings bottom right diagonal
        for(i = cPos[0] + 1, j = cPos[1] + 1; i < 7 && j < 7; ++i, ++j) {
                if(i == pPos[0] && j == pPos[1]) {
                        break;
                }
                if(gameBoard[i][j] > 0) {
                        gameBoard[i][j] = gameBoard[i][j] - 1;
                }
        }

        //level down buildings top left diagonal
        for(i = cPos[0] - 1, j = cPos[1] - 1; i > 0 && j > 0; --i, --j) {
                if(i == pPos[0] && j == pPos[1]) {
                        break;
                }
                if(gameBoard[i][j] > 0) {
                        gameBoard[i][j] = gameBoard[i][j] - 1;
                }
        }

        //level down buildings top right diagonal
        for(i = cPos[0] + 1, j = cPos[1] - 1; i < 7 && j > 0; ++i, --j) {
                if(i == pPos[0] && j == pPos[1]) {
                        break;
                }
                if(gameBoard[i][j] > 0) {
                        gameBoard[i][j] = gameBoard[i][j] - 1;
                }
        }

        //level down buildings bottom left diagonal
        for(i = cPos[0] - 1, j = cPos[1] + 1; i > 0 && j < 7; --i, ++j) {
                if(i == pPos[0] && j == pPos[1]) {
                        break;
                }
                if(gameBoard[i][j] > 0) {
                        gameBoard[i][j] = gameBoard[i][j] - 1;
                }
        }
}


void printBoard(int gameBoard[][7], int pPos[], int cPos[]) {
 
	/* iterates through the board and prints it out
        *  gameBoard is the game board's current state
        *  pPos is the player's current coordinates
        *  cPos is the CPU's current coordinates
        */

	int toPrint;
	for(int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			toPrint = gameBoard[i][j];
			if(pPos[0] == i && pPos[1] == j) {
				//player is bold green
				printf(BOLDGREEN  "A " RESET);
			} else if(cPos[0] == i && cPos[1] == j) {
				//CPU is bold red
				printf(BOLDRED  "C " RESET);
			} else if(i == 0 || j == 0) {
				// axis labels are bold black
				printf(BOLDBLACK "");
				printf("%d ", toPrint);
				printf("" RESET);
			} else {
				printf("%d ", toPrint);
			}
		}
		printf("\n");
	}	

}

int main (void) {

	int pPos[2]; int cPos[2]; //coordinate arrays of player position and CPU position

	int gameBoard[7][7] = { //gameboard
                 {0, 1, 2, 3, 4, 5, 6},
                 {1, 2, 2, 2, 2, 2, 2},
                 {2, 2, 2, 2, 2, 2, 2},
                 {3, 2, 2, 2, 2, 2, 2},
                 {4, 2, 2, 2, 2, 2, 2},
                 {5, 2, 2, 2, 2, 2, 2},
                 {6, 2, 2, 2, 2, 2, 2}
	};

	startingPosition(gameBoard, pPos, cPos);  
	printBoard(gameBoard, pPos, cPos);

	while(!isGameOver(gameBoard)) {
		printf("\n");
		userMovePrompt(pPos, cPos);
		updateBoardPlayer(gameBoard, pPos, cPos);
		printBoard(gameBoard, pPos, cPos);
		if(isGameOver(gameBoard)) {
			break;
		}
		printf("\n");
		moveCPU(gameBoard, pPos, cPos);
		updateBoardCPU(gameBoard, pPos, cPos);
		printBoard(gameBoard, pPos, cPos);
	}

	return 0;

}
