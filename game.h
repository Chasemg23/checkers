#ifndef MAIN_SAVITCH_GAME
#define MAIN_SAVITCH_GAME
#include <queue>   // Provides queue<string>
#include <string>  // Provides string

namespace main_savitch_14
{
    class game
    {
    public:
	void clear() const;

	enum who { HUMAN, NEUTRAL, COMPUTER }; ///< Possible game outcomes
	
	///@brief Constructor for game class
	///@details Sets the move number to zero
	game( ) { move_number = 0; }

	///@brief Destructor for game class
	virtual ~game( ) { }
	
	who play( );

    protected:
	virtual void display_message(const std::string& message) const;
    	virtual std::string get_user_move( );
	
	///@details Decides who the last mover was based on the move number, 1 = Human or 0 = Computer
	///@return Enumeration value, either Human or Computer
	virtual who last_mover( ) const 
	    { return (move_number % 2 == 1 ? HUMAN : COMPUTER); }

	///@return Number of moves completed
	virtual int moves_completed( ) const { return move_number; }

	///@details Decides who the next mover will be based on the move number, 1 = Computer or 0 = Human
	///@return Enumeration value, either Human or Computer
	virtual who next_mover( ) const
	    { return (move_number % 2 == 0 ? HUMAN : COMPUTER); }

	///@param Enumeration value player, either Human or Computer
	///@details Decides who the opposite player is based on the parameter value
	///@return Returns Human if the parameter is Computer or returns Computer if the parameter is Human
	virtual who opposite(who player) const
	    { return (player == HUMAN) ? COMPUTER : HUMAN; }
    	virtual who winning( ) const;

	///@param Constant string move passed by reference
	///@details increments the move number by one
    	virtual void make_move(const std::string& move) { ++move_number; }

	///@details Resets the move number back to zero
    	virtual void restart( ) { move_number = 0; }

    	virtual game* clone( ) const = 0;
    	virtual void compute_moves(std::queue<std::string>& moves) const = 0;
    	virtual void display_status( ) const = 0;
    	virtual int evaluate( ) const = 0;
    	virtual bool is_game_over( ) const = 0;
    	virtual bool is_legal(const std::string& move) const = 0;

    private:
	int move_number;                     ///< Integer that stores the number of moves made so far

	static const int SEARCH_LEVELS = 4;  ///< Levels for look-ahead evaluation
	
	int eval_with_lookahead(int look_ahead, int beat_this);
	void make_computer_move( );
	void make_human_move( );
    };
}

#endif
