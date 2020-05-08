//																	D O W N    W I T H    M A T T H E W    A H N

#include "hashtable.h"
#include <fstream>

// Ahn's starting point:		Far Rockaway Mott		2:02am
// Ahn's ending point:			Flushing Main Street

// command line:	./main.out input.txt output.txt

int main(int argc, char* argv[]){

	Hashtable table(0, 200);


//																					I N P U T
	std::ifstream in_str(argv[1]);

	if (!in_str.good()) {
		std::cerr << "Can't open " << argv[1] << " to read.\n";
		exit(1);
	}

	std::string text;
	std::string inputName;
	std::list<std::string> inputLines;
	std::vector<std::pair<int,int>> inputHours(7);

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
		int inputCloseHour;
		for(int i = 0; i != 7; i++){
			in_str >> text;
			in_str >> inputCloseHour;
			inputHours[i] = std::make_pair(stoi(text),inputCloseHour);
		}

		// R O U T E S

		std::list<std::pair<int,int>> inputTrains;
		std::list<std::pair<int,int>> inputWalks;

		while(text != "end"){

			int routeDuration;
			std::string connectName;				// name of connected station
			int connectHash;						// hash of connected station if needs to be added
			int foundHash;							// hash of connected station if already added
			bool walk;

			in_str >> text;

			// W A L K S
			if(text == "w"){
				walk = true;

				in_str >> routeDuration;
				in_str >> connectName;

				std::pair<int,int> walk;

				foundHash = table.findHash(connectName);

				// if station doesn't exist
				if(foundHash == -1){
					// make station & put in table
					connectHash = table.hash(connectName);
					Station connectStation (connectName, connectHash);
					table.addStation(connectHash, connectStation);
					// pair for inputWalks list
					walk.first = connectHash;
					walk.second = routeDuration;
					inputWalks.push_back(walk);
					table.addOcc();

				// if station exists
				}else{
					// pair for inputWalks list
					walk.first = foundHash;
					walk.second = routeDuration;
					inputWalks.push_back(walk);
					table.addOcc();
				}

			// T R A I N S
			}else{
				walk = false;

				in_str >> routeDuration;
				in_str >> connectName;

				std::pair<int,int> train;

				foundHash = table.findHash(connectName);
				// if station doesn't exist
				if(foundHash == -1){
					// make station & put in table
					connectHash = table.hash(connectName);
					Station connectStation (connectName, connectHash);
					table.addStation(connectHash, connectStation);
					// pair for inputTrains list
					train.first = connectHash;
					train.second = routeDuration;
					inputTrains.push_back(train);
					table.addOcc();
				//if station exists
				}else{
					// pair for inputTrains list
					train.first = foundHash;
					train.second = routeDuration;
					inputTrains.push_back(train);
					table.addOcc();
				}
			}
		}

		int inputHash = table.hash(inputName);
		// create new station
		Station newStation(inputName, inputHash, inputLines, inputHours, inputTrains, inputWalks);
		// put station in table
		table.addStation(inputHash, newStation);
	}



	return 0;


//																					O U T P U T

}
