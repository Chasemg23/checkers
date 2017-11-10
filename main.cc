#include <iostream>
#include "colors.h"
#include "checkers.h"

using namespace std;
using namespace main_savitch_14;

int main () {
	game * c;
	c = new checkers;
	c->play();
	return 0;
}
