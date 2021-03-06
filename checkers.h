///@brief checkers class derived from the game class that defines all functions that needed overridden from the game class and defines the board
///@author Chase Gindlesperger

/**
 *	Chase Gindlesperger
 *	Checkers.h
 *      CS3560 Term Project
 */
#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include "colors.h"
#include "game.h"
#include "space.h"

using namespace std;

namespace main_savitch_14 {

	class checkers : public game{
		public:
			checkers();
			bool is_legal(const string& move) const;
			int evaluate() const;
			void make_move(const string& move);
			void compute_moves(queue<string>& moves) const;
			void display_status() const;
			game* clone()const;
			bool is_game_over() const;
			void restart();
			game::who winning() const;
		
		private:
			space board[8][8];
			int redcount;
			int blackcount;
	};
}
#endif
