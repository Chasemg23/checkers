#ifndef SPACE_H
#define SPACE_H

#include <iostream>

namespace main_savitch_14 {

	class space {
		public:
            		space() {empty = true; king = false; red = false;}
            		void output() const;
            		void operator=(const space& s);
            		void setempty(bool b) {empty = b;}
            		void setred(bool b) {red = b;}
            		void setking(bool b) {king = b;}
            		bool isempty() const {return empty;}
            		bool isred() const {return red;}
            		bool isking() const {return king;}
        
        	private:
            		bool empty;
           	 	bool red;
            		bool king;
    	};
}
#endif
