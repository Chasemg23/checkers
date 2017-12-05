///@file space.cc
///@brief Implements functions for the pieces on the board
///@author Chase Gindlesperger

/**
	* Chase Gindlesperger
	* space.cc
	*
	* CS3560 Term Project
*/

#include <iostream>
#include "colors.h"
#include "space.h"

namespace main_savitch_14 {

	///@details Outputs spaces on board according to their values in board[]
	void space::output() const{
        	if(isempty())
            		cout << "   ";			///< If the space is empty output four spaces
        	else if(isred() && isking())
            		cout << RED << "(@)";		///< If the space is occupied by a red king ouput (@) in red
        	else if(isred() && !isking())
            		cout << RED << " @ ";		///< If the space is occupied by a red piece but not a king ouput @ in red
        	else if(!isred() && isking())
            		cout << BLACK << "(@)";		///< If the space is occupied by a black king output (@) in black
        	else if(!isred() && !isking())
            		cout << BLACK << " @ ";		///< If the space is occupied by a black piece but not a king output @ in black
    	}

    	void space::operator = (const space& s) {
        	red = s.red;
        	king = s.king;
        	empty = s.empty;
    	}
}
