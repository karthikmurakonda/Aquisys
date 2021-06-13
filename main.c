#include "main.h"

int main() {
    #ifdef _WIN32
      	system("ATTRIB +H /s /d %cd%/.*");	//command to hide .data folder in windows os
	#endif

    loginpage();

    return 0;
}
