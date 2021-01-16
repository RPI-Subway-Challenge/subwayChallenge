//																	D O W N    W I T H    M A T T H E W    A H N

#include "line.h"
#include <fstream>

// Ahn's starting point:		Far Rockaway Mott		2:02am
// Ahn's ending point:			Flushing Main Street

// command line:	./main.out stationData.txt lineData.txt output.txt


int main(int argc, char* argv[]){

	// check for 4 arguments
	if(argc != 4){
		std::cerr << "You provided " << argc << "arguments intead of 4.\n";
		exit(1);
	}


	//															S T A T I O N S   T E X T

	std::ifstream in_str(argv[1]);

	if (!in_str.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}

	std::string text;
	std::vector<Station> stations(473);
	int i = 0;
	
	// read text and make new station in vector with that name
	while (in_str >> text) {
		Station newStation (text);
		stations[i] = newStation;
		i++;
	}



	//															L I N E S   T E X T

	std::ifstream in_str2(argv[2]);

	if (!in_str2.good()) {
		std::cerr << "Can't open " << argv[2] << " to read.\n";
		exit(1);
	}

	std::vector<Line> lines(36);

	for (i = 0; i != 473; i++){
		std::cout << i << ' ' << stations[i].getName() << std::endl;
	}

	std::cout << "Done.\n";


	return 0;
}

/*
Read stations
Make station vec

Read line data
Construct line
Add 






A
1
Schedule
42
Schedule
end

B
3
95



*/