//Chase Gindlesperger
//Checkers.cc

#include <string>
#include "game.h"
#include "checkers.h"

using namespace std;

namespace main_savitch_14 {

	checkers::checkers(){
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


void checkers::display_status() const{
        int i, k,j;
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
				} else {
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
                                 } else { //Odd columns in even rows are white
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
                                } else {
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
                                } else {
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
                                } else {
                                        cout << B_BLACK << "         ";
                                }
                        }
                        cout << RESET << endl;


                }
        }
}

	void checkers::display_status() const{
        	int i, k;
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
                        	for(k = 0; k < 8; k++){
                                	if(k % 2 == 0){  //Even columns in even rows are red
                                        	cout << B_BLACK;
						board[k][i].output();
                                 	} else { //Odd columns in even rows are black
                                        	cout << B_WHITE;
						board[k][i].output();
                                 	}
                        	}
                        	cout << RESET << endl;
                	}

                	else { // Odd Rows
                        	for(k = 0; k < 8; k++) {
                                	if(k % 2 == 0) { // Even columns in odd rows are black
                                        	cout << B_WHITE;
						board[k][i].output();
                                	} else { // Odd columns in odd rows are red
						cout << B_BLACK;
						board[k][i].output();
                                	}
                         	}
                        	cout << RESET << endl;
                	}
        	}
	}

	bool checkers::is_legal(const string& move) const{
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
		int col1,row1,col2,row2;
		char c;
		space tmp;

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
			} else if(col2 == col1 - 2) {
				if(board[col1-2][row1-2].isred())
					redcount--;
				else
					blackcount--;
				board[col1-2][row1-2].setempty(true);
			}
		}
		else if(row2 == row1 + 2){
			if(col2 == col1 + 2) {
				if(board[col1][row1].isred())
					redcount--;
				else
					blackcount--;
				board[col1][row1].setempty(true);
			} else if(col2 == col1 - 2) {
				if(board[col1-2][row1].isred())
					redcount--;
				else
					blackcount--;
				board[col1-2][row1].setempty(true);
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
		if(redcount == 0) {
			cout << "Black Wins!";
			return true;
		} else if(blackcount == 0) {
			cout << "Red Wins!";
			return true;
		} else
			return false;
	}

	void checkers::compute_moves(queue<string>& moves)const{
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
		if(redcount > blackcount)
			return HUMAN;
		else if(blackcount > redcount)
			return COMPUTER;
		else
			return NEUTRAL;
	}

	int checkers::evaluate()const{
		return blackcount - redcount;
	}

	game* checkers::clone() const {
		return new checkers(*this);
	}
}
