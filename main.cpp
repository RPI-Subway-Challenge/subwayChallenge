//																	D O W N    W I T H    M A T T H E W    A H N

#include "station.h"
#include <fstream>

// Ahn's starting point:		Far Rockaway Mott		2:02am
// Ahn's ending point:			Flushing Main Street

// compile:		g++ main.cpp -o main.out
// run:			./main.out data.csv


int main(int argc, char* argv[]){

	// check for 4 arguments
	if(argc != 2){
		std::cerr << "You provided " << argc << "arguments intead of 2.\n";
		exit(1);
	}


	//																R E A D    D A T A



	//															P R I N T    S T A T I O N S

	std::cout << "COMPLETE\n";

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