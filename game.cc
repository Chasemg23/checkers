#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string>
#include <string>     // Provides string
#include "game.h"     // Provides definition of game class
using namespace std;
///@file game.cc
///@brief Code for the functions that structure the game
///@author Savitch

namespace main_savitch_14
{

    void game::clear() const{

	///@details Clears the screen and then repositions the cursor to the top left of the window

	std::cout << "\x1B[2J\x1B[H";
    }

    game::who game::play( ){

	///@brief Game loop
	///@details Sets the move number to zero, loops clearing the screen, displaying the board, and getting input for moves until the game is over
	///@return Human or Computer

	restart( );
	while (!is_game_over( ))
	{
	    clear( );
	    display_status( );
	    if (last_mover( ) == COMPUTER)
		make_human_move( );
	    else
		make_computer_move( );
	}
	display_status( );
	return HUMAN;
    }

    void game::display_message(const string& message) const{

	///@param Constant string message passed by reference
	///@brief Displays the string message to the console

	cout << message;
    }

    string game::get_user_move( )
    {

	///@brief Gets user's move
	///@details Creates a string to store the input, asks the user to make a move, stores the input, converts all letters to lowercase
	///@return User's move stored in string variable answer

	string answer;

	display_message("\nHuman is red and Computer is black. Moves are entered this way: a6b5\n");
	display_message("The first two characters are the position of the piece you want to move"
			" and the last two characters are the position you want to move to.\n");
	display_message("Enter your move: ");
	getline(cin, answer);
	for(int i = 0; i < answer.length(); i++){
		answer[i] = tolower(answer[i]);
	}
	return answer;
    }

    game::who game::winning( ) const
    {

	///@brief Decides who is currently winning
	///@details Evaluates the board to see which player has more pieces on the board
	///@return Human, Computer, or Neutral if the game is currently tied

	int value = evaluate( );

	if (value > 0)
	    return last_mover( );
	else if (value < 0)
	    return next_mover( );
	else
	    return NEUTRAL;
    }

    int game::eval_with_lookahead(int look_ahead, int beat_this)
    {

	///@param Integer look_ahead for levels of evaluation
	///@param Integer beat_this to store another move we're considering
	///@brief Looks ahead and decides the best move to make
	///@details look_ahead is how deep the lookahead should go to evaluate the move and beat_this is another move but if the current board position
	/// can't beat this then cut it short
	///@return The best move stored in best_value

    	queue<string> moves;   ///< All possible opponent moves
	int value;             ///< Value of a board position after opponent moves
    	int best_value;        ///< Evaluation of best opponent move
    	game* future;          ///< Pointer to a future version of this game

	if (look_ahead == 0 || is_game_over( ))
	{
	    if (last_mover( ) == COMPUTER)
	            return evaluate( );
	    else
		return -evaluate( );
	}

    	compute_moves(moves);
    	best_value = INT_MIN;
    	while (!moves.empty( ))
    	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(look_ahead-1, best_value);
	    delete future;
	    if (value > best_value)
	    {
		if (-value <= beat_this)
		    return INT_MIN + 1;
		best_value = value;
	    }
	    moves.pop( );
    	}

    	return -best_value;
    }

    void game::make_computer_move( )
    {

	///@brief Lets the computer move
	///@details Computes all legal moves, evaluates the move, decides which is best, and then makes the move

	queue<string> moves;
	int value;
	int best_value;
	string best_move;
	game* future;

	compute_moves(moves);
	assert(!moves.empty( ));

	best_value = INT_MIN;
	while (!moves.empty( ))
	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
	    delete future;
	    if (value >= best_value)
	    {
		best_value = value;
		best_move = moves.front( );
	    }
	    moves.pop( );
	}

	make_move(best_move);
    }

    void game::make_human_move( )
    {

	///@brief Lets the human move
	///@details Creates a string to store the input, gets the user move, if the move is illegal it asks the user for a different move until
	/// the input is legal and then makes the move

        string move;
	move = get_user_move( );
	while (!is_legal(move))
	{
	    display_message("Illegal move.\n");
	    move = get_user_move( );
        }
	make_move(move);
    }
}
