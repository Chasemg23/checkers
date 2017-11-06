//Chase Gindlesperger
//Checkers.cc


#include "game.h"
#include "checkers.h"
#include <string>
using namespace std;

namespace main_savitch_14 {


checkers::checkers(){
	int i, k;
	blackcount = 12;
	redcount = 12;

	for(i = 0; i < 8; i++) {
		for(k = 0; k < 8; k++) {
			if(k == 0 || k == 2) {
				if(i % 2 == 1) {
					board[i][k].setempty(false);
					board[i][k].setred(false);
					board[i][k].setking(false);
				}
			} else if(k == 1) {
				if(i % 2 == 0) {
					board[i][k].setempty(false);
					board[i][k].setred(false);
					board[i][k].setking(false);
				}
			} else if(k == 5 || k == 7) {
				if(i % 2 == 0) {
					board[i][k].setempty(false);
					board[i][k].setred(true);
					board[i][k].setking(false);
				}
			}else if(k == 6) {
				if(i % 2 == 1) {
					board[i][k].setempty(false);
					board[i][k].setred(true);
					board[i][k].setking(false);
				}
			}else {
				board[i][k].setempty(true);
				board[i][k].setred(false);
				board[i][k].setking(false);
			}
		}
	}
}

void checkers::restart() {
	checkers();
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
	int st1, st2, en1, en2;
	c = move[0];
	st1 = c - '0';
	st1 -= 48;

	c = move[1];
	st2 = c - '0';

	c = move[2];
	en1 = c - '0';
	en1 -= 48;

	c = move[3];
	en2 = c - '0';

	if(board[st1-1][st2-1].isempty())
		return false;
	if(!(board[en1-1][en2-1].isempty()))
        	return false;

	//MOVES ALLOWED FOR NORMAL PIECES
	if(!board[st1-1][st2-1].isking()) {
		//MOVES ALLOWED FOR HUMANS
		if(next_mover() == HUMAN){
			if(board[st1-1][st2-1].isred()){
				if(en2 == st2-1){
					if(en1 == st1-1 || en1 == st1+1)
						return true;
					else
						return false;
				}
				//JUMPING MOVES
				else if(en2 == st2 - 2) {
					if(en1 == st1 - 2) {
						if(!board[st1-2][st2-2].isempty()) {
							if(!board[st1-2][st2-2].isred())
								return true;
							else
								return false;
						}
						else
							return false;
					}
					else if(en1 == st1 + 2) {
						if(!board[st1][st2-2].isempty()) {
							if(!board[st1][st2-2].isred())
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
			if(!board[st1-1][st2-1].isred()){
				if(st2 == en2 -1) {
					if(en1 == st1-1 || en1 == st1+1)
						return true;
					else
						return false;
				}
				//JUMPING MOVES
				else if(en2 == st2 + 2) {
					if(en1 == st1 + 2) {
						if(!board[st1][st2].isempty()) {
							if(board[st1][st2].isred())
								return true;
							else
								return false;
						}
						else
							return false;
					}
					else if(en1 == st1 - 2) {
						if(!board[st1-2][st2].isempty()){
							if(board[st1-2][st2].isred())
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
		if(next_mover() == HUMAN && !board[st1-1][st2-1].isred())
			return false;
		if(next_mover() == COMPUTER  && board[st1-1][st2-1].isred())
			return false;
		if(st2 == en2 - 1 || st2 == en2+1) {
			if(en1 == st1 -1 || en1 == st1+1)
				return true;
			else
				return false;
		} else if(en2 == st2 + 2) {
			if(en1 == st1 + 2){
				if(!board[st1][st2].isempty()) {
					if(board[st1-1][st2-1].isred() != board[st1][st2].isred())
						return true;
					else
						return false;
				}
				else
					return false;
			}
			else if(en1 == st1 - 2){
				if(!board[st1-2][st2].isempty()) {
					if(board[st1-1][st2-1].isred() != board[st1-2][st2].isred())
						return true;
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		} else if (en2 == st2 - 2) {
			if(en1 == st1 + 2){
				if(!board[st1][st2-2].isempty()) {
					if(board[st1-1][st2-1].isred() != board[st1][st2-2].isred())
						return true;
					else
						return false;
				}
				else
					return false;
			}
			else if(en1 == st1 -2) {
				if(!board[st1-2][st2-2].isempty()) {
					if(board[st1-1][st2-1].isred() != board[st1-2][st2-2].isred())
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
	int st1,st2,en1,en2;
	char c;
	space tmp;

	c = move[0];
	st1 = c - '0';
	st1 -= 48;

	c = move[1];
	st2 = c - '0';

	c = move[2];
	en1 = c - '0';
	en1 -= 48;

	c = move[3];
	en2 = c - '0';

 	tmp = board[en1-1][en2-1];
	board[en1-1][en2-1] = board[st1-1][st2-1];
	board[st1-1][st2-1] = tmp;
	if(en2 == 1 || en2 == 8)
		board[en1-1][en2-1].setking(true);
	if(en2 == st2 - 2){
		if(en1 == st1 + 2){
			if(board[st1][st2-2].isred())
				redcount--;
			else
				blackcount--;
			board[st1][st2-2].setempty(true);
		} else if(en1 == st1 - 2) {
			if(board[st1-2][st2-2].isred())
				redcount--;
			else
				blackcount--;
			board[st1-2][st2-2].setempty(true);
		}
	}
	else if(en2 == st2 + 2){
		if(en1 == st1 + 2) {
			if(board[st1][st2].isred())
				redcount--;
			else
				blackcount--;
			board[st1][st2].setempty(true);
		} else if(en1 == st1 - 2) {
			if(board[st1-2][st2].isred())
				redcount--;
			else
				blackcount--;
			board[st1-2][st2].setempty(true);
		}
	}


	if(en2 == st2 + 2 || en2 == st2 - 2) {
		if(!board[en1-2][en2-2].isempty() && !board[en1-2][en2-2].isred())

		if(board[en1-1][en2-1].isred()) 

		if(board[en1-1][en2-1].isking()) {
			if(board[en1-2][en2-2].isred() != board[en1-1][en2-1].isred())
				if(board[en1-3][en2-3].isempty()) {
					tmp = board[en1-3][en2-3];
					board[en1-3][en2-3] = board[en1-1][en2-1];
					board[en1-1][en2-1] = tmp;
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
