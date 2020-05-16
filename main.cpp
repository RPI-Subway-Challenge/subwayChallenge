//																	D O W N    W I T H    M A T T H E W    A H N

#include "hashtable.h"
#include <fstream>

// Ahn's starting point:		Far Rockaway Mott		2:02am
// Ahn's ending point:			Flushing Main Street

// command line:	./main.out input.txt output.txt


int main(int argc, char* argv[]){

	Time startTime (0, 2, 0);	// start sunday at 2am

	Hashtable table(startTime);

//																					I N P U T

	if(argc != 3){
		std::cerr << "You provided " << argc << "arguments intead of 3.\n";
		exit(1);
	}

	std::ifstream in_str(argv[1]);

	if (!in_str.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}

	std::string text;
	std::string inputName;
	std::list<std::string> inputLines;
	std::vector<std::pair<Time,Time>> inputHours;

	while (in_str >> text) {

		// N A M E
		inputName = text;
		in_str >> text;

		// L I N E S
		while(text != "Times"){
			inputLines.push_back(text);
			in_str >> text;
		}

		// H O U R S
		int inputHour;
		int inputMinute;
		for(int i = 0; i != 7; i++){
			in_str >> inputHour;
			in_str >> inputMinute;
			Time inputOpenTime (i, inputHour,inputMinute);		// open time
			in_str >> inputHour;
			in_str >> inputMinute;
			Time inputCloseTime (i, inputHour,inputMinute);	// close time
			inputHours[i] = std::make_pair(inputOpenTime,inputCloseTime);
		}

		// R O U T E S

		std::list<std::pair<int,Time>> inputTrains;
		std::list<std::pair<int,Time>> inputWalks;

		while(text != "end"){

			int routeMinutes;
			std::string connectName;
			int connectHash;
			bool walk;

			in_str >> text;

			// W A L K S
			if(text == "w"){
				walk = true;

				in_str >> routeMinutes;
				in_str >> connectName;

				std::pair<int,Time> walk;

				connectHash = table.findHash(connectName);

				// if station doesn't exist
				if(connectHash == -1){
					// make station & put in table
					connectHash = table.hash(connectName);
					Station connectStation (connectName, connectHash);
					table.addStation(connectHash, connectStation);
					// pair for inputWalks list
					walk.first = connectHash;
					Time routeTime (0,0, routeMinutes);		// assumes all routes under 60 min
					walk.second = routeTime;
					inputWalks.push_back(walk);
				// if station exists
				}else{
					// pair for inputWalks list
					walk.first = connectHash;
					Time routeTime (0,0, routeMinutes);
					walk.second = routeTime;
					inputWalks.push_back(walk);
				}

			// T R A I N S
			}else{
				walk = false;

				in_str >> routeMinutes;
				in_str >> connectName;

				std::pair<int,Time> train;

				connectHash = table.findHash(connectName);
				// if station doesn't exist
				if(connectHash == -1){
					// make station & put in table
					connectHash = table.hash(connectName);
					Station connectStation (connectName, connectHash);
					table.addStation(connectHash, connectStation);
					// pair for inputTrains list
					train.first = connectHash;
					Time routeTime (0,0, routeMinutes);
					train.second = routeTime;
					inputTrains.push_back(train);
				//if station exists
				}else{
					// pair for inputTrains list
					train.first = connectHash;
					Time routeTime (0,0, routeMinutes);
					train.second = routeTime;
					inputTrains.push_back(train);
				}
			}
		}

		int inputHash = table.findHash(inputName);
		// if not already in table make station
		if(inputHash == -1){
			inputHash = table.hash(inputName);
			Station newStation(inputName, inputHash, inputLines, inputHours, inputTrains, inputWalks);
			table.addStation(inputHash, newStation);
		// if in table update lines hours trains & walks
		}else{
			table.updateStation(inputHash, inputLines, inputHours, inputTrains, inputWalks);
		}
	}

	in_str.close();

	std::cout << "INPUT COMPLETE\n";



//																					S O L V E
	std::string startString = "Far_Rockaway_Mott";
	int startHash = table.findHash(startString);

	if(startHash == -1){
		std::cerr << "Cannot find start: Far_Rockaway_Mott\n";
		exit(1);
	}

	// set ptr to starting station
	Station* ptr = & table.getStation(startHash);

	Route emptyRoute = Route();

	table.findPath(ptr, 0, emptyRoute);


//																					O U T P U T
	
	std::ofstream out_str(argv[2]);

	if(!out_str.good()){
		std::cerr << "Failed to open " << argv[2];
	}

	out_str << "BEST TIME: " << table.getBestDuration().getHour() << " " << table.getBestDuration().getMinute() << std::endl;
	out_str << std::endl << "STOPS:" << std::endl;
	std::list<std::pair<std::string,bool>>::iterator iter;
	// loop through bestRoute
	for(iter = table.getBestRoute().getRoute().begin(); iter != table.getBestRoute().getRoute().end(); iter++){
		// if walkbool print walk before destination
		if(iter->second){
			out_str << "walk" << std::endl;
		}
		// print next stop name
		out_str << iter->first << std::endl;
	}

	out_str.close();

	return 0;
}
