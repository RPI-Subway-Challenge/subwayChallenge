//																	D O W N    W I T H    M A T T H E W    A H N

#include "hashtable.h"

// constructor
Hashtable::Hashtable(Time startTime){
	time = startTime;
	size = 1000;
	occupancy = 0;
	maxProbe = 0;
	duration.setDay(0);
	duration.setHour(0);
	duration.setMinute(0);
	bestDuration.setDay(0);
	bestDuration.setHour(22);
	bestDuration.setMinute(30);

	std::vector<Station> tempTable (size);
	table = tempTable;		// is this copying?
}




// hash function
int Hashtable::hash(std::string &inputName){
	int hash;
	int probeCount = 0;

	for(int i = 0; i != inputName.size(); i++){
		hash = hash + int(inputName[i]);
	}

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

	// linear prob till find station or probeMax hit
	while(table[hash1].getName() != inputName && probeCount != maxProbe){
		if(hash1 == size){
			hash1 = 0;
		}else{
			hash1++;
		}
		probeCount++;
	}

	// if not found return -1
	if(probeCount == maxProbe){
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
void Hashtable::findPath(Station* & ptr, int visted, Route &route){

	// fail base case
	if( ptr->getHours(time.getDay()).first > time || time > ptr->getHours(time.getDay()).second || duration > bestDuration ){	// end if station is closed
		return;
	}

	// success base case
	else if( visted == occupancy ){
		bestDuration = duration;
		bestRoute = route;
		std::cout << "BEST ROUTE FOUND    " << bestDuration.getHour() << ':' << bestDuration.getMinute() << std::endl;
		return;

	// else move on
	}else{
		std::list<std::pair<int,Time>>::iterator iter;	// iter through train and walk lists
		Station* next;
		std::pair<std::string,bool> nextMove;
		visted++;
		// trains
		for(iter == ptr->getTrains().begin(); iter != ptr->getTrains().end(); iter++){
			// change pointer
			next = & getStation(iter->first);
			// add to route
			nextMove.first = next->getName();
			nextMove.second = false;
			route.addStation(nextMove);
			// advance time
			time =  time + iter->second;
			// recursion
			findPath(next, visted, route);
			// revert route
			route.popStation();
			// revert time
			time = time - iter->second;
		}
		// walks
		for(iter == ptr->getWalks().begin(); iter != ptr->getWalks().end(); iter++){
			// change pointer
			next = & getStation(iter->first);
			// add to route
			nextMove.first = next->getName();
			nextMove.second = true;
			route.addStation(nextMove);
			// advance time
			time = time + iter->second;
			// recursion
			findPath(next, visted, route);
			// revert route
			route.popStation();
			// revert time
			time = time - iter->second;
		}
	}
}

