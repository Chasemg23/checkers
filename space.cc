#include <iostream>
#include "colors.h"
#include "space.h"

namespace main_savitch_14 {

	void space::output() const{
        	if(isempty())
            		cout << "   ";
        	else if(isred() && isking())
            		cout << RED << "(@)";
        	else if(isred() && !isking())
            		cout << RED << " @ ";
        	else if(!isred() && isking())
            		cout << BLACK << "(@)";
        	else if(!isred() && !isking())
            		cout << BLACK << " @ ";
    	}

    	void space::operator = (const space& s) {
        	red = s.red;
        	king = s.king;
        	empty = s.empty;
    	}
}
