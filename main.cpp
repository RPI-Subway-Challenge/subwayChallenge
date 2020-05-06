//																	D O W N    W I T H    M A T T H E W    A H N

#include "hashtable.h"
#include <fstream>

// Ahn's starting point: Far Rockaway Mott

// command line:	./main.out input.txt output.txt

int main(int argc, char* argv[]){

//																					I N P U T
	std::ifstream in_str(argv[1]);

	if (!in_str.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}

	std::string text;
	std::string inputName;
	std::vector<std::pair<int,int>> inputHours(7);

	while (in_str >> text) {

	}




	// Station* head = new Station();
	return 0;


//																					O U T P U T

}
