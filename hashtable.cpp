//																	D O W N    W I T H    M A T T H E W    A H N

#include "hashtable.h"

// constructor
Hashtable::Hashtable(Time startTime){
	time = startTime;
	size = 1000;
	occupancy = 0;
	maxProbe = 0;
	bestDuration.setDay(0);
	bestDuration.setHour(2);
	bestDuration.setMinute(0);

	std::vector<Station> tempTable (size);
	table = tempTable;		// is this copying?
}




// hash function
int Hashtable::hash(std::string &inputName){
	int hash = 0;
	int probeCount = 0;

	for(int i = 0; i != inputName.size(); i++){
		hash = hash + int(inputName[i]);
	}
	hash = hash % size;

	// linear probing to insert
	while(table[hash].getName() != "NONE"){
		if(hash == size-1){
			hash = 0;
		}
		else{
			hash++;
		}
		probeCount++;
	}

	if(probeCount > maxProbe){maxProbe = probeCount;}

	return hash;
}




// find if station in table if so return hash
int Hashtable::findHash(std::string &inputName){
	int hash1 = 0;
	int probeCount = 0;

	// find hash w/o probe
	for(int i = 0; i != inputName.size(); i++){
		hash1 = hash1 + int(inputName[i]);
	}
	hash1 = hash1 % size;

	// linear prob till find station or probeMax hit
	while(table[hash1].getName() != inputName && probeCount != maxProbe){
		if(hash1 == size){
			hash1 = 0;
		}else{
			hash1++;
		}
		probeCount++;
	}

	// if not found at max probe return -1
	if(probeCount == maxProbe && table[hash1].getName() != inputName){
		return -1;
	}

	// if found return hash
	return hash1;
}



// add station at hash index
void Hashtable::addStation(int inputHash, Station &inputStation){
		table[inputHash] = inputStation;
		occupancy++;
}



void Hashtable::updateStation(int inputHash, std::list<std::string> &inputLines, std::vector<std::pair<Time,Time>> &inputHours,
						std::list<std::pair<int,Time>> &inputTrains, std::list<std::pair<int,Time>> &inputWalks){
	table[inputHash].setLines(inputLines);
	table[inputHash].setHours(inputHours);
	table[inputHash].setTrains(inputTrains);
	table[inputHash].setWalks(inputWalks);

}





// recursive path finding algorithm
void Hashtable::findPath(Station* & ptr, int visited, Route &route){

	if( visited > occupancy ){
		std::cerr << "ERROR: Visited station count is greater than total num of stations\n";
		exit(1);
	}

	// fail base case
	else if( ptr->getHours(time.getDay()).first > time || time > ptr->getHours(time.getDay()).second || route.getDuration() > bestDuration ){	// end if station is closed
		return;
	}


	// success base case
	else if( visited == occupancy && bestDuration > route.getDuration()){
		bestDuration = route.getDuration();
		bestRoute = route;
		std::cout << "BEST ROUTE FOUND    " << bestDuration.getHour() << ':' << bestDuration.getMinute() << std::endl;
		return;


	// else move on
	}else{
		// if new increase visited count and set station visited
		if(ptr->getVisited() == false){
			visited++;
			ptr->setVisited();
		}

		// print path
		std::cout << visited << ' ';
		std::list<std::pair<std::string,bool>>::iterator pathIter;
		for(pathIter = route.getPath().begin(); pathIter != route.getPath().end(); pathIter++){
			std::cout << pathIter->first << ' ';
		}
		std::cout << std::endl;

		// initializations
		std::list<std::pair<int,Time>>::iterator iter;	// iter through train and walk lists
		Station* next;
		std::pair<std::string,bool> nextMove;

		// trains
		for(iter = ptr->getTrains().begin(); iter != ptr->getTrains().end(); iter++){
			// assign next pointer
			next = & table[iter->first];
			// add to route
			nextMove.first = next->getName();
			nextMove.second = false;
			route.addStation(nextMove);
			// advance time
			time =  time + iter->second;
			route.addDuration(iter->second);
			// recursion
			findPath(next, visited, route);
			// revert route
			route.popStation();
			// revert visited
			ptr->setUnvisited();
			// revert time
			time = time - iter->second;
			route.subDuration(iter->second);
		}

		// walks
		for(iter = ptr->getWalks().begin(); iter != ptr->getWalks().end(); iter++){
			// change pointer
			next = & table[iter->first];
			// add to route
			nextMove.first = next->getName();
			nextMove.second = true;
			route.addStation(nextMove);
			// advance time
			time = time + iter->second;
			route.addDuration(iter->second);
			// recursion
			findPath(next, visited, route);
			// revert route
			route.popStation();
			time = time - iter->second;
			route.subDuration(iter->second);
		}
	}
}

