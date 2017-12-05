///@file checkers.cc
///@brief Code for all the functions defined in checkers.h
///@author Chase Gindlesperger

/**
 *	Chase Gindlesperger
 *	Checkers.cc
 *
 *	CS3560 Term Project
*/


#include <string>
#include "game.h"
#include "checkers.h"

using namespace std;

namespace main_savitch_14 {

	checkers::checkers(){

	///@brief Constructor - sets the board up to start the game. Makes the pieces red, black, or empty where they should be.

		int i, j;
		blackcount = 12;
		redcount = 12;

		for(i = 0; i < 8; i++) {
			for(j = 0; j < 8; j++) {
				if(j == 0 || j == 2) {
					if(i % 2 == 1) {
						board[i][j].setempty(false);
						board[i][j].setred(false);
						board[i][j].setking(false);
					}
				} else if(j == 1) {
					if(i % 2 == 0) {
						board[i][j].setempty(false);
						board[i][j].setred(false);
						board[i][j].setking(false);
					}
				} else if(j == 5 || j == 7) {
					if(i % 2 == 0) {
						board[i][j].setempty(false);
						board[i][j].setred(true);
						board[i][j].setking(false);
					}
				}else if(j == 6) {
					if(i % 2 == 1) {
						board[i][j].setempty(false);
						board[i][j].setred(true);
						board[i][j].setking(false);
					}
				}else {
						board[i][j].setempty(true);
						board[i][j].setred(false);
						board[i][j].setking(false);
				}
			}
		}

	}


	void checkers::restart() {
	///@brief Resets the game board by calling the constructor

		checkers();
	}

/*	void checkers::display_status() const{
        	int i, j;
		char letter;
		letter = 'A';
		cout << "  ";
		for(i = 1; i <= 8; i++) {
			cout << " " << letter << " ";
			letter++;
		}
		cout << endl;

        	for(i = 0; i < 8; i ++){
			cout << RESET << i+1 << " ";

                	if(i % 2 == 0){ // Even Rows
                        	for(j = 0; j < 8; j++){
                                	if(j % 2 == 0){  //Even columns in even rows are red
                                        	cout << B_BLACK;
						board[j][i].output();
                                 	} else { //Odd columns in even rows are black
                                        	cout << B_WHITE;
						board[j][i].output();
                                 	}
                        	}
                        	cout << RESET << endl;
                	}

                	else { // Odd Rows
                        	for(j = 0; j < 8; j++) {
                                	if(j % 2 == 0) { // Even columns in odd rows are black
                                        	cout << B_WHITE;
						board[j][i].output();
                                	} else { // Odd columns in odd rows are red
						cout << B_BLACK;
						board[j][i].output();
                                	}
                         	}
                        	cout << RESET << endl;
                	}
        	}
*/
	void checkers::display_status() const {
	///@brief Displays the updated board

        	int i, k, j;
		char letter;
		letter = 'A';
		cout << "  ";
		for(i = 1; i <= 8; i++) {
			cout << "     " << letter << "   ";
			letter ++;
		}
		cout << endl;

       		for(i = 0; i < 8; i ++){
               		if(i % 2 == 0){ // Even Rows
				cout << RESET << "   ";

				for(j=0; j < 8; j++) {
					//cout << "  ";

					if(j % 2 == 0){
						cout << B_BLACK << "         ";
					}else {
						cout << B_WHITE << "         ";
					}
				}
				cout << RESET << endl;

				cout << RESET << " " << i+1 << " ";

        	       		for(k = 0; k < 8; k++){
                			if(k % 2 == 0){  //Even columns in even rows are black
						cout << B_BLACK << "   ";
                                		cout << B_BLACK;
						board[k][i].output();
						cout << B_BLACK << "   ";
                        		}else { //Odd columns in even rows are white
						cout << B_WHITE << "   ";
                                		cout << B_WHITE;
						board[k][i].output();
						cout << B_WHITE << "   ";
                        		}
                		}
				cout << RESET << endl;

				cout << RESET << "   ";

	                	for(j=0; j < 8; j++) {
					//cout << "  ";

					if(j % 2 == 0){
         		               		cout << B_BLACK << "         ";
                        		}else {
                         			cout << B_WHITE << "         ";
                        		}
               			}

                		cout << RESET << endl;
			}

			else { // Odd Rows
				cout << RESET << "   ";

                        	for(j=0; j < 8; j++) {
                                	//cout << "  ";

					if(j % 2 == 0){
                                       		cout << B_WHITE << "         ";
                               		}else {
                                       		cout << B_BLACK << "         ";
                               		}
                       		}
				cout << RESET << endl;

				cout << RESET << " " << i+1 << " ";

                        	for(k = 0; k < 8; k++) {
                                	if(k % 2 == 0) { // Even columns in odd rows are white
                                    		cout << B_WHITE << "   ";
						cout << B_WHITE;
						board[k][i].output();
						cout << B_WHITE << "   ";
                                	} else { // Odd columns in odd rows are black
						cout << B_BLACK << "   ";
						cout << B_BLACK;
						board[k][i].output();
						cout << B_BLACK << "   ";
                                	}
                        	}

                        	cout << RESET << endl;

				cout << RESET << "   ";

        	                for(j=0; j < 8; j++) {
                	                //cout << "  ";

					if(j % 2 == 0){
                        	                cout << B_WHITE << "         ";
                                	}else {
                                        	cout << B_BLACK << "         ";
                                	}
                        	}
	        		cout << RESET << endl;
			}
        }
	}

	bool checkers::is_legal(const string& move) const{

	///@brief This function determines if a move is legal or illegal
	///@param const string& move
	///@return bool

		char c;
		int col1, row1, col2, row2;
		c = move[0];
		col1 = c - '0';
		col1 -= 48;

		c = move[1];
		row1 = c - '0';

		c = move[2];
		col2 = c - '0';
		col2 -= 48;

		c = move[3];
		row2 = c - '0';

		if(board[col1-1][row1-1].isempty())
			return false;
		if(!(board[col2-1][row2-1].isempty()))
        		return false;

		//MOVES ALLOWED FOR NORMAL PIECES
		if(!board[col1-1][row1-1].isking()) {
			//MOVES ALLOWED FOR HUMANS
			if(next_mover() == HUMAN){
				if(board[col1-1][row1-1].isred()){
					if(row2 == row1-1){
						if(col2 == col1-1 || col2 == col1+1)
							return true;
						else
							return false;
					}
					//JUMPING MOVES
					else if(row2 == row1 - 2) {
						if(col2 == col1 - 2) {
							if(!board[col1-2][row1-2].isempty()) {
								if(!board[col1-2][row1-2].isred())
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else if(col2 == col1 + 2) {
							if(!board[col1][row1-2].isempty()) {
								if(!board[col1][row1-2].isred())
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else
							return false;
					}
					 //else
						//return false;
		/*			//DOUBLE JUMPING MOVES
					else if(row2 == row1 - 4) {
						//DOUBLE TO THE LEFT
						if(col2 == col1 - 4) {
							if(!board[col1-4][row1-4].isempty()) {
								if(!board[col1-4][row1-4].isred()) {
									if(!board[col1-2][row1-2].isempty()) {
										if(!board[col1-2][row1-2].isred())
											return true;
										else
											return false;
									}
									 else
										return false;
								}
								 else
									return false;
							}
							 else
								return false;
						}
						//DOUBLE TO THE RIGHT
						else if(col2 == col1 + 4) {
							if(!board[col1+2][row1-4].isempty()) {
								if(!board[col1+2][row1-4].isred()) {
									if(!board[col1][row1-2].isempty()) {
										if(!board[col1][row1-2].isred())
											return true;
										else
											return false;
									}
									 else
										return false;
								}
								 else
									return false;
							}
							 else
								return false;
						}
						else if(col2 == col1) {
							//LEFT THEN RIGHT
							if(!board[col1-2][row1-2].isempty() && !board[col1-2][row1-4].isempty()) {
								if(!board[col1-2][row1-2].isred()) {
									if(!board[col1-2][row1-4].isred())
										return true;
									else
										return false;
								}
								else
									return false;
							}
							else
								return false;
							//RIGHT THEN LEFT
							if(!board[col1][row1-2].isempty() && !board[col1][row1-4].isempty()) {
								if(!board[col1][row1-2].isred()) {
									if(!board[col1][row1-4].isred())
										return true;
									else
										return false;
								}
								else
									return false;
							}
							else
								return false;
						}
						else
							return false;

					}	*/
					else
						return false;
				}
				else
					return false;
			}

			//MOVES ALLOWED FOR COMPUTER
			else if(next_mover() == COMPUTER) {
				if(!board[col1-1][row1-1].isred()){
					if(row1 == row2 -1) {
						if(col2 == col1-1 || col2 == col1+1)
							return true;
						else
							return false;
					}
					//JUMPING MOVES
					else if(row2 == row1 + 2) {
						if(col2 == col1 + 2) {
							if(!board[col1][row1].isempty()) {
								if(board[col1][row1].isred())
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else if(col2 == col1 - 2) {
							if(!board[col1-2][row1].isempty()){
								if(board[col1-2][row1].isred())
									return true;
								else
									return false;
							}
							else
								return false;
						}
						else
							return false;
					}
				/*	//DOUBLE JUMPING MOVES
					else if(row2 == row1 + 4) {
						//DOUBLE TO THE LEFT
						if(col2 == col1 + 4) {
							if(!board[col1+3][row1+3].isempty()) {
								if(!board[col1+3][row1+3].isred()) {
									if(!board[col1][row1].isempty()) {
										if(!board[col1][row1].isred())
											return true;
										else
											return false;
									}
									 else
										return false;
								}
								 else
									return false;
							}
							 else
								return false;
						}
						//DOUBLE TO THE RIGHT
						else if(col2 == col1 - 4) {
							if(!board[col1-4][row1-4].isempty()) {
								if(!board[col1-4][row1-4].isred()) {
									if(!board[col1-2][row1].isempty()) {
										if(!board[col1-2][row1].isred())
											return true;
										else
											return false;
									}
									 else
										return false;
								}
								 else
									return false;
							}
							 else
								return false;
						}
						else if(col2 == col1) {
							//LEFT THEN RIGHT
							if(!board[col1+3][row1+3].isempty() && !!board[col1][row1].isempty()) {
								if(!board[col1-2][row1-2].isred()) {
									if(!board[col1-2][row1-4].isred())
										return true;
									else
										return false;
								}
								else
									return false;
							}
							else
								return false;
							//RIGHT THEN LEFT
							if(!board[col1-4][row1-4].isempty() && !board[col1-2][row1].isempty()) {
								if(!board[col1][row1-2].isred()) {
									if(!board[col1][row1-4].isred())
										return true;
									else
										return false;
								}
								else
									return false;
							}
							else
								return false;
						}
						else
							return false;

					}	*/
					else
						return false;
				}
				else
					return false;
			}
		}

		//MOVES ALLOWED FOR KINGS
		else {
			if(next_mover() == HUMAN && !board[col1-1][row1-1].isred())
				return false;
			if(next_mover() == COMPUTER  && board[col1-1][row1-1].isred())
				return false;
			if(row1 == row2 - 1 || row1 == row2+1) {
				if(col2 == col1 -1 || col2 == col1+1)
					return true;
				else
					return false;
			} else if(row2 == row1 + 2) {
				if(col2 == col1 + 2){
					if(!board[col1][row1].isempty()) {
						if(board[col1-1][row1-1].isred() != board[col1][row1].isred())
							return true;
						else
							return false;
					}
					else
						return false;
				}
				else if(col2 == col1 - 2){
					if(!board[col1-2][row1].isempty()) {
						if(board[col1-1][row1-1].isred() != board[col1-2][row1].isred())
							return true;
						else
							return false;
					}
					else
						return false;
				}
				else
					return false;
			} else if (row2 == row1 - 2) {
				if(col2 == col1 + 2){
					if(!board[col1][row1-2].isempty()) {
						if(board[col1-1][row1-1].isred() != board[col1][row1-2].isred())
							return true;
						else
							return false;
					}
					else
						return false;
				}
				else if(col2 == col1 -2) {
					if(!board[col1-2][row1-2].isempty()) {
						if(board[col1-1][row1-1].isred() != board[col1-2][row1-2].isred())
							return true;
						else
							return false;
					}
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
		return false;
	}

	void checkers::make_move(const string& move){

	///@brief Allows for a move to be made
	///@param const string move passed by reference

		int col1, row1, col2, row2;
		char c;
		space tmp;
		bool doubleleft = false;

		c = move[0];
		col1 = c - '0';
		col1 -= 48;

		c = move[1];
		row1 = c - '0';

		c = move[2];
		col2 = c - '0';
		col2 -= 48;

		c = move[3];
		row2 = c - '0';

 		tmp = board[col2-1][row2-1];
		board[col2-1][row2-1] = board[col1-1][row1-1];
		board[col1-1][row1-1] = tmp;

		if(row2 == 1 || row2 == 8)
			board[col2-1][row2-1].setking(true);

		if(row2 == row1 - 2){
			if(col2 == col1 + 2){
				if(board[col1][row1-2].isred())
					redcount--;
				else
					blackcount--;

				board[col1][row1-2].setempty(true);

			}else if(col2 == col1 - 2) {
				if(board[col1-2][row1-2].isred())
					redcount--;
                		else
					blackcount--;

				board[col1-2][row1-2].setempty(true);
			}

        	}else if(row2 == row1 + 2) {
			if(col2 == col1 + 2) {
				if(board[col1][row1].isred())
					redcount--;
				else
					blackcount--;

				board[col1][row1].setempty(true);

			}else if(col2 == col1 - 2) {
				if(board[col1-2][row1].isred())
					redcount--;
				else
					blackcount--;

				board[col1-2][row1].setempty(true);
			}
		}else if(row2 == row1 - 4) {
			if(col2 == col1 - 4) {
				if(board[col1][row1].isred())
					redcount -= 2;
				else
					blackcount -= 2;
				board[col1-2][row1-2].setempty(true);
				board[col1-4][row1-4].setempty(true);
			}else if(col2 == col1 + 4) {
				if(board[col1][row1].isred())
					redcount -= 2;
				else
					blackcount -= 2;
				board[col1][row1-2].setempty(true);
				board[col1+2][row1-4].setempty(true);
			}else if(col2 == col1 && (!board[col1-2][row1-2].isred() && !board[col1-2][row1-4].isred() || board[col1-2][row1-2].isred() && board[col1-2][row1-4].isred())) {
				if(board[col1][row1].isred())
					redcount -= 2;
				else
					blackcount -= 2;
				board[col1-2][row1-2].setempty(true);
				board[col1-2][row1-4].setempty(true);
			}
			else if(col2 == col1 && (!board[col1][row1-2].isred() && !board[col1][row1-4].isred() || board[col1][row1-2].isred() && board[col1][row1-4].isred())) {
				if(board[col1][row1].isred())
					redcount -= 2;
				else
					blackcount -= 2;
				board[col1][row1-2].setempty(true);
				board[col1][row1-4].setempty(true);
				redcount -= 2;
			}
		}


		if(row2 == row1 + 2 || row2 == row1 - 2) {
			if(!board[col2-2][row2-2].isempty() && !board[col2-2][row2-2].isred())

				if(board[col2-1][row2-1].isred())

					if(board[col2-1][row2-1].isking()) {
						if(board[col2-2][row2-2].isred() != board[col2-1][row2-1].isred())
							if(board[col2-3][row2-3].isempty()) {
								tmp = board[col2-3][row2-3];
								board[col2-3][row2-3] = board[col2-1][row2-1];
								board[col2-1][row2-1] = tmp;
							}
					}

		}
		game::make_move(move);
	}


	bool checkers::is_game_over() const{
	///@brief Determines if the game is over
	///@details If there are no red pieces left, the game is over. If there are no black pieces left, the game is over.
	///@return bool

		if(redcount == 0) {
			clear();
			cout << "\t\t\t\tBlack Wins!\n" << endl;
			return true;
		} else if(blackcount == 0) {
			clear();
			cout << "\t\t\t\tRed Wins!\n" << endl;
			return true;
		} else
			return false;
	}

	void checkers::compute_moves(queue<string>& moves)const{
	///@brief Computes moves for the computer
	///@param queue of strings passed by reference

		string m = "    ";
		char i,j,k,l;
        	for(i = '1'; i < '9'; i++) {
                	for(j = 'a'; j < 'i'; j++) {
                        	for(k = '1'; k < '9'; k++) {
                                	for(l = 'a'; l < 'i'; l++) {
                                        	m[0] = j;
                                        	m[1] = i;
                                        	m[2] = l;
                                        	m[3] = k;
                                        	if(is_legal(m))
                                                	moves.push(m);
                                	}
                        	}
                	}
        	}
	}

	game::who checkers::winning() const {
	///@brief Decides who is currently winning
	///@details If red has more pieces on the board, return HUMAN. If black has more pieces on the board, return COMPUTER. If red and black have the same
	/// amount of pieces on the board return NEUTRAL.
	///@return HUMAN, COMPUTER, or NEUTRAL

		if(redcount > blackcount)
			return HUMAN;
		else if(blackcount > redcount)
			return COMPUTER;
		else
			return NEUTRAL;
	}

	int checkers::evaluate()const{
	///@brief Decides who has more piecs on the board
	///@return int - number of black pieces minus the number of red pieces

		return blackcount - redcount;
	}

	game* checkers::clone() const {
	///@brief creates a clone of the game
	///@return A new checkers object pointing to the current game

		return new checkers(*this);
	}
}
